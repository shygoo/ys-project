#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "smsr00.h"
#include "bswap.h"
#include "rom.h"
#include "util.h"
#include "ys_structs.h"
#include "img.h"

#include "stb_image.h"
#include "stb_image_write.h"

#define ROM_OBJECT_LUT 0x000A1C90
#define OBJECT_LUT_COUNT 1582

#define ROM_BANK_TABLE 0x000A79D4

// bank offset to rom addr
uint32_t bo_addr(rom_t *rom, uint32_t bankOffset)
{
    // Bank 00: 00001060
    // Bank 01: 00000000
    // Bank 02: 00000000
    // Bank 03: 00526EC0
    // Bank 04: 00B47A10

    uint32_t *banks = (uint32_t *) &rom->data[ROM_BANK_TABLE];

    uint8_t  bankNum = (bankOffset >> 24) & 0x0F;
    uint32_t offset = bankOffset & 0x00FFFFFF;
    uint32_t romAddress = BSWAP32(banks[bankNum]) + offset;

    return romAddress;
}

void *bo_ptr(rom_t *rom, uint32_t bankOffset)
{
    return &rom->data[bo_addr(rom, bankOffset)];
}

void dump_all_smsr00(rom_t *rom, const char *dirpath)
{
    printf("decoding smsr00 files... ");

    for(int i = 0; i < rom->size - sizeof(SMSR00_SIG); i += 4)
    {
        uint8_t *block = &rom->data[i];

        if(memcmp(SMSR00_SIG, block, sizeof(SMSR00_SIG)) != 0)
        {
            continue;
        }

        size_t size = smsr00_get_output_size(block);
        uint8_t *out = malloc(size);
        smsr00_decode(block, out);

        char path[256];
        sprintf(path, "%s/%08X.bin", dirpath, i);
        FILE *fp = fopen(path, "wb");
        fwrite(out, 1, size, fp);
        fclose(fp);

        free(out);
    }
    printf("done\n");
}

void block_info_copy_data(void *dst, rom_t *rom, struct BlockInfo *blockInfo)
{
    uint32_t addr = bo_addr(rom, blockInfo->boData);

    if(blockInfo->sizeEnc < blockInfo->size)
    {
        smsr00_decode(&rom->data[addr + 0x10], dst);
    }
    else
    {
        memcpy(dst, &rom->data[addr], blockInfo->size);
    }
}


///////////

void dump_block_info_field(FILE *fp, uint32_t boBlockInfo, const char *label, rom_t *rom)
{
    uint32_t raBlockInfo = bo_addr(rom, boBlockInfo);
    struct BlockInfo *blockInfo = (struct BlockInfo *) &rom->data[raBlockInfo];

    fprintf(fp, "    %-18s     %08X (%08X)\n", label, boBlockInfo, raBlockInfo);
    
    uint32_t raData = bo_addr(rom, blockInfo->boData);

    fprintf(fp,
        "    ->  size:    %08X\n" // seems like the upper 16 bits are flags
        "        sizeEnc: %08X\n"
        "        boData:  %08X (%08X)\n",
        blockInfo->size, blockInfo->sizeEnc, blockInfo->boData, raData
    );

    if(blockInfo->sizeEnc > blockInfo->size)
    {
        fprintf(fp, "        **** check size\n");
    }
}

void copytile(uint32_t *outputBuf, int wrap, int x, int y, uint32_t *img, int width, int height)
{
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            outputBuf[(y + j) * wrap + x + i] = img[j*width+i];
        }
    }
}

void dump_object_info_type_0000(FILE *fp, uint16_t objectId, struct ObjectA_0000 *objA, rom_t *rom)
{
    struct TileDimensions *tileDimensions = NULL;
    struct BlockInfo *tileDataInfo = NULL;
    struct BlockInfo *tilePaletteInfo = NULL;
    struct BlockInfo *tileMapInfo = NULL;
    struct BlockInfo *collisionMapInfo = NULL;

    fprintf(fp,
        "  ObjectA\n"
        "    type            %04X\n"
        "    useOverlay      %02X\n",
        objA->head.type, objA->useOverlay
    );

    if(!objA->useOverlay)
    {
        fprintf(fp, "    nativeFunc      %08X\n", objA->asmInfo.nativeFunc);
    }
    else
    {
        struct OverlayInfo *ovlInfo = &objA->asmInfo.overlayInfo;

        fprintf(fp,
            "    ovlRomStart     %08X\n"
            "    ovlRomEnd       %08X\n"
            "    ovlFakeMemStart %08X\n"
            "    ovlFakeMemEnd   %08X\n",
            ovlInfo->romStart, ovlInfo->romEnd, ovlInfo->fakeMemStart, ovlInfo->fakeMemEnd
        );
    }

    fprintf(fp,
        "    objectId        %04X\n"
        "    unk1A           %04X\n",
       objA->objectId, objA->unk1A
    );

    if(objA->boTileDimensions != 0)
    {
        uint32_t raTileDimensions = bo_addr(rom, objA->boTileDimensions);
        tileDimensions = (struct TileDimensions *) &rom->data[raTileDimensions];

        fprintf(fp, "    boTileDimensions     %08X (%08X)\n", objA->boTileDimensions, raTileDimensions);

        fprintf(fp,
            "    ->  unk00:      %04X\n"
            "        unk02:      %04X\n"
            "        tileWidth:  %04X\n"
            "        tileHeight: %04X\n"
            "        mapWidth:   %04X\n"
            "        mapHeight:  %04X\n",
            tileDimensions->unk00,
            tileDimensions->unk02,
            tileDimensions->tileWidth,
            tileDimensions->tileHeight,
            tileDimensions->mapWidth,
            tileDimensions->mapHeight
        );
    }

    if(objA->boTileDataInfo != 0)
    {
        uint32_t raTileDataInfo = bo_addr(rom, objA->boTileDataInfo);
        tileDataInfo = (struct BlockInfo *) &rom->data[raTileDataInfo];
        dump_block_info_field(fp, objA->boTileDataInfo, "boTileDataInfo", rom);
    }

    if(objA->boTilePaletteInfo != 0)
    {
        uint32_t raTilePaletteInfo = bo_addr(rom, objA->boTilePaletteInfo);
        tilePaletteInfo = (struct BlockInfo *) &rom->data[raTilePaletteInfo];
        dump_block_info_field(fp, objA->boTilePaletteInfo, "boTilePaletteInfo", rom);
    }

    if(objA->boTileMapInfo != 0)
    {
        uint32_t raTileMapInfo = bo_addr(rom, objA->boTileMapInfo);
        tileMapInfo = (struct BlockInfo *) &rom->data[raTileMapInfo];
        dump_block_info_field(fp, objA->boTileMapInfo, "boTileMapInfo", rom);
    }

    if(objA->boUnkData1Info != 0)
    {
        dump_block_info_field(fp, objA->boUnkData1Info, "boUnkData1Info", rom);
    }

    if(objA->boUnkData2Info != 0)
    {
        dump_block_info_field(fp, objA->boUnkData2Info, "boUnkData2Info", rom);
    }

    if(objA->boCollisionMapInfo != 0)
    {
        collisionMapInfo = (struct BlockInfo *) bo_ptr(rom, objA->boCollisionMapInfo);
        dump_block_info_field(fp, objA->boCollisionMapInfo, "boCollisionMapInfo", rom);
    }

    fprintf(fp,
        "    unk54   %08X\n"
        "    unk58   %08X\n"
        "    unk5C   %08X\n"
        "    unk60   %08X\n\n",
        objA->unk54, objA->unk58, objA->unk5C, objA->unk60
    );

    //if(objectId == 0x8067)
    if(tileDimensions && tilePaletteInfo && tileDataInfo && tileMapInfo)
    {
        //printf("%04X\n", objectId);

        uint8_t  *tileData = (uint8_t *) malloc(tileDataInfo->size);
        uint16_t *tilePalette = (uint16_t *) malloc(tilePaletteInfo->size);
        uint16_t *tileMap = (uint16_t *) malloc(tileMapInfo->size);

        block_info_copy_data(tileData, rom, tileDataInfo);
        block_info_copy_data(tilePalette, rom, tilePaletteInfo);
        block_info_copy_data(tileMap, rom, tileMapInfo);

        int numPixelsPerTile = tileDimensions->tileWidth * tileDimensions->tileHeight;
        int numTiles = tileDataInfo->size / numPixelsPerTile;
        int numTilesInMap = tileMapInfo->size / sizeof(uint16_t);

        uint32_t *tileBank32 = malloc(numTiles * numPixelsPerTile * sizeof(uint32_t));

        printf("w %d, h %d ", tileDimensions->tileWidth, tileDimensions->tileHeight);
        printf("%04X numPixelsPerTile %d, numTiles %d (tileDataInfo->size 0x%04X), numTilesInMap %d\n", objectId, numPixelsPerTile, numTiles, tileDataInfo->size, numTilesInMap);

        // convert all tiles to rgba32 images
        for(int i = 0; i < numTiles; i++)
        {
            int offs = i * numPixelsPerTile;
            ci8_to_rgba32(&tileBank32[offs], &tileData[offs], tilePalette, numPixelsPerTile);
        }

        if(objectId & 0x8000)
        {
            // dump tile bank to png
            int tileBankHeight = numTiles * tileDimensions->tileHeight;
            int tileBankWidth = tileDimensions->tileWidth;
            char pngName[256];
            sprintf(pngName, "bank_%04X.png", objectId);
            stbi_write_png(pngName, tileDimensions->tileWidth, tileBankHeight, 4, tileBank32, tileBankWidth*4);

            //printf("%d\n", tileMapInfo->size);

            int mapWidthCalc = (tileMapInfo->size * numPixelsPerTile / sizeof(uint16_t)) / (tileDimensions->mapHeight);
            int mapNumTilesXCalc = mapWidthCalc / tileDimensions->tileHeight;

            int mapNumTilesX = mapWidthCalc / tileDimensions->tileWidth;
            int mapNumTilesY = tileDimensions->mapHeight / tileDimensions->tileHeight;

            if(mapWidthCalc != tileDimensions->mapWidth)
            {
                printf("map width overriden (%d to %d)\n", tileDimensions->mapWidth, mapWidthCalc);
            }

            // dump tile map to png
            uint32_t *imgOut = malloc(mapWidthCalc * tileDimensions->mapHeight * sizeof(uint32_t));
            uint32_t numPixelsInMapImage = numTilesInMap * numPixelsPerTile;

            for(int tileMapIdx = 0; tileMapIdx < numTilesInMap; tileMapIdx++)
            {
                int row = tileMapIdx / mapNumTilesX;
                int col = tileMapIdx % mapNumTilesX;

                int tileBankIdx = BSWAP16(tileMap[tileMapIdx]);

                int realRow = row;

                if(mapNumTilesY >= 32)
                {
                    realRow = (row / 2) + ((row & 1) ? 16 : 0);
                }

                int x = col * tileDimensions->tileWidth;
                int y = realRow * tileDimensions->tileHeight;

                copytile(imgOut, mapNumTilesX * tileDimensions->tileWidth,
                    x, y,
                    &tileBank32[tileBankIdx * numPixelsPerTile],
                    tileDimensions->tileWidth,
                    tileDimensions->tileHeight);
            }

            //char pngName[256];
            sprintf(pngName, "map_%04X.png", objectId);
            stbi_write_png(pngName, mapWidthCalc, tileDimensions->mapHeight, 4, imgOut, mapWidthCalc*4);
            free(imgOut);
        }

        free(tileData);
        free(tilePalette);
        free(tileMap);
        free(tileBank32);
        
    }
    
}

void dump_object_info_type_0001(FILE *fp, struct ObjectA_0001 *objA)
{
    // 803FB6E0

    fprintf(fp,
        "    type    %04X\n"
        "    unk04   %02X\n"
        "    unk08   %08X\n"
        "    unk18   %08X\n"
        "    unk1C   %02X\n"
        "    unk1D   %02X\n"
        "    boUnk20 %08X\n"
        "    boUnk24 %08X\n"
        "    boUnk28 %08X\n"
        "    unk2C   %08X\n"
        "    boUnk30 %08X\n"
        "    unk34   %08X\n"
        "    unk38   %08X\n"
        "    unk3C   %08X\n"
        "    boUnk40 %08X\n\n",
        objA->head.type, objA->unk04, objA->unk08, objA->unk18, objA->unk1C, objA->unk1D,
        objA->boUnk20, objA->boUnk24, objA->boUnk28, objA->unk2C, objA->boUnk30,
        objA->unk34, objA->unk38, objA->unk3C, objA->boUnk40
    );
}

void dump_object_info_type_0002(FILE *fp, struct ObjectA_0002 *objA)
{
    fprintf(fp,
        "  ObjectA\n"
        "    type        %04X\n"
        "    useOverlay  %02X\n",
        objA->head.type, objA->useOverlay
    );

    if(!objA->useOverlay)
    {
        fprintf(fp, "    nativeFunc      %08X\n", objA->asmInfo.nativeFunc);
    }
    else
    {
        struct OverlayInfo *ovlInfo = &objA->asmInfo.overlayInfo;

        fprintf(fp,
            "    ovlRomStart     %08X\n"
            "    ovlRomEnd       %08X\n"
            "    ovlFakeMemStart %08X\n"
            "    ovlFakeMemEnd   %08X\n",
            ovlInfo->romStart, ovlInfo->romEnd, ovlInfo->fakeMemStart, ovlInfo->fakeMemEnd
        );
    }
}

void dump_object_info(rom_t *rom, const char* path)
{
    printf("dumping object info... ");

    FILE *fp = fopen(path, "wb");

    struct ObjectEntry *entries = (struct ObjectEntry *) &rom->data[ROM_OBJECT_LUT];

    for(int i = 0; i < OBJECT_LUT_COUNT; i++)
    {
        struct ObjectEntry *entry = &entries[i];

        uint32_t raObjectA = bo_addr(rom, entry->boObjectA);
        uint32_t raObjectB = bo_addr(rom, entry->boObjectB);

        struct ObjectA *objectA = (struct ObjectA *) &rom->data[raObjectA];
        uint8_t *objectB = &rom->data[raObjectB];

        fprintf(fp, "id: %04X, boObjectA: %08X (%08X), boObjectB: %08X (%08X)\n",
            entry->objectId, entry->boObjectA, raObjectA, entry->boObjectB, raObjectB);

        switch(objectA->type)
        {
        case 0x0000:
            dump_object_info_type_0000(fp, entry->objectId, (struct ObjectA_0000 *) objectA, rom);
            break;
        case 0x0001: // yoshi
            dump_object_info_type_0001(fp, (struct ObjectA_0001 *) objectA);
            break;
        case 0x0002:
            dump_object_info_type_0002(fp, (struct ObjectA_0002 *) objectA);
            break;
        default:
            fprintf(fp, "unhandled type %04X\n", objectA->type);
        }
    }
    printf("done\n");
    fclose(fp);
}


int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        return EXIT_FAILURE;
    }

    const char *rompath = argv[1];

    rom_t rom;
    rom_load(&rom, rompath);

    makedir("dump");
    makedir("dump/smsr00");

    //dump_all_smsr00(&rom, "dump/smsr00");
    dump_object_info(&rom, "dump/object_info.txt");

    rom_unload(&rom);
    
}
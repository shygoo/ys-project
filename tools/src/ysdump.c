#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "smsr00.h"
#include "bswap.h"
#include "rom.h"
#include "util.h"

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

#define ROM_OBJECT_LUT 0x000A1C90
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

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct
{
    /*00*/ u16 objectId;  // unique identifier
    /*02*/ u16 unk02;     // probably padding
    /*04*/ u32 boObjectA; // bank-offset of ObjectA struct
    /*08*/ u32 boObjectB; // bank-offset of ObjectB struct
} ObjectEntry;


/*
8005B184 func

800A1090 yosh obj entry
load u16 objA.unk00 from rom -> 800FEA00
load top 16 bytes of objA -> 803FB6E0 [00010000 00000000 8001D760 00000000]
load 0x44 (68) bytes of objA -> 803FB6E0
jalr calls 0x8005B0AC

8005B0AC func reads from yoshi's objA struct
8005205C ""

800A1124 apple obj entry
load u16 objA.unk00 from rom -> 803d0260
load top 16 bytes of objA -> 803d0260
load 0x64 (100) bytes of objA -> 803d0260

Yoshi's objA is 0x44 bytes, apple is 0x64 bytes

800A615C objA.unk00 is and index of the jump table here 

struct Struct1
{
    u16 type; // objA.unk00 put here
    u16 _02; // padding
    struct ObjectA_0001 *objA;
    u16 unk08;
    u16 _0A; // padding
    void *unk0C;
};

struct ObjectA_0001
{
    u8 unk1C;
    u8 unk1D;
};

func_8005AF8C(struct Struct1 *a0, u16 objectId) // type 0000 handler

func_8005B0AC(struct Struct1 *ptr, u16 objectId) // type 0001 (yoshi object) handler
{
    sp1c = a1
    func_80051DA0(&ptr->objA, objectId) // fills ptr+4, ptr+8, ptr+0c
    a2->unk10 = ptr->unk04->unk1C // sb
    a2->unk40 = ptr->unk0c + 2
    a2->unk11 = *(u8*)(&ptr->unk04->unk1C + 1) // ? unk04->unk1D?
    return 1;
}

func_8005B10C(struct Struct1 *a0, u16 objectId)
{

}

*/

void dump_object_info_type_0000(FILE *fp, uint8_t *objA)
{
    uint32_t objA_type                = U16_BE(objA, 0x00);
    uint32_t objA_unk02               = U16_BE(objA, 0x02);
    uint32_t objA_unk04               = U32_BE(objA, 0x04);
    uint32_t objA_bhvInitFunc         = U32_BE(objA, 0x08);
    uint32_t objA_unk0C               = U32_BE(objA, 0x0C);
    uint32_t objA_unk10               = U32_BE(objA, 0x10);
    uint32_t objA_unk14               = U32_BE(objA, 0x14);
    uint16_t objA_objectId            = U16_BE(objA, 0x18);
    uint16_t objA_unk1A               = U16_BE(objA, 0x1A);
    uint32_t objA_tileDimensionsSize  = U32_BE(objA, 0x1C);
    uint32_t objA_boTileDimensions    = U32_BE(objA, 0x20);
    uint32_t objA_tileDataInfoSize    = U32_BE(objA, 0x24);
    uint32_t objA_boTileDataInfo      = U32_BE(objA, 0x28);
    uint32_t objA_tilePaletteInfoSize = U32_BE(objA, 0x2C);
    uint32_t objA_boTilePaletteInfo   = U32_BE(objA, 0x30);
    uint32_t objA_tileMapInfoSize     = U32_BE(objA, 0x34);
    uint32_t objA_boTileMapInfo       = U32_BE(objA, 0x38);
    uint32_t objA_unkData1InfoSize    = U32_BE(objA, 0x3C);
    uint32_t objA_boUnkData1Info      = U32_BE(objA, 0x40);
    uint32_t objA_unkData2InfoSize    = U32_BE(objA, 0x44);
    uint32_t objA_boUnkData2Info      = U32_BE(objA, 0x48);
    uint32_t objA_collisionMapInfoSize = U32_BE(objA, 0x4C);
    uint32_t objA_boCollisionMapInfo   = U32_BE(objA, 0x50);
    uint32_t objA_unk54   = U32_BE(objA, 0x54);
    uint32_t objA_unk58   = U32_BE(objA, 0x58);
    uint32_t objA_unk5C   = U32_BE(objA, 0x5C);
    uint32_t objA_unk60   = U32_BE(objA, 0x60);

    fprintf(fp,
        "  ObjectA\n"
        "    type        %04X\n"
        "    unk02       %04X\n"
        "    unk04       %08X\n"
        "    bhvInitFunc %08X\n"
        "    unk0C       %08X\n"
        "    unk10       %08X\n"
        "    unk14       %08X\n"
        "    objectId    %04X\n"
        "    unk1A       %04X\n"
        "    tileDimensionsSize   %08X\n"
        "    boTileDimensions     %08X\n"
        "    tileDataInfoSize     %08X\n"
        "    boTileDataInfo       %08X\n"
        "    tilePaletteInfoSize  %08X\n"
        "    boTilePaletteInfo    %08X\n"
        "    tileMapInfoSize      %08X\n"
        "    boTileMapInfo        %08X\n"
        "    unkData1InfoSize     %08X\n"
        "    boUnkData1Info       %08X\n"
        "    unkData2InfoSize     %08X\n"
        "    boUnkData2Info       %08X\n"
        "    collisionMapInfoSize %08X\n"
        "    boCollisionMapInfo   %08X\n"
        "    unk54   %08X\n"
        "    unk58   %08X\n"
        "    unk5C   %08X\n"
        "    unk60   %08X\n\n",
        objA_type, objA_unk02, objA_unk04, objA_bhvInitFunc, objA_unk0C, objA_unk10, objA_unk14, objA_objectId, objA_unk1A,
        objA_tileDimensionsSize, objA_boTileDimensions,
        objA_tileDataInfoSize, objA_boTileDataInfo,
        objA_tilePaletteInfoSize, objA_boTilePaletteInfo,
        objA_tileMapInfoSize, objA_boTileMapInfo,
        objA_unkData1InfoSize, objA_boUnkData1Info,
        objA_unkData2InfoSize, objA_boUnkData2Info,
        objA_collisionMapInfoSize, objA_boCollisionMapInfo,
        objA_unk54, objA_unk58, objA_unk5C, objA_unk60
    );
}

void dump_object_info_type_0001(FILE *fp, uint8_t *objA)
{
    // 803FB6E0
    //printf("type 0001 unhandled\n");

    uint16_t objA_type = U16_BE(objA, 0x00);
    uint8_t  objA_unk04 = objA[0x04];
    uint32_t objA_unk08 = U32_BE(objA, 0x08);
    uint16_t objA_unk18 = U16_BE(objA, 0x18);
    uint8_t  objA_unk1C = objA[0x1C];
    uint8_t  objA_unk1D = objA[0x1D];
    uint32_t objA_boUnk20 = U32_BE(objA, 0x20);
    uint32_t objA_boUnk24 = U32_BE(objA, 0x24);
    uint32_t objA_boUnk28 = U32_BE(objA, 0x28);
    uint32_t objA_unk2C = U32_BE(objA, 0x2C);
    uint32_t objA_boUnk30 = U32_BE(objA, 0x30);
    uint32_t objA_unk34 = U32_BE(objA, 0x34);
    uint32_t objA_unk38 = U32_BE(objA, 0x38);
    uint32_t objA_unk3C = U32_BE(objA, 0x3C);
    uint32_t objA_boUnk40 = U32_BE(objA, 0x40);

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
        objA_type, objA_unk04, objA_unk08, objA_unk18, objA_unk1C, objA_unk1D,
        objA_boUnk20, objA_boUnk24, objA_boUnk28, objA_unk2C, objA_boUnk30,
        objA_unk34, objA_unk38, objA_unk3C, objA_boUnk40
    );
}

void  dump_object_info_type_0002(FILE *fp, uint8_t *objA)
{
    uint16_t objA_type = U16_BE(objA, 0x00);
    uint8_t  objA_unk04 = objA[0x04];
    uint32_t objA_unk08 = U32_BE(objA, 0x08); // rom start
    uint32_t objA_unk0C = U32_BE(objA, 0x0C); // rom end
    uint32_t objA_unk10 = U32_BE(objA, 0x10); // fake ram start
    uint32_t objA_unk14 = U32_BE(objA, 0x14); // fake ram end

    // endptr - last word in the block = relocation info start

    // 800DA840 overlay table
    // array of { void *location, u16 objectNum, u16 _pad,  void *fakeMemStart, void *fakeMemEnd }

    // 800FE96C relocation table around here
    // 8033a920 800fe958 00c2e050

    // func_80081430(void *overlay_block, void *relocation_block); // linker routine

    /*
        if unk04 is 00, unk08 is a pointer to a native function (8005BE50),
        and unk0c,unk10,unk14 are 0
    */

   // 80081744 obj type 2 handler
   // func_80081744(unk08, unk0c, unk10, unk14)
   // {
   //    res = func_80064DD0(unk14 - unk10)
   //    if(!res) return;
   //    func_8008169C(unk08, unk0c, unk10, unk14, res)
   //    return res;
   // }


   // 80341A60 44 00 03 d4
   // 80341530+03D4

   // Relocation structure
   // ss -- rrrr oooooooooooooooooooooooo
   // s: section (0=invalid?, 1=.text, 2=.data, 3=.rodata)
   // -: unused bits
   // r: relocation type (4 = R_MIPS_26, 5 = R_MIPS_HI16, 6 = R_MIPS_LO16)
   // o: offset

   // top two bits selects one of these 800FE9A8
   // 00000000 invalid
   // 80341af0 .text
   // 80341c10  80341C10
   // 80341c20



    fprintf(fp,
        "    type    %04X\n"
        "    unk04   %02X\n"
        "    unk08   %08X\n"
        "    unk0C   %08X\n"
        "    unk10   %08X\n"
        "    unk14   %08X\n\n",
        objA_type, objA_unk04, objA_unk08,
        objA_unk0C, objA_unk10, objA_unk14);
}

void dump_object_info(rom_t *rom, const char* path)
{
    FILE *fp = fopen(path, "wb");

    for(int i = 0; i < 1582; i++)
    {
        uint8_t *entry = &rom->data[ROM_OBJECT_LUT + i*12];

        uint16_t entry_objectId = U16_BE(entry, 0x00);
        uint32_t entry_objectUnk = U16_BE(entry, 0x02);
        uint32_t entry_boObjectA = U32_BE(entry, 0x04);
        uint32_t entry_boObjectB = U32_BE(entry, 0x08);

        uint32_t raObjectA = bo_addr(rom, entry_boObjectA);
        uint32_t raObjectB = bo_addr(rom, entry_boObjectB);

        uint8_t *objA = &rom->data[raObjectA];
        uint8_t *objB = &rom->data[raObjectB];

        uint32_t objA_type = U16_BE(objA, 0x00);

        fprintf(fp, "id: %04X, boObjectA: %08X (%08X), boObjectB: %08X (%08X)\n",
            entry_objectId, entry_boObjectA, raObjectA, entry_boObjectB, raObjectB);

        switch(objA_type)
        {
            case 0x0000:
                dump_object_info_type_0000(fp, objA);
                break;
            case 0x0001: // yoshi
                dump_object_info_type_0001(fp, objA);
                break;
            case 0x0002:
                dump_object_info_type_0002(fp, objA);
                //fprintf(fp, "type 0002 unhandled\n");
                // 0x18 bytes each
                // 00020000 01000000 00EABA90 00EAEC40 807B4800 807B7C40
                break;
            default:
                fprintf(fp, "unhandled type %04X\n", objA_type);
        }

    }

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

    dump_all_smsr00(&rom, "dump/smsr00");
    dump_object_info(&rom, "dump/object_info.txt");

    rom_unload(&rom);
    
}
#ifndef _YS_STRUCTS_H_
#define _YS_STRUCTS_H_

#include "n64types.h"

#pragma scalar_storage_order big-endian

struct ObjectEntry
{
    /*00*/ u16 objectId;  // unique identifier
    /*02*/ u16 unk02;     // probably padding
    /*04*/ u32 boObjectA; // bank-offset of ObjectA struct
    /*08*/ u32 boObjectB; // bank-offset of ObjectB struct
};

struct OverlayInfo
{
    /*00*/ u32   romStart;
    /*04*/ u32   romEnd;
    /*08*/ u32   fakeMemStart;
    /*0C*/ u32   fakeMemEnd;
};

union AsmInfo
{
    /*00*/ u32 nativeFunc; // void *
    /*00*/ struct OverlayInfo overlayInfo;
};

struct ObjectA
{
    u16   type;
    u8    _pad02[2];
};

struct ObjectA_0000
{
    /*00*/ struct ObjectA head;
    
    /*04*/ u8    useOverlay;           // 1 if asmInfo.overlayInfo is to be used
           u8    _pad05[3];

    /*08*/ union AsmInfo asmInfo;

    /*08   asmInfo.nativeFunc
      08   asmInfo.overlayInfo.romStart
      0C   asmInfo.overlayInfo.romEnd
      10   asmInfo.overlayInfo.fakeMemStart
      14   asmInfo.overlayInfo.fakeMemEnd */

    /*18*/ u16   objectId;             // unique identifier
    /*1A*/ u16   unk1A;

    /*1C*/ u32   tileDimensionsSize;   // sizeof(TileDimensions)
    /*20*/ u32   boTileDimensions;     // bank-offset of TileDimensions struct

    /*24*/ u32   tileDataInfoSize;     // sizeof(BlockInfo)
    /*28*/ u32   boTileDataInfo;       // bank-offset of BlockInfo struct for the tiles' 8bit color-index data

    /*2C*/ u32   tilePaletteInfoSize;  // sizeof(BlockInfo)
    /*30*/ u32   boTilePaletteInfo;    /* bank-offset of BlockInfo struct for the tiles' palette data
                                          palette data is a 0x200 byte array of rgba5551 (u16) colors */

    /*34*/ u32   tileMapInfoSize;      // sizeof(BlockInfo)
    /*38*/ u32   boTileMapInfo;        /* bank-offset of BlockInfo struct for the tile map
                                          the tile map is a u16 array tile indeces */

    /*3C*/ u32   unkData1InfoSize;     // sizeof(BlockInfo)
    /*40*/ u32   boUnkData1Info;       // bank-offset of BlockInfo struct for ??

    /*44*/ u32   unkData2InfoSize;     // sizeof(BlockInfo)
    /*48*/ u32   boUnkData2Info;       // bank-offset of BlockInfo struct for ??

    /*4C*/ u32   collisionMapInfoSize; // sizeof(BlockInfo)
    /*50*/ u32   boCollisionMapInfo;   /* bank-offset of BlockInfo struct for collision data
                                          the collision map is a u16 array, parallel to the tile map array */

    /*54*/ u32   unk54;                // unknown data
    /*58*/ u32   unk58;                // unknown data
    /*5C*/ u32   unk5C;                // unknown data
    /*60*/ u32   unk60;                // unknown data
};

struct ObjectA_0001 // only used for yoshi
{
    /*00*/ struct ObjectA head;
    /*04*/ u8  unk04;
    /*08*/ u32 unk08;
    /*18*/ u16 unk18;
    /*1C*/ u8  unk1C;
    /*1D*/ u8  unk1D;
    /*20*/ u32 boUnk20;
    /*24*/ u32 boUnk24;
    /*28*/ u32 boUnk28;
    /*2C*/ u32 unk2C;
    /*30*/ u32 boUnk30;
    /*34*/ u32 unk34;
    /*38*/ u32 unk38;
    /*3C*/ u32 unk3C;
    /*40*/ u32 boUnk40;
};

struct ObjectA_0002
{
    /*00*/ struct ObjectA head;
    /*04*/ u8 useOverlay; // 1 if asmInfo.overlayInfo is to be used
           u8 _pad05[3];

    /*08*/ union AsmInfo asmInfo;

    /*08   asmInfo.nativeFunc
      08   asmInfo.overlayInfo.romStart
      0C   asmInfo.overlayInfo.romEnd
      10   asmInfo.overlayInfo.fakeMemStart
      14   asmInfo.overlayInfo.fakeMemEnd */
};

struct TileDimensions
{
    /*00*/ u16 unk00;      // ?? related to width
    /*02*/ u16 unk02;      // ?? related to height
    /*04*/ u16 tileWidth;  // width of an individual tile
    /*06*/ u16 tileHeight; // height of an individual tile
    /*08*/ u16 mapWidth;   // width of the whole map (num tiles X * tileWidth)
    /*0A*/ u16 mapHeight;   // height of the whole map (num tiles Y * tileHeight)
};

struct BlockInfo
{
    /*00*/ u32 size;    // decoded block size
    /*04*/ u32 sizeEnc; // encoded block size
    /*08*/ u32 boData;  /* bank-offset of the data (may be a CMPR or raw)
                           if the data is raw, both size and sizeEnc will be the same value */
};

#pragma scalar_storage_order default

#endif // _YS_STRUCTS_H_

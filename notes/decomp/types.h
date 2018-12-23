#ifndef TYPES_H
#define TYPES_H


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef char s8;
typedef short s16;
typedef int s32;
typedef long long s64;
typedef float f32;
typedef double f64;

// display list command
typedef struct Gfx
{
    u32 w0;
    u32 w1;
} Gfx;

/*
settings to be copied into an s2dex background struct (uObjScaleBg_t)
*/
struct BgSource
{
    /*00*/ void *unk00; // imagePtr
    /*04*/ void *unk04; // pallettePtr ?
    /*08*/ u8  unk08; // fmt
    /*09*/ u8  unk09; // siz
    /*0A*/ u16 unk0A; // imageW
    /*0C*/ u16 unk0C; // imageH
    /*0E*/ u16 unk0E;
    /*10*/ s32 unk10; // imageX
    /*14*/ s32 unk14; // imageY
    /*18*/ u16 unk18;
    /*1A*/ u16 unk1A;
    /*1C*/ s16 unk1C; // frameX
    /*1E*/ s16 unk1E; // frameY
    /*20*/ s32 unk20; // imageX_2
    /*24*/ s32 unk24; // imageY_2
    /*28*/ f32 unk28;
    /*2C*/ f32 unk2C;
    /*30*/ s32 unk30;
    /*34*/ s32 unk34;
    /*38*/ u8  unk38;
    // 39 3a 3b
    /*3C*/ s32 unk3C;
    /*40*/ s32 unk40;
};


/*
used for storing s2dex background structs (uObjScaleBg_t) inline with the display list
"branch" should be filled with a branch command that skips over the non-display list data
*/
struct InlineBgGfx
{
    Gfx branch;
    struct uObjScaleBg_t bg;
};

struct UnkStruct1 {
    struct InlineBgGfx *inlineBg;
};

struct SomeCopySettings
{
    int16_t unk00;
    int16_t unk02;
};

#endif

///////////////////////////

#include "s2dex.h"
#include "types.h"
#include <stdint.h>

/*
8006F560
SMSR00 decompressor function
very similar format to MIO0, but the control bits and length-offset pairs aren't stored in separate sections
*/
void smsr00_decode(uint8_t *src, uint8_t *dst)
{
    uint8_t *endPtr = dst + *(uint32_t*)(src + 0x08); //t8
    uint8_t *dataPtr = src + *(uint32_t*)(src + 0x0C); //t9

    src += 0x10;

    int numCtrlBits = 0; // num ctrl bits
    int ctrlBits;

    while(dst < endPtr)
    {
        if(numCtrlBits == 0)
        {
            ctrlBits = *(int16_t*) src; // load control bits
            numCtrlBits = 0x10;
            src += 2;
            ctrlBits <<= numCtrlBits; // ?
        }

        if(ctrlBits >= 0) // check if top bit is set
        {
            *dst++ = *dataPtr++;
        }
        else
        {
            uint16_t pair = *(uint16_t*) src;
            src += 2;

            int length = (pair >> 12) + 3;
            int offset = (pair & 0x0FFF) - 1;
            uint8_t *dstWindowPtr = dst - offset;

            while(length--)
            {
               *dst++ = *dstWindowPtr++;
            }
        }

        ctrlBits <<= 1;
        numCtrlBits--;
    }
}

// 8007D5E0
void dl_push_background(struct BgSource *bgSrc, struct UnkStruct1 *unk1)
{
    // sp14 = s0
    // s0 = a0
    // sp1c = ra
    // sp18 = s1
    // sp9c = a1
    // t6 = sp9c
    // t8 = 0x06010000
    // at = 1

    struct InlineBgGfx *inlineBg; // t7
    uObjScaleBg_t *bg; // s1

    inlineBg = unk1->inlineBg;
    void *sp94 = inlineBg;

    bg = &inlineBg->bg;
    inlineBg->branch.w1 = (char*)bg + sizeof(uObjScaleBg_t);
    inlineBg->branch.w0 = 0x06010000;

    sp94 = (char*)bg + sizeof(uObjScaleBg_t);

    bg->imageX = (bgSrc->unk10 << 5) + bgSrc->unk20;
    bg->imageW = (bgSrc->unk0A << 2);
    bg->frameX = (bgSrc->unk1C << 2);

    bg->imageY = (bgSrc->unk14 << 5) + bgSrc->unk24;
    bg->imageH = (bgSrc->unk0C << 2);
    bg->frameY = (bgSrc->unk1E << 2);

    bg->imagePtr = bgSrc->unk00;
    bg->imageLoad = G_BGLT_LOADBLOCK; // 0x33
    // 688
    bg->imageFmt = bgSrc->unk08;
    bg->imagePal = 0;
    bg->imageFlip = 0;
    bg->imageSiz = bgSrc->unk09;

    // 6A0
    //...
}

///////////////////////////

void some_copy(uint32_t* dst, int16_t *a1, uint32_t *src, struct SomeCopySettings *a3)
{
    int16_t t2 = a3->unk00; // s16
    int16_t t3 = *a1;
    int16_t t1 = a3->unk02; // dst size

    uint32_t *v0 = dst; // dst
    uint32_t *v1 = src; // src

    uint32_t *t0 = dst; // dst

    t2 /= 8;
    t3 /= 4;

    int t4 = 0; // outerCount bb40

    if(t1 <= 0)
    {
        return;
    }

    int a1_2 = t3 * 4; // bb44

    _8006BB48:
    int a0 = 0; // bb4c innerCount
    if(t2 <= 0) goto _8006BBD4; // bb48

    int a3_2 = t2 & 3; // bb50
    int a2 = a3_2; // bb58
    if(a3_2 == 0) goto _8006BB84; // bb54

    // copy 2 words
    _8006BB5C:
    v0[0] = v1[0];
    v0[1] = v1[1];
    v0 += 2; // 8 bytes
    v1 += 2;
    a0++; // inc innerCount
    if(a2 != a0) goto _8006BB5C; // bb74 loop

    if(a0 == t2)
    {
        goto _8006BBD4;
    }

    // copy 8 words
    _8006BB84:
    v0[0] = v1[0];
    v0[1] = v1[1];
    v0[2] = v1[2];
    v0[3] = v1[3];
    v0[4] = v1[4];
    v0[5] = v1[5];
    v0[5] = v1[6];
    v0[7] = v1[7];
    v0 += 8; // (0x20 bytes)
    v1 += 8; // (0x20 bytes)
    a0 += 4; // inc innerCount
    if(a0 != t2) goto _8006BB84; // bbcc loop

    _8006BBD4:
    t4++; // bbd4 inc outerCount

    _8006BBD8:
    t0 += a1_2;
    v0 = t0;

    if(t4 != t1) goto _8006BB48;
}
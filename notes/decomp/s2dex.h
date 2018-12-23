/*
s2dex notes
Modified version of f3dex for 2d graphics

Commands added to f3dex:

    G_BG_1CYC            0x01 gsSPBgRect1Cyc
    G_BG_COPY            0x02 gsSPBgRectCopy
    G_OBJ_RECTANGLE      0x03 gsSPObjRectangle
    G_OBJ_SPRITE         0x04 gsSPObjSprite
    G_OBJ_MOVEMEM        0x05 ? gsSPObjMatrix / gsSPObjSubMatrix
    G_SELECT_DL          0xb0 gsSPSelectDL / gsSPSelectBranchDL
    G_OBJ_RENDERMODE     0xb1 gsSPObjRenderMode
    G_OBJ_RECTANGLE_R    0xb2 gsSPObjRectangleR
    G_OBJ_LOADTXTR       0xc1 gsSPObjLoadTxtr
    G_OBJ_LDTX_SPRITE    0xc2 gsSPObjLoadTxSprite
    G_OBJ_LDTX_RECT      0xc3 gsSPObjLoadTxRect
    G_OBJ_LDTX_RECT_R    0xc4 gsSPObjLoadTxRectR
    G_RDPHALF_0          0xe4

Commands removed from f3dex:

    gSPViewport
    gSPPerspNormalize
    gSPClipRatio
    gSPMatrix
    gSPInsertMatrix
    gSPPopMatrix
    gSPForceMatrix
    gSPVertex
    gSPModifyVertex
    gSPCullDisplayList
    gSPBranchLessZ*
    gSPSetGeometryMode
    gSPTexture
    gSPClearGeometryMode
    gSPTextureL
    gSP1Triangle
    gSP1Quadrangle
    gSPLineW3D
    gSP2Triangles
    gSPLine3D
    gSPNumLights
    gSPLightColor
    gSPLookAt*
    gDPSetHilite2Tile
    gSPLight
    gSPSetLights[0-7]
    gDPSetHilite1Tile
    gSPFogFactor
    gSPFogPosition
    gSPSprite2DBase
    gSPSprite2DDraw
    gSPSprite2DScaleFlip

---------------------

https://level42.ca/projects/ultra64/Documentation/man/n64man/gsp/gSPObjLoadTxSprite.html
https://level42.ca/projects/ultra64/Documentation/man/n64man/gsp/gSPObjLoadTxtr.html
https://level42.ca/projects/ultra64/Documentation/man/n64man/gsp/gSPObjSprite.html
*/

#define G_BGLT_LOADBLOCK    0x0033
#define G_BGLT_LOADTILE     0xfff4
#define G_BG_FLAG_FLIPS     0x01
#define G_BG_FLAG_FLIPT     0x10

// gsSPObjLoadTxSprite(uObjTxSprite *txsp)

typedef struct {
  uObjTxtr    txtr; // 24 bytes
  uObjSprite    sprite;
} uObjTxSprite;

typedef struct {
  u32   type;   /* Structure identifier (G_OBJLT_TXTRBLOCK) */
  u64   *image; /* Texture source address in DRAM (8-byte alignment) */
  u16   tmem;   /* TMEM word address where texture will be loaded (8-byte word) */
  u16   tsize;  /* Texture size (specified by GS_TB_TSIZE) */
  u16   tline;  /* Texture line width (specified by GS_TB_TLINE) */
  u16   sid;    /* Status ID (multiple of 4: either 0, 4, 8, or 12) */
  u32   flag;   /* Status flag */
  u32   mask;   /* Status mask */
} uObjTxtrBlock_t;     /* 24 bytes */

typedef struct {
  s16 objX;        /* x-coordinate of upper-left corner of OBJ (s10.2) */
  u16 scaleW;      /* Width-direction scaling (u5.10) */
  u16 imageW;      /* Texture width (length in s direction, u10.5)  */
  u16 paddingX;    /* Unused (always 0) */
  s16 objY;        /* y-coordinate of upper-left corner of OBJ (s10.2) */
  u16 scaleH;      /* Height-direction scaling (u5.10) */
  u16 imageH;      /* Texture height (length in t direction, u10.5)  */
  u16 paddingY;    /* Unused (always 0) */
  u16 imageStride; /* Texel wrapping width (In units of 64-bit words) */
  u16 imageAdrs;   /* Texture starting position in TMEM (In units of 64-bit words) */
  u8  imageFmt;    /* Texel format
                      G_IM_FMT_RGBA (RGBA format)
                      G_IM_FMT_YUV (YUV format)
                      G_IM_FMT_CI (CI format)
                      G_IM_FMT_IA (IA format)
                      G_IM_FMT_I  (I format) */
  u8  imageSiz;    /* Texel size
                      G_IM_SIZ_4b (4 bits/texel)
                      G_IM_SIZ_8b (8 bits/texel)
                      G_IM_SIZ_16b (16 bits/texel)
                      G_IM_SIZ_32b (32 bits/texel) */
  u16 imagePal;    /* Position of palette for 4-bit color index texture  (4-bit precision, 0~7)  */
  u8  imageFlags;  /* Display flag
                (*) More than one of the following flags can be specified as the bit sum of the flags: 
                      0 (Normal display (no inversion))
                      G_OBJ_FLAG_FLIPS (s-direction (x) inversion)
                      G_OBJ_FLAG_FLIPT (t-direction (y) inversion)  */
} uObjSprite_t;    /* 24 bytes */


// gsSPBgRect1Cyc(         uObjBg *bg)

typedef struct  {
/*00*/    u16 imageX;     // X coordinate at upper-left position of BG image  (u10.5)
/*02*/    u16 imageW;     // BG image width 					(u10.2)
/*04*/    s16 frameX;     // Upper-left position of transfer frame		(s10.2)
/*06*/    u16 frameW;     // Transfer frame width		                (u10.2)
/*08*/    u16 imageY;     // Y coordinate at upper left position of BG image	(u10.5)
/*0A*/    u16 imageH;     // BG image height			                (u10.2)
/*0C*/    s16 frameY;     // Upper-left position of transfer frame	        (s10.2)
/*0E*/    u16 frameH;     // Transfer frame height		                (u10.2)
   
/*10*/    u64 *imagePtr;  // Texture address at upper-left position of BG image
/*18*/    u16 imageLoad;  // Use LoadBlock or LoadTile?
/*1A*/    u8  imageFmt;   // BG image format		     G_IM_FMT_*
/*1B*/    u8  imageSiz;   // BG image size	             G_IM_SIZ_*
/*1C*/    u16 imagePal;   // Pallette number
/*1E*/    u16 imageFlip;  // Flip image with horizontal flip G_BG_FLAG_FLIPS
                          // Up to this point is shared by uObgScaleBg_t
                          // Since the following are set in the initialization routin
                          // guS2DInitBg() they do not need to be set by the user
/*20*/    u16 tmemW;      // TMEM width Word size for frame 1 line
                          // When LoadBlock 	GS_PIX2TMEM(imageW/4,imageSiz)
                          // When LoadTile 	GS_PIX2TMEM(frameW/4,imageSiz)+1 
/*22*/    u16 tmemH;      // Quadruple TMEM height(s13.2) which can be loaded at once                    // When normal texture 512/tmemW*4
                          // When CI Texture 	256/tmemW*4
/*24*/    u16 tmemLoadSH; // SH value
                          // When LoadBlock  	tmemSize/2-1
                          // When LoadTile 	tmemW*16-1
/*26*/    u16 tmemLoadTH; // TH value or Stride value 
                          // When LoadBlock 	GS_CALC_DXT(tmemW)
                          // When LoadTile  	tmemH-1
/*28*/    u16 tmemSizeW;  // imagePtr skip value for one line of image 1
                          // When LoadBlock 	tmemW*2
                          // When LoadTile  	GS_PIX2TMEM(imageW/4,imageSiz)*2
/*2A*/    u16 tmemSize;   // imagePtr skip value for one load iteration
                          // = tmemSizeW*tmemH
} uObjBg_t;         // 40 bytes

typedef	struct	{
/*00*/  u16 imageX;      /* x-coordinate of upper-left position of texture (u10.5) */ 
/*02*/  u16 imageW;      /* Texture width (8-byte alignment, u10.2) */
/*04*/  s16 frameX;      /* x-coordinate of upper-left position of transfer destination frame (s10.2) */
/*06*/  u16 frameW;      /* Transfer destination frame width (u10.2) */
/**/
/*08*/  u16 imageY;      /* y-coordinate of upper-left position of texture (u10.5) */ 
/*0a*/  u16 imageH;      /* Texture height (u10.2) */
/*0c*/  s16 frameY;      /* y-coordinate of upper-left position of transfer destination  frame (s10.2) */
/*0e*/  u16 frameH;      /* Transfer destination frame height (u10.2) */
/**/
/*10*/  u64 *imagePtr;   /* Address of texture source in DRAM */
/*14*/  u16 imageLoad;   /* Method for loading the BG image texture
                          G_BGLT_LOADBLOCK (use LoadBlock)
                          G_BGLT_LOADTILE (useLoadTile) */
/*16*/  u8  imageFmt;    /* Texel format
                          G_IM_FMT_RGBA (RGBA format)
                          G_IM_FMT_YUV (YUV format)
                          G_IM_FMT_CI (CI format)
                          G_IM_FMT_IA (IA format)
                          G_IM_FMT_I (I format) */
/*17*/  u8  imageSiz;    /* Texel size
                          G_IM_SIZ_4b (4 bits/texel)
                          G_IM_SIZ_8b (8 bits/texel)
                          G_IM_SIZ_16b (16 bits/texel)
                          G_IM_SIZ_32b (32 bits/texel) */
/*18*/  u16 imagePal;    /* Position of palette for 4-bit color
                          index texture (4-bit precision, 0~15) */
/*1a*/  u16 imageFlip;   /* Image inversion on/off (horizontal
                          direction only)
                          0 (normal display (no inversion))
                          G_BG_FLAG_FLIPS (horizontal inversion of texture image) */
/*1c*/  u16 scaleW;      /* x-direction scale value (u5.10) */
/*1e*/  u16 scaleH;      /* y-direction scale value (u5.10) */
/*20*/  s32 imageYorig;  /* image drawing origin (s20.5) */
/*24*/  u8  padding[4];  /* Padding */
} uObjScaleBg_t;   /* 40 bytes */

typedef union {
  uObjBg_t       b;
  uObjScaleBg_t  s;
  long long int  force_structure_alignment;
} uObjBg;


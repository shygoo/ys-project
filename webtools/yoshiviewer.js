// ra: ROM Address
// bo: Bank Offset

function getXY(mouseEvent)
{
    var target = mouseEvent.target;
    var rect = target.getBoundingClientRect();
    var style = getComputedStyle(target);
    var styleWidth = parseInt(style.width);
    var styleHeight = parseInt(style.height);
    var ratioX = (styleWidth / target.width);
    var ratioY = (styleHeight / target.height);
    var x = ((mouseEvent.clientX - rect.x) / ratioX) | 0;
    var y = ((mouseEvent.clientY - rect.y) / ratioY) | 0;
    return { x: x, y: y };
}

function YV(canvasSelector)
{
    this.romDV;
    this.objectPosDV;
    this.tileImages; // array of ImageData
    this.loadedResources = {};
    this.domCanvas = document.querySelector(canvasSelector);
    this.ctx = this.domCanvas.getContext('2d');

    this.domCanvas.onclick = function(e)
    {
        var coords = getXY(e);
        console.log((coords.x/8|0)*8, (coords.y/8|0)*8);
    }
}

YV.ci8ToImageData = function(imageDV, imageDVOffs, paletteDV, paletteDVOffs, width, height)
{
    var numInputBytes = width * height;

    const CONV = 255 / 0x1F;
    var outputU8 = new Uint8ClampedArray(numInputBytes * 4);

    for(var i = 0; i < numInputBytes; i++)
    {
        var ci = imageDV.getUint8(imageDVOffs + i);
        var color16 = paletteDV.getUint16(paletteDVOffs + ci * 2);

        var r = (((color16 >> 11) & 0x1F) * CONV) | 0;
        var g = (((color16 >> 6) & 0x1F) * CONV) | 0;
        var b = (((color16 >> 1) & 0x1F) * CONV) | 0;
        var a = (color16 & 1) * 255;

        if(a == 0)
        {
            r = 255; g = 0; b = 0; a = 1;
        }

        //var a = 255;

        outputU8[i*4 + 0] = r;
        outputU8[i*4 + 1] = g;
        outputU8[i*4 + 2] = b;
        outputU8[i*4 + 3] = a;
    }

    return new ImageData(outputU8, width, height);
}
/*
YV.ci8ToImageDataFlipV = function(imageDV, imageDVOffs, paletteDV, paletteDVOffs, width, height)
{
    var numInputBytes = width * height;
    
    const CONV = 255 / 0x1F;
    var outputU8 = new Uint8ClampedArray(numInputBytes * 4);

    for(var i = 0; i < numInputBytes; i++)
    {
        var ci = imageDV.getUint8(imageDVOffs + i);
        var color16 = paletteDV.getUint16(paletteDVOffs + ci * 2);

        var r = (((color16 >> 11) & 0x1F) * CONV) | 0;
        var g = (((color16 >> 6) & 0x1F) * CONV) | 0;
        var b = (((color16 >> 1) & 0x1F) * CONV) | 0;
        var a = (color16 & 1) * 255;

        if(a == 0)
        {
            r = 255; g = 0; b = 0; a = 1;
        }

        //var a = 255;

        outputU8[i*4 + 0] = r;
        outputU8[i*4 + 1] = g;
        outputU8[i*4 + 2] = b;
        outputU8[i*4 + 3] = a;
    }

    return new ImageData(outputU8, width, height);
}*/

YV.ENTITY_INFO = {
    0x4001: ['#0F0', 'yoshi'],
    0x4030: ['#F00', 'apple'],
    0x4031: ['#FF0', 'banana'],
    0x4032: ['#0F0', 'watermelon'],
    0x4033: ['#F0F', 'grapes'],
    0x403a: ['#0FF', 'shyguy'],
    0x406F: ['#FF0', 'coin'],
    0x4086: ['#AFA', 'egg box'],
    0x40b8: ['#F00', 'surprise ball'],
    0x40c3: ['#777', 'fence'],
    0x4199: ['#0FF', 'unknown'],
    0x419c: ['#0FF', 'shyguy 2'],
    0x41D1: ['#FAA', 'apple bubble'],
    0x41d2: ['#FFA', 'banana bubble'],
    0x41d3: ['#AFA', 'watermelon bubble'],
    0x41d5: ['#AFA', 'melon bubble'],
    0x41e8: ['#AFA', 'path split right'],
    0x41ea: ['#AFA', 'path split left'],
    0x4208: ['#AFA', 'jar'],
    0x4507: ['#F1F', 'miss warp 1'],
    0x4508: ['#F1F', 'miss warp 2'],
    0x4536: ['#AAA', 'pakederm?'],
    0x45f4: ['#FFF', 'tip box'],
    0x45bc: ['#AFA', 'melon spawner'],
    0x45bd: ['#AFA', 'melon activator'],
    0x4686: ['#FA0', 'flower'],
    0x4684: ['#FFF', 'other box'],
    0x46a8: ['#AFA', 'watermelon bubble 2'],
    0x417f: ['#FF0', 'hidden shyguy'],
    0x4732: ['#AAF', 'unknown'],
    0x8067: ['#FFF', 'level 1 terrain'],
    0x4147: ['#FFF', 'start'],
    0x414A: ['#FFF', 'goal'],
    0x473d: ['#FFF', 'secret coin'] 
};

const TileDimensions = {
    unk00:      U16,
    unk02:      U16,
    tileWidth:  U16, // width of an individual tile
    tileHeight: U16, // height of an individual tile
    mapWidth:   U16, // number of horizontal tiles * tileWidth
    mapHeight:  U16  // number of vertical tiles * tileHeight
    // bg: 0100 0100 0010 0010 1A00 0200
    // apple: 0018 0015 0018 0015 0018 00BD
    // watermelon: 0018 0015 0018 0015 0018 00BD
};

const ResourceA = {
    unk00:               U32,
    // 01000000 = flip?
    unk04:               U32, // 00000000 bg layers, 01000000 fruits, coin 00000000 (sprite/bg drawing mode?)
    bhvInitFunc:         U32, // bg 8006E548, fruit 00CAFDD0
    unk0C:               U32,
    unk10:               U32,
    unk14:               U32,
    resno:               U16, // redundant resource number
    unk1A:               U16, // padding?
    tileDimensionsSize:  U32, // sizeof(TileDimensions)
    boTileDimensions:    U32, // bank-offset -> TileDimensions (tile width/height & tilemap width/height)
    tileDataInfoSize:    U32, // sizeof(BlockInfo)
    boTileDataInfo:      U32, // bank-offset -> BlockInfo struct -> color index data for all tiles
    tilePaletteInfoSize: U32, // sizeof(BlockInfo)
    boTilePaletteInfo:   U32, // bank-offset -> BlockInfo struct -> RGB5551 color palette
    tileIndecesInfoSize: U32, // sizeof(BlockInfo)
    boTileIndecesInfo:   U32, // bank-offset -> BlockInfo struct -> tilemap (u16 array of tile indeces)
    unk2Size:            U32,
    boUnk2:              U32,
    // uknown ptr (00000034 00000034 03271B08):
    // 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
    // 10 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F
    // 20 21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F
    // 30 31 32 33
    unk3Size: U32,
    boUnk3:   U32,  // optional? uknown ptr
    collisionInfoSize:   U32, 
    boCollisionInfo:     U32,  // optional? uknown ptr (00006800 00000C96 03270E6C)
    unk54:    0x10
};

const ResourceB = {
    // 05000100 43FA4000 00000000 00000000 00000000 3F800000 3F800000 3F800000 08000000 00000000 00000D00 01000000 00000000 0302418C 00000000 00000018 00000000 000000C8 00000000 00000000 01000000
    // 05000100 44162000 00000000 00000000 00000000 3F800000 3F800000 3F800000 08000000 00000000 00000900 00800000 00000000 030241E0 00000000 00000018 00000000 0000FF9C 00000000 00000000 01000000
    // 05000100 442F2000 00000000 00000000 00000000 3F800000 3F800000 3F800000 08000000 00000000 00000C00 01000000 00000000 03024234 00000000 00000018 00000000 00000000 00000000 00000000 01000000
    
    // apple/watermelon:
    // 00010800 43FA30A4 00000000 00000000 00000000 3F800000 3F800000 3F800000 0AFFFFFF FF000000 00000000 00000100 00000000 00000000 00000000
    _pad00: 0x34,
    unk34: U32 // ptr to struct of 0x18 bytes? 00000018 00000000 00000000 00000000 00000000 01000000
};

const BlockInfo = {
    size: U32,    // decoded block size
    sizeEnc: U32, // encoded block size
    boBlock: U32  // bank-offset of the block (may be CMPR or raw)
};

const ResourceHeader = {
    resno: U16, // resource number
    unk02: U16, // padding, probably
    boResourceA: U32, // bank offset of resource A struct
    boResourceB: U32, // bank offset of resource B struct
};

const ObjectPlacementListInfo = {
    numObjects: U16,
    unk02: U16, // padding probably
    boObjectPlacements: U32
};

const ObjectPlacement = {
    resno: U16,
    layer: U16,
    x: F32,
    y: F32
};

const LevelEntry = {
    unk00: U32,
    boLevelInfo: U32
};

const LevelInfo = {
    unk00: 0x5C,
    boObjectPlacementListInfoPtr: U32

    /*
    00000000
    00000000
    43FA0000 // 500.0f
    00000000
    00000000
    00000000
    00000000
    00000000
    00000000
    8006CF04
    00000000
    43880000 // 272.0f
    43FA0000 // 500.0f
    00000000
    3F800000 // 1.0f
    3F800000 // 1.0f
    00000000
    4601B000
    43FA0000 // 500.0f
    44BB8000 // 1500.0f
    00000000
    43F00000 // 480.0f
    01010000
    0400A708 // 0x5C: boObjectLayoutData

    4002 4003 4004 4006 4007 4008 4009 4005 // objects to preload?
    400A 400B 400C 400D 400E 4035 400F 4010
    4011 4012 4013 4030 4031 4032 4033 4034
    4014 4015 4016 4017 4018 4019 401A 401B
    401C 401D 401F 401E 4020 40F2 4021 4022
    4023 402C 4088 4024 460C 460D 4025 4026
    4027 4035 473B 4738 4736 40B1 4070 46F4
    45D7 41DB 45A5 45CB 45A9 4733 41CE 4146
    465E 465F 4660 4661 4662 4663 4664 453B
    4590 4537 4565 FFFF

    00000000
    00000000
    00000001
    0000003E
    60000000
    8005A150
    00010000
    */
};

////////////////////

const RA_RESOURCE_LIST = 0x000A1C90;
const RA_RESOURCE_LIST_END = 0x000A1C90 + 0x4A28;
const RA_BANKS_TABLE = 0x000A79D4; 

YV.prototype.setRom = function(romAB)
{
    this.romDV = new DataView(romAB);
    this.rom = new Memory(romAB);
}

YV.prototype.bankOffsetToAddr = function(bankOffset)
{
    // 00: 00001060, 01: 00000000, 02: 00000000, 03: 00526EC0, 04: 00B47A10
    var bank = bankOffset >> 24;
    var offset = bankOffset & 0x00FFFFFF;
    return this.rom.u32[RA_BANKS_TABLE + bank*4] + offset;
}

YV.prototype.boStruct = function(bankOffset, layout)
{
    // create struct from bank-offset address
    var ra = this.bankOffsetToAddr(bankOffset);
    return this.rom.struct(ra, layout);
}

YV.prototype.loadBlock = function(blockInfo)
{
    // assume its pointing to a CMPR:SMSR00 block if size > sizeEnc
    var raBlock = this.bankOffsetToAddr(blockInfo.boBlock);

    var dv = (blockInfo.size > blockInfo.sizeEnc) ?
        smsr00_decode(this.rom.dv, raBlock + 0x10) :
        new DataView(this.rom.ab.slice(raBlock, raBlock + blockInfo.size));

    return dv;
}

YV.prototype.unloadResources = function()
{
    this.loadedResources = {};
}

YV.prototype.loadResource = function(resno)
{
    if(resno in this.loadedResources)
    {
        return this.loadedResources[resno];
    }

    for(var raEntry = RA_RESOURCE_LIST; raEntry < RA_RESOURCE_LIST_END; raEntry += 0x0C)
    {
        var header = this.rom.struct(raEntry, ResourceHeader);

        if(header.resno != resno)
        {
            continue;
        }

        var structA = this.boStruct(header.boResourceA, ResourceA)
        var structB = this.boStruct(header.boResourceB, ResourceB)

        var tileDimensions = this.boStruct(structA.boTileDimensions, TileDimensions)
        var tileDataBlockInfo = this.boStruct(structA.boTileDataInfo, BlockInfo);
        var tilePaletteBlockInfo = this.boStruct(structA.boTilePaletteInfo, BlockInfo);
        var tileIndecesBlockInfo = this.boStruct(structA.boTileIndecesInfo, BlockInfo);
        //var unk2 = structA.boUnk2;

        console.log(resno.hex(4) + ' ' + (resno in YV.ENTITY_INFO ? YV.ENTITY_INFO[resno][1]:''));
        console.log("structA:\n" + structA.__prettyPrint())
        console.log("tileDimensions:\n" + tileDimensions.__prettyPrint())
        console.log("structB:\n" + structB.__prettyPrint())

        var tileDataDV = this.loadBlock(tileDataBlockInfo);
        var paletteDV = this.loadBlock(tilePaletteBlockInfo);
        var tileIndecesDV = this.loadBlock(tileIndecesBlockInfo);
        var collisionDV = null;

        if(structA.unk2Size != 0)
        {
            var addr = this.bankOffsetToAddr(structA.boUnk2);
            console.log("unk2: " + addr.hex())

            // apple      030089AC -> 0052F86C: 00010000 0000001A 03008990
            //  03008990 -> 0052F850: 00000000 0000000A 000A 000A 0000 0000 0000 0000 2422 2444 01C2 0000
            // watermelon 030089FC -> 0052F8BC: 00010000 0000001A 030089E0
            //  030089E0 -> 0052F8A0: 00000000 0000000A 000A 000A 0000 0000 0000 0000 4222 2244 01C2 0000
            // no noticeable difference when swapped
        }

        if(structA.unk3Size != 0)
        {

        }

        if(structA.collisionInfoSize != 0)
        {
            var collisionBlockInfo = this.boStruct(structA.boCollisionInfo, BlockInfo);
            if(resno == 0x8067)
            {
                collisionDV = this.loadBlock(collisionBlockInfo);
            }

            console.log("collisionBlockInfo:\n", collisionBlockInfo.__prettyPrint());
        }

        var dv = this.romDV;

        var tileImages = [];
        var tileWidth = tileDimensions.tileWidth;
        var tileHeight = tileDimensions.tileHeight;
        var numBytesPerTile = (tileWidth * tileHeight);
        var numTiles = tileDataDV.byteLength / numBytesPerTile;

        // todo turn tilemap into one canvas her

        for(var tileIndex = 0; tileIndex < numTiles; tileIndex++)
        {
            var tileOffs = tileIndex * numBytesPerTile;
            var imageData = YV.ci8ToImageData(tileDataDV, tileOffs, paletteDV, 0, tileWidth, tileHeight);
            tileImages.push(imageData);
        }

        this.loadedResources[resno] = {
            tileDataDV: tileDataDV,
            paletteDV: paletteDV,
            tileIndecesDV: tileIndecesDV,
            collisionDV: collisionDV,
            tileImages: tileImages,
            dimensions: tileDimensions,
            _resA: structA,
            _resB: structB
        };

        return this.loadedResources[resno];
    }

    return null;
}


YV.prototype.loadLevel = function(levelNum)
{
    var dv = this.romDV;

    //var levelNum = 0x2B; // 2b = first level

    var raLevelEntry = 0x000A84A0 + (levelNum * 8);
    var levelEntry = this.rom.struct(raLevelEntry, LevelEntry);
    var levelInfo = this.boStruct(levelEntry.boLevelInfo, LevelInfo);
    
    // pointer to pointer
    var raObjectPlacementListInfoPtr = this.bankOffsetToAddr(levelInfo.boObjectPlacementListInfoPtr);
    var boObjectPlacementListInfo = this.rom.u32[raObjectPlacementListInfoPtr];

    this.objectPlacementListInfo = this.boStruct(boObjectPlacementListInfo, ObjectPlacementListInfo);

    //console.log(this.objectPlacementListInfo.__prettyPrint())
}

YV.prototype.renderObjects = function()
{
    var boStart = this.objectPlacementListInfo.boObjectPlacements;
    var boEnd = boStart + this.objectPlacementListInfo.numObjects * 12;

    for(var i = boEnd - 12; i >= boStart; i -= 12)
    {
        var obj = this.boStruct(i, ObjectPlacement);

        this.drawResource(obj.resno, obj.x, obj.y);

        var label = obj.resno.hex(4);
        var fill = '#FFF';

        if(obj.resno in YV.ENTITY_INFO)
        {
            fill = YV.ENTITY_INFO[obj.resno][0];
            label += ' ' + YV.ENTITY_INFO[obj.resno][1];
        }

        this.ctx.strokeStyle = fill;
        this.ctx.fillStyle = fill;
        this.ctx.lineWidth = 1;

        var textDim = this.ctx.measureText(label);
        console.log("textdim", textDim)
        this.ctx.fillStyle = "rgba(0,0,0,0.7)";
        this.ctx.fillRect((obj.x|0)-1, (obj.y|0)-9, textDim.width+2, 10);

        this.ctx.fillStyle = fill;
        this.ctx.fillText(label, (obj.x|0), (obj.y|0));
        this.ctx.strokeRect((obj.x|0)-8 + 0.5, (obj.y|0)-8 + 0.5, 16, 16);
        this.ctx.fillRect((obj.x|0), (obj.y|0), 1, 1);
    }
}

YV.prototype.clearCanvas = function()
{
    this.ctx.fillStyle = "#555";
    this.ctx.fillRect(0, 0, 5000, 5000);
}

YV.prototype.drawResource = function(resno, x, y)
{
    //console.log(resno.hex(4))

    switch(resno)
    {
    case 0x8067:
    case 0x80B9:
    case 0x80B8:
    case 0x4030:
    case 0x4031:
    case 0x4032:
    case 0x4033:
    case 0x406F:
    case 0x403A:
    case 0x4086:
    case 0x4199:
    case 0x419C:
    case 0x45F4:
    case 0x4507:
    case 0x4508:
    case 0x40B8:
    case 0x4686:
    case 0x4684:
    case 0x4208:
    case 0x417F:
    case 0x4147: // pole?
    case 0x414A: // pole?
    //case 0x41E8: crash
    //case 0x41EA: crash
    //case 0x414F: crash
    case 0x473D: // hidden coins
    case 0x40c3:
    //case 0x45BD: melon spawner activator
    //case 0x4732: crash
    //case 0x4536:
    //case 0x41D3:
    //case 0x4001:
        break;
    default:
        return;
    }

    var res = this.loadResource(resno);
    //var numTileIndeces = (res.tileIndecesDV.byteLength / 2);
    //console.log(numTileIndeces);

    //console.log(resno.hex(2), res)
    //console.log(this.bankOffsetToAddr(res._resA.boUnk2).hex())

    var numTilesX = res.dimensions.mapWidth / res.dimensions.tileWidth;
    var numTilesY = res.dimensions.mapHeight / res.dimensions.tileHeight;
    var numTileIndeces = numTilesX * numTilesY;

    var tileWidth = res.dimensions.tileWidth;
    var tileHeight = res.dimensions.tileHeight;

    var tCanvas = document.createElement('canvas');
    tCanvas.width = res.dimensions.mapWidth;
    tCanvas.height = res.dimensions.mapHeight;
    var tctx = tCanvas.getContext('2d');

    var tCanvas2 = document.createElement('canvas');
    tCanvas2.width = res.dimensions.tileWidth;
    tCanvas2.height = res.dimensions.tileHeight;
    var tctx2 = tCanvas2.getContext('2d');
    tctx2.translate(0, tCanvas2.height);
    tctx2.scale(1, -1)

    var numTilesX = 0;
    var numTilesY = 0;

    // where do these numbers come from?
    // numbers in the dimensions struct don't always seem to match
    switch(resno)
    {
        case 0x80B9: numTilesX = 128; numTilesY = 32; break;
        case 0x80B8: numTilesX = 48; numTilesY = 16; break;
        case 0x8067: numTilesX = 416; numTilesY = 32; break;
    }

    if(resno == 0x8067 || resno == 0x80B9)
    {
        for(var i = 0; i < res.tileIndecesDV.byteLength / 2; i++)
        {
            var tileIndex = res.tileIndecesDV.getUint16(i*2);
            var row = (i / numTilesX) | 0;
            var col = i % numTilesX;
            var x = col * tileWidth;
            var y = ((row/2)|0) * tileHeight;  // why?
    
            if(row & 1) y += (numTilesY * tileHeight) / 2; // why?
    
            tctx.putImageData(res.tileImages[tileIndex], x, y);

            // check for collision data
            if(res.collisionDV != null)
            {
                var tileCollisionAttributes = res.collisionDV.getUint16(i*2);
                //console.log(tileCollisionAttributes.hex(4))
                if(tileCollisionAttributes != 0)
                {
                    switch(tileCollisionAttributes >> 8)
                    {
                        case 0x07: tctx.fillStyle = 'rgba(255, 0, 0, 0.5)'; break;
                        case 0x06: tctx.fillStyle = 'rgba(255, 0, 255, 0.5)'; break;
                        case 0x2F: tctx.fillStyle = 'rgba(0, 0, 255, 0.5)'; break;
                        default:
                            tctx.fillStyle = 'rgba(255, 255, 255, 0.5)'; break;
                    }

                    tctx.fillRect(x, y, 16, 16);
                    tctx.fillRect(x+7, y+7, 2, 2);
                }
            }
        }

        this.ctx.drawImage(tCanvas, 0, 0);
    }

    // interlaced for some reason
    if(resno == 0x80B9)
    {

        for(var i = 0; i < res.tileIndecesDV.byteLength / 2; i++)
        {
            var tileIndex = res.tileIndecesDV.getUint16(i*2);
            var row = (i / numTilesX) | 0;
            var col = i % numTilesX;
            var x = col * tileWidth;
            var y = ((row/2)|0) * tileHeight;  // why?

            if(row & 1) y += (numTilesY * tileHeight) / 2; // why?

            tctx.putImageData(res.tileImages[tileIndex], x, y);
            // check for collision data
        }
        
        for(var j = 0; j < 4; j++)
        {
            this.ctx.drawImage(tCanvas, 0+j*0x800, 0);
        }
    }
    else if(resno == 0x80B8) // y offset by 256 for some reason
    {
        for(var j = 0; j < 10; j++)
        {
            //console.log('80B8', res.dimensions.__prettyPrint())
            for(var i = 0; i < res.tileIndecesDV.byteLength / 2; i++)
            {
                var tileIndex = res.tileIndecesDV.getUint16(i*2);
                var row = (i / numTilesX) | 0;
                var col = i % numTilesX;
                var x = col * tileWidth;
                var y = row * tileHeight;
            
                y += 256; // why?
            
                tctx.putImageData(res.tileImages[tileIndex], 0, 0);
                this.ctx.drawImage(tCanvas, x+j*768, y);
            }
        }

    }
    else if(resno >= 0x4030 && resno <= 0x4033)
    {
        var idx = (resno - 0x4030) + 3
        tctx.putImageData(res.tileImages[idx], 0, 0); // how is the index selected?
        tctx2.drawImage(tCanvas, 0, 0);
        this.ctx.drawImage(tCanvas2, x-12, y-10);
    }
    else if(resno == 0x4086) // egg box
    {
        // incorrect palette is being loaded
        tctx.putImageData(res.tileImages[1], 0, 0); // how is the index selected?
        tctx2.drawImage(tCanvas, 0, 0);
        this.ctx.drawImage(tCanvas2, x-tCanvas2.width/2, y-tCanvas2.height/2);
    }
    else
    {
        tctx.putImageData(res.tileImages[0], 0, 0);

        if(res._resA.unk04 == 0x01000000) // does this actually specify flipping
        {
            // flip it
            tctx2.drawImage(tCanvas, 0, 0);
            this.ctx.drawImage(tCanvas2, x-tCanvas2.width/2, y-tCanvas2.height/2);
        }
        else
        {
            this.ctx.drawImage(tCanvas, x-tCanvas2.width/2, y-tCanvas2.height/2);
        }

    }
}

YV.prototype.render = function()
{
    var start = performance.now();
    this.renderObjects();
    console.log(performance.now() - start)

    this.ctx.fillStyle = "rgba(0, 0, 0, 0.2)"
    for(var i = 0; i < 416; i++)
    {
        this.ctx.fillRect(i*16, 0, 1, 512);
    }

    for(var i = 0; i < 32; i++)
    {
        this.ctx.fillRect(0, i*16, 6656, 1);
    }
}

// 13312 / 2 6656 3328 1664 1024 832
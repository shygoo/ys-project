function smsr00_decode(romDV, romOffset)
{
    var srcOffs = romOffset + 0x10;
    var outputSize = romDV.getUint32(romOffset + 0x08);
    var dataOffs = srcOffs + romDV.getUint32(romOffset + 0x0C);
    
    var dst = new ArrayBuffer(outputSize);
    var dstDV = new DataView(dst);

    var dstOffs = 0;

    var numCtrlBits = 0;
    var ctrlBits;
    
    while(dstOffs < outputSize)
    {
        if(numCtrlBits == 0)
        {
            numCtrlBits = 16;
            ctrlBits = romDV.getUint16(srcOffs);
            srcOffs += 2;
        }

        if(ctrlBits & 0x8000)
        {
            dstDV.setUint8(dstOffs++, romDV.getUint8(dataOffs++));
        }
        else
        {
            var pair = romDV.getUint16(srcOffs);
            srcOffs += 2;

            var length = (pair >> 12) + 3;
            var offset = (pair & 0x0FFF) - 1;
            var windowOffs = (dstOffs - offset) - 2;

            while(length--)
            {
                dstDV.setUint8(dstOffs++, dstDV.getUint8(windowOffs++));
            }
        }

        ctrlBits <<= 1;
        numCtrlBits--;
    }

    return dstDV;
}
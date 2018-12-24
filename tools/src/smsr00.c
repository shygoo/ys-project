#include <stdint.h>
#include "smsr00.h"
#include "bswap.h"

#include <stdio.h>

const char SMSR00_SIG[6] = {'S','M','S','R','0','0'};

size_t smsr00_get_output_size(uint8_t *src)
{
    return BSWAP32(*(uint32_t*)(src + 0x08));
}

void smsr00_decode(uint8_t *src, uint8_t *dst)
{
    size_t outputSize = BSWAP32(*(uint32_t*)(src + 0x08));
    size_t dataOffs = BSWAP32(*(uint32_t*)(src + 0x0C));
    src += 0x10;

    uint8_t *dstEnd = dst + outputSize;
    uint8_t *data = src + dataOffs;

    int numCtrlBits = 0;
    int16_t ctrlBits;

    while(dst < dstEnd)
    {
        if(numCtrlBits == 0)
        {
            ctrlBits = BSWAP16(*(int16_t*) src);
            numCtrlBits = 0x10;
            src += 2;
        }

        if(ctrlBits & 0x8000)
        {
            *dst++ = *data++;
        }
        else
        {
            uint16_t pair = BSWAP16(*(uint16_t*) src);
            src += 2;

            int length = (pair >> 12) + 3;
            int offset = (pair & 0x0FFF) - 1;
            uint8_t *windowPtr = dst - offset - 2;

            while(length--)
            {
               *dst++ = *windowPtr++;
            }
        }

        ctrlBits <<= 1;
        numCtrlBits--;
    }
}

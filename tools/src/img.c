#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"

#include "img.h"

void ci8_to_rgba32(uint32_t *out, uint8_t *ciData, uint16_t *palette, int numPixels)
{
    for(int i = 0; i < numPixels; i++)
    {
        uint8_t ci = ciData[i];
        uint16_t color16 = BSWAP16(palette[ci]);

        uint8_t r = (color16 >> 11) & 0x1F;
        uint8_t g = (color16 >>  6) & 0x1F;
        uint8_t b = (color16 >>  1) & 0x1F;
        uint8_t a = color16 & 1;

        uint32_t color32 = (r << 27) | (g << 19) | (b << 11) | (a * 255);

        out[i] = BSWAP32(color32);
    }
}

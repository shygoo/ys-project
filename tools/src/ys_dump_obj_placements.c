#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BSWAP32(v) ((((v) & 0x000000FF) << 24) | \
                    (((v) & 0x0000FF00) <<  8) | \
                    (((v) & 0x00FF0000) >>  8) | \
                    (((v) & 0xFF000000) >> 24))

#define BSWAP16(v) ((((v) & 0x00FF) << 8) | \
                    (((v) & 0xFF00) >> 8))

struct ObjectPlacement
{
    uint16_t objectId; // object ID
    uint16_t layer;    // seems to be the drawing layer, collision is active on layer 0x0001
    float x;        // x coordinate in level
    float y;        // y coordinate in level
};

int main(int argc, const char *argv)
{
    FILE *fp = fopen("ys.z64", "rb");
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    uint8_t *rom = malloc(size);
    rewind(fp);
    fread(rom, 1, size, fp);
    fclose(fp);

    struct ObjectPlacement *objects = (struct ObjectPlacement *) &rom[0x00B51B4C];

    for(int i = 0; i < 123; i++)
    {
        uint16_t id = BSWAP16(objects[i].objectId);
        uint16_t layer = BSWAP16(objects[i].layer);
        uint32_t x_bits  = BSWAP32(*(uint32_t*)&objects[i].x);
        uint32_t y_bits  = BSWAP32(*(uint32_t*)&objects[i].y);

        printf("place_object(0x%04X, %d, %g, %g)\n", id, layer, *(float*)&x_bits, *(float*)&y_bits);
       // struct ObjectPlacement *obj = (struct ObjectPlacement *) &rom[0x00B51B4C + i * sizeof(struct ObjectPlacement)];
    }
}
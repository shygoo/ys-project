#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "smsr00.h"

int main(int argc, const char *argv[])
{
    FILE *fp = fopen("ys.z64", "rb");
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    uint8_t *rom = malloc(size);
    rewind(fp);
    fread(rom, 1, size, fp);
    fclose(fp);

    char smsr00_magic[] = {'S','M','S','R','0','0'};

    printf("starting...\n");

    for(int i = 0; i < size - sizeof(smsr00_magic); i++)
    {
        if(memcmp(smsr00_magic, &rom[i], sizeof(smsr00_magic)) != 0)
        {
            continue;
        }

        size_t output_size = smsr00_get_output_size(&rom[i]);
        char *out = malloc(output_size);
        smsr00_decode(&rom[i], out);

        char name[32];
        sprintf(name, "%08X.bin", i);
        FILE *fp_out = fopen(name, "wb");
        fwrite(out, 1, output_size, fp_out);
        fclose(fp_out);

        free(out);

        printf("%08X %04X\n", i,  output_size);
    }

    free(rom);
    printf("done\n");
}
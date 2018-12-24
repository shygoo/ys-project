#include "rom.h"

uint8_t *rom_load(rom_t *rom, const char *path)
{
    rom->fp = fopen(path, "rb");
    fseek(rom->fp, 0, SEEK_END);

    rom->size = ftell(rom->fp);
    rom->data = (uint8_t *) malloc(rom->size);

    rewind(rom->fp);
    fread(rom->data, 1, rom->size, rom->fp);
}

void rom_unload(rom_t *rom)
{
    fclose(rom->fp);
    free(rom->data);
}

#ifndef _ROM_H_
#define _ROM_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    FILE *fp;
    size_t size;
    uint8_t *data;
} rom_t;

uint8_t *rom_load(rom_t *rom, const char *path);
void rom_unload(rom_t *rom);

#endif // _ROM_H_

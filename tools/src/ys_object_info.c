#include "rom.h"

int main(int argc, const char *argv[])
{
    rom_t rom;
    rom_load(&rom, "ys.z64");
}
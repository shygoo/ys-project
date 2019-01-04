#include <stdint.h>
#include "rom.h"
#include "mips_disasm.h"
#include "bswap.h"

const char *szSecNames[] = {
    "SEC_UNK",
    "SEC_TEXT",
    "SEC_DATA",
    "SEC_RODATA"
};

const char *szRelTypeNames[] = {
    "R_UNK_00",
    "R_UNK_01",
    "R_32",
    "R_UNK_03",
    "R_26",
    "R_HI16",
    "R_LO16",
    "R_UNK_07",
    "R_UNK_08",
    "R_UNK_09",
    "R_UNK_0A",
    "R_UNK_0B",
    "R_UNK_0C",
    "R_UNK_0D",
    "R_UNK_0E",
    "R_UNK_0F",
};

int main(int argc, const char *argv[])
{
    rom_t rom;
    rom_load(&rom, "ys.z64");

    uint32_t ovlRomStart = 0x00CAFDD0;
    uint32_t ovlRomEnd  = 0x00CB0E70;

    uint32_t ovlFakeMemStart = 0x80573E90;
    uint32_t ovlFakeMemEnd   = 0x80579A40;

    uint32_t ovlSize = 0x00CB0E70 - 0x00CAFDD0;

    uint32_t metaSize = U32_BE(rom.data, ovlRomEnd - sizeof(uint32_t));

    uint8_t *meta = &rom.data[ovlRomEnd - metaSize];

    uint32_t textSize = U32_BE(meta, 0x00);
    uint32_t dataSize = U32_BE(meta, 0x04);
    uint32_t rodataSize = U32_BE(meta, 0x08);
    uint32_t bssSize = U32_BE(meta, 0x0C);
    uint32_t numRelocations = U32_BE(meta, 0x10);

    uint8_t *ovl = &rom.data[ovlRomStart];
    uint8_t *text = ovl;
    uint8_t *data = text + textSize;
    uint8_t *rodata = data + dataSize;

    uint32_t *relocations = (uint32_t *) &meta[0x14];

    //analyse(ovlFakeMemStart, ovl, textSize);
    mips_analysis_t analysis;
    mips_analysis_init(&analysis);
    mips_analysis_run(&analysis, ovlFakeMemStart, text, textSize);
    mips_analysis_free(&analysis);

    printf("// text:\n");

    for(int i = 0; i < textSize; i += 4)
    {
        opcode_t opcode;
        opcode.bits = U32_BE(text, i);
        
        char code[64];
        int res = disasm_opcode(code, ovlFakeMemStart + i, opcode);

        if(mips_analysis_have_jal_target(&analysis, ovlFakeMemStart + i))
        {
            printf("\nfunc_%08X:\n", ovlFakeMemStart + i);
        }

        if(res)
        {
            printf("/*0x%02X*/ %s\n", ovlFakeMemStart + i, code);
        }
        else
        {
            printf("/*0x%02X*/ .dw 0x%08X // unknown opcode\n", ovlFakeMemStart + i, opcode.bits);
        }
        
    }

    printf("\n// data:\n");

    for(int i = 0; i < dataSize; i += 4)
    {
        uint32_t word = U32_BE(data, i);
        printf("/*0x%02X*/ .dw 0x%08X\n", ovlFakeMemStart + textSize + i, word);
    }

    printf("\n// rodata:\n");

    for(int i = 0; i < rodataSize; i += 4)
    {
        uint32_t word = U32_BE(rodata, i);
        printf("/*0x%02X*/ .dw 0x%08X\n", ovlFakeMemStart + textSize + dataSize + i, word);
    }

    printf("\n// meta:\n");
    printf(".dw 0x%08X // textSize\n"
           ".dw 0x%08X // dataSize\n"
           ".dw 0x%08X // rodataSize\n"
           ".dw 0x%08X // bssSize\n"
           ".dw 0x%08X // numRelocations\n\n",
           textSize, dataSize, rodataSize, bssSize, numRelocations);

    printf("// relocations:\n");

    for(uint32_t i = 0; i < numRelocations; i++)
    {
        uint32_t rel = BSWAP32(relocations[i]);
        //printf(".dw 0x%08X\n", rel);

        int sec = rel >> 30;
        int type = (rel >> 24) & 0xF;
        int offs = rel & 0x00FFFFFF;

        printf("ovl_rel %s, %s, 0x%06X\n", szSecNames[sec], szRelTypeNames[type], offs);
    }

    printf("\n");
    printf(".dw 0x00000000\n");
    printf(".align 16\n");
    printf(".org org()-4\n");
    printf(".dw 0x%08X // metaSize\n", metaSize);

    //uint32_t rodataSize = U32_BE(meta, 0x00);
}
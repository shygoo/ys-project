#include <stdio.h>
#include "mips_disasm.h"
#include "rom.h"
#include "bswap.h"

const opcode_entry_t opcodes[] = {
    // op      name     decoder
    { 0b000000, "***",   decode_special }, // use special_opcodes
    { 0b000001, "***",   decode_regimm }, // use regimm_opcodes
    { 0b000011, "jal",   decode_target26 },
    { 0b000100, "beq",   decode_st_offs },
    { 0b000101, "bne",   decode_st_offs },
    { 0b001000, "addi",  decode_ts_imm },
    { 0b001001, "addiu", decode_ts_imm },
    { 0b001010, "slti",  decode_ts_imm },
    { 0b001011, "sltiu", decode_ts_imm },
    { 0b001100, "andi",  decode_ts_imm },
    { 0b001101, "ori",   decode_ts_imm },
    { 0b001111, "lui",   decode_t_imm },
    { 0b010100, "beql",  decode_st_offs },
    { 0b010101, "bnel",  decode_st_offs },
    { 0b100000, "lb",    decode_loadstore },
    { 0b100001, "lh",    decode_loadstore },
    { 0b100011, "lw",    decode_loadstore },
    { 0b100100, "lbu",   decode_loadstore },
    { 0b100101, "lhu",   decode_loadstore },
    { 0b101000, "sb",    decode_loadstore },
    { 0b101001, "sh",    decode_loadstore },
    { 0b101011, "sw",    decode_loadstore },
    { 0b110001, "lwc1",  decode_loadstore_c1 },
    { 0b111001, "swc1",  decode_loadstore_c1 },
    { 0, NULL, NULL}
};

const opcode_entry_t special_opcodes[] = {
    // func   name decoder
    { 0b001000, "jr",   decode_s },
    { 0b100101, "or",   decode_dst },
    { 0b100000, "add",  decode_dst },
    { 0b100001, "addu", decode_dst },
    { 0b100100, "and",  decode_dst },
    { 0b101010, "slt",  decode_dst },
    { 0b101011, "sltu", decode_dst },
    { 0b100010, "sub",  decode_dst },
    { 0b100011, "subu", decode_dst },
    { 0b100110, "xor",  decode_dst },
    { 0, NULL, NULL }
};

const opcode_entry_t regimm_opcodes[] = {
    // regimm  name decoder
    { 0b00000, "bltz",   decode_s_offs },
    { 0b10000, "bltzal", decode_s_offs },
    { 0b00001, "bgez",   decode_s_offs },
    { 0b10001, "bgezal", decode_s_offs },
    { 0, NULL, NULL}
};

const char *szGPRNames[] = {
    "r0", "at", "v0", "v1", "a0", "a1", "a2", "a3",
    "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
    "t9", "t9", "k0", "k1", "gp", "sp", "fp", "ra"
};

const char *szFPRNames[] = {
    "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7",
    "f8", "f9", "f10", "f11", "f12", "f13", "f14", "f15",
    "f16", "f17", "f18", "f19", "f20", "f21", "f22", "f23",
    "f24", "f25", "f26", "f27", "f28", "f29", "f30", "f31"
};

const char *gprname(int num)
{
    return szGPRNames[num & 0x1F];
}

const char *fprname(int num)
{
    return szFPRNames[num & 0x1F];
}

int decode_special(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    const opcode_entry_t *opcodeEntry = lookup_opcode(special_opcodes, opcode.std.fn);

    if(opcodeEntry == NULL)
    {
        return 0;
    }

    int res = opcodeEntry->decode(out, pc, opcode, opcodeEntry->name);

    return res;
}

int decode_regimm(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    const opcode_entry_t *opcodeEntry = lookup_opcode(regimm_opcodes, opcode.regimm.regimm);

    if(opcodeEntry == NULL)
    {
        return 0;
    }

    int res = opcodeEntry->decode(out, pc, opcode, opcodeEntry->name);
    return res;
}

int decode_dst(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-8s %s, %s, %s", name,
        gprname(opcode.std.d),
        gprname(opcode.std.s),
        gprname(opcode.std.t));

    return 1;
}

int decode_ts_imm(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-8s %s, %s, 0x%04X", name,
        gprname(opcode.sti.t),
        gprname(opcode.sti.s),
        opcode.sti.imm16);

    return 1;
}

int decode_t_imm(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-8s %s, 0x%04X", name,
        gprname(opcode.sti.t),
        opcode.sti.imm16);

    return 1;
}

int decode_st_offs(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    uint32_t target = pc + (opcode.sti.imm16 * 4);

    sprintf(out, "%-8s %s, %s, 0x%08X", name,
        gprname(opcode.sti.s),
        gprname(opcode.sti.t),
        target);

    return 1;
}

int decode_s_offs(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    uint32_t target = pc + (opcode.sti.imm16 * 4);

    sprintf(out, "%-8s %s, 0x%04X", name,
        gprname(opcode.sti.s),
        target);

    return 1;
}

int decode_target26(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    uint32_t target = opcode.i26.imm26 * 4;
    sprintf(out, "%-8s 0x%08X", name, target);
    return 1;
}

int decode_loadstore(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-8s %s, 0x%04X(%s)", name,
        gprname(opcode.sti.t),
        opcode.sti.imm16,
        gprname(opcode.sti.s));

    return 1;
}

int decode_loadstore_c1(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-8s %s, 0x%04X(%s)", name,
        fprname(opcode.sti.t),
        opcode.sti.imm16,
        gprname(opcode.sti.s));

    return 1;
}

int decode_s(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-8s %s", name,
        gprname(opcode.std.s));

    return 1;
}

const opcode_entry_t *lookup_opcode(const opcode_entry_t *opcodes, int tag)
{
    for(int i = 0;; i++)
    {
        if(opcodes[i].name == NULL)
        {
            return NULL;
        }

        if(opcodes[i].tag == tag)
        {
            return &opcodes[i];
        }
    }

    return NULL;
}

int disasm_opcode(char *out, uint32_t pc, opcode_t opcode)
{
    if(opcode.bits == 0x00000000)
    {
        sprintf(out, "nop");
        return 1;
    }

    const opcode_entry_t *opcodeEntry = lookup_opcode(opcodes, opcode.sti.op);

    if(opcodeEntry == NULL)
    {
        return 0;
    }

    int res = opcodeEntry->decode(out, pc, opcode, opcodeEntry->name);

    return res;
}

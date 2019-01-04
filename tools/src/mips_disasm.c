#include <stdio.h>
#include "mips_disasm.h"
#include "rom.h"
#include "bswap.h"

const opcode_info_t opcodes[] = {
    // op      name     decoder
    { 0b000000, "***",    decode_special }, // use special_opcodes
    { 0b000001, "***",    decode_regimm }, // use regimm_opcodes
    { 0b010001, "***",    decode_cop1 },
    { 0b000010, "j",      decode_target26 },
    { 0b000011, "jal",    decode_target26 },
    { 0b000110, "blez",   decode_s_offs },
    { 0b010110, "blezl",  decode_s_offs },
    { 0b000100, "beq",    decode_st_offs },
    { 0b000101, "bne",    decode_st_offs },
    { 0b000111, "bgtz",   decode_s_offs },
    { 0b010111, "bgtzl",  decode_s_offs },
    { 0b001000, "addi",   decode_ts_imm },
    { 0b001001, "addiu",  decode_ts_imm },
    { 0b001010, "slti",   decode_ts_imm },
    { 0b001011, "sltiu",  decode_ts_imm },
    { 0b001100, "andi",   decode_ts_imm },
    { 0b001101, "ori",    decode_ts_imm },
    { 0b001110, "xori",   decode_ts_imm },
    { 0b001111, "lui",    decode_t_imm },
    { 0b010100, "beql",   decode_st_offs },
    { 0b010101, "bnel",   decode_st_offs },
    { 0b011000, "daddi",  decode_ts_imm },
    { 0b011001, "daddiu", decode_ts_imm },
    { 0b011010, "ldl",    decode_loadstore },
    { 0b011011, "ldr",    decode_loadstore },
    { 0b100000, "lb",     decode_loadstore },
    { 0b100001, "lh",     decode_loadstore },
    { 0b100010, "lwl",    decode_loadstore },
    { 0b100011, "lw",     decode_loadstore },
    { 0b100100, "lbu",    decode_loadstore },
    { 0b100101, "lhu",    decode_loadstore },
    { 0b100110, "lwr",    decode_loadstore },
    { 0b100111, "lwu",    decode_loadstore },
    { 0b101000, "sb",     decode_loadstore },
    { 0b101001, "sh",     decode_loadstore },
    { 0b101010, "swl",    decode_loadstore },
    { 0b101011, "sw",     decode_loadstore },
    { 0b101110, "swr",    decode_loadstore },
    { 0b110001, "lwc1",   decode_loadstore_c1 },
    { 0b110111, "ld",     decode_loadstore },
    { 0b111001, "swc1",   decode_loadstore_c1 },
    { 0b110101, "ldc1",   decode_loadstore_c1 },
    { 0b111101, "sdc1",   decode_loadstore_c1 },
    { 0b111111, "sd",     decode_loadstore },
    { 0b101100, "sdl",    decode_loadstore },
    { 0b101101, "sdr",    decode_loadstore },
    // SYNC stype
    // SYSCALL code
    // BREAK code
    // TEQ s, t[, code]
    // TEQI s, imm
    // TGE s, t[, code]
    // TGEI s, imm
    // TGEIU s, imm
    // TGEU s, t
    // TLT s, t
    // TLTI s, imm
    // TLTIU s, imm
    // tltu s, t[, code]
    // tne s, t
    // tnei
    //{ 0b110000, "ll", decode_loadstore }, //?
    //{ 0b110100, "lld", decode_loadstore }, //?
    // movn, movz, pref, sc?
    // scd
    { 0, NULL, NULL}
};

// COPz 0100zz

const opcode_info_t special_opcodes[] = {
    // func   name decoder
    { 0b000000, "sll",   decode_dt_shamt },
    { 0b000010, "srl",   decode_dt_shamt },
    { 0b000011, "sra",   decode_dt_shamt },
    { 0b000100, "sllv",  decode_dts },
    { 0b000110, "srlv",  decode_dts },
    { 0b000111, "srav",  decode_dts },
    { 0b001000, "jr",     decode_s },
    { 0b001001, "jalr",   decode_jalr},
    { 0b010000, "mfhi", decode_d },
    { 0b010010, "mflo", decode_d },
    { 0b010001, "mthi", decode_s },
    { 0b010011, "mtlo", decode_s },
    { 0b010100, "dsllv",  decode_dts },
    { 0b010111, "dsrav",  decode_dts },
    { 0b010110, "dsrlv",  decode_dts },
    { 0b011000, "mult",  decode_st },
    { 0b011001, "multu",  decode_st },
    { 0b011010, "div",    decode_st },
    { 0b011011, "divu",   decode_st },
    { 0b011100, "dmult",  decode_st },
    { 0b011110, "ddiv",   decode_st },
    { 0b011111, "ddivu",  decode_st },
    { 0b011101, "dmultu", decode_st },
    { 0b100101, "or",     decode_dst },
    { 0b100000, "add",    decode_dst },
    { 0b100001, "addu",   decode_dst },
    { 0b100010, "sub",   decode_dst },
    { 0b100011, "subu",  decode_dst },
    { 0b101101, "daddu",  decode_dst },
    { 0b100100, "and",    decode_dst },
    { 0b101010, "slt",    decode_dst },
    { 0b101011, "sltu",   decode_dst },
    { 0b100110, "xor",    decode_dst },
    { 0b100111, "nor",    decode_dst }, // ?
    { 0b101100, "dadd",   decode_dst },
    { 0b101110, "dsub",  decode_dst },
    { 0b101111, "dsubu",  decode_dst },
    { 0b111000, "dsll",   decode_dt_shamt },
    { 0b111100, "dsll32", decode_dt_shamt },
    { 0b111011, "dsra",   decode_dt_shamt },
    { 0b111111, "dsra32", decode_dt_shamt },
    { 0b111010, "dsrl",   decode_dt_shamt },
    { 0b111110, "dsrl32", decode_dt_shamt },
    { 0, NULL, NULL }
};

const opcode_info_t regimm_opcodes[] = {
    // regimm  name decoder
    { 0b00000, "bltz",    decode_s_offs },
    { 0b00010, "bltzl",    decode_s_offs },
    { 0b10000, "bltzal",  decode_s_offs },
    { 0b00001, "bgez",    decode_s_offs },
    { 0b00011, "bgezl",   decode_s_offs },
    { 0b10001, "bgezal",  decode_s_offs },
    { 0b10010, "bltzall",  decode_s_offs },
    { 0b10011, "bgezall", decode_s_offs },
    { 0, NULL, NULL}
};

// if fmt = s, d, w, l
const opcode_info_t cop1_opcodes[] = {
    { 0b000000, "add.", decode_cop1_dst },
    { 0b000001, "sub.", decode_cop1_dst },
    { 0b000010, "mul.", decode_cop1_dst },
    { 0b000011, "div.", decode_cop1_dst },
    { 0b000100, "sqrt.", decode_cop1_ds},
    { 0b000101, "abs.", decode_cop1_ds },
    { 0b000110, "mov.", decode_cop1_ds },
    { 0b000111, "neg.", decode_cop1_ds },
    { 0b001000, "round.l.", decode_cop1_ds },
    { 0b001001, "trunc.l.", decode_cop1_ds },
    { 0b001100, "round.w.", decode_cop1_ds },
    { 0b001101, "trunc.w.", decode_cop1_ds },
    { 0b100001, "cvt.d.", decode_cop1_ds },
    { 0b100101, "cvt.l.", decode_cop1_ds },
    { 0b100000, "cvt.s.", decode_cop1_ds },
    { 0b100100, "cvt.w.", decode_cop1_ds },
    { 0b001010, "ceil.l.", decode_cop1_ds },
    { 0b001110, "ceil.w.", decode_cop1_ds },
    { 0b001011, "floor.l.", decode_cop1_ds },
    { 0b001111, "floor.w.", decode_cop1_ds },

    { 0b110000, "c.f.", decode_cop1_st },
    { 0b110001, "c.un.", decode_cop1_st },
    { 0b110010, "c.eq.", decode_cop1_st },
    { 0b110011, "c.ueq.", decode_cop1_st },
    { 0b110100, "c.olt.", decode_cop1_st },
    { 0b110101, "c.ult.", decode_cop1_st },
    { 0b110110, "c.ole.", decode_cop1_st },
    { 0b110111, "c.ule.", decode_cop1_st },
    { 0b111000, "c.sf.", decode_cop1_st },
    { 0b111001, "c.ngle.", decode_cop1_st },
    { 0b111010, "c.seq.", decode_cop1_st },
    { 0b111011, "c.ngl.", decode_cop1_st },
    { 0b111100, "c.lt.", decode_cop1_st },
    { 0b111101, "c.nge.", decode_cop1_st },
    { 0b111110, "c.le.", decode_cop1_st },
    { 0b111111, "c.ngt.", decode_cop1_st },

    //{ 0b000110, "mov.", decode_cop1_ds}
    { 0, NULL, NULL}
};

// C.cond.fmt fs, ft
// 010001 fmt ft fs - FC cond
// 6      5   5  5  5 2  4

// 45020004
// 010001 [01 000] 000100000000000 [000100]
// 45010004
// 010001 010000 00100 000000000000100

// 010001 010000 00110 000000000000100
const opcode_info_t cop1_mtmf_opcodes[] = {
    // mf
    { 0b01000, "***",   decode_cop1_bc }, // bc1f, bc1t
    { 0b00001, "dmfc1", decode_cop1_mtmf },
    { 0b00100, "mtc1",  decode_cop1_mtmf },
    { 0b00101, "dmtc1", decode_cop1_mtmf },
    { 0b00000, "mfc1",  decode_cop1_mtmf },
    { 0b00010, "cfc1",  decode_cop1_mtmf },
    { 0b00110, "ctc1",  decode_cop1_mtmf },
    {0, NULL, NULL}
};

const opcode_info_t cop1_bc_opcodes[] = {
    { 0b00000, "bc1f", decode_cop1_branch },
    { 0b00001, "bc1t", decode_cop1_branch },
    { 0b00010, "bc1fl", decode_cop1_branch },
    { 0b00011, "bc1tl", decode_cop1_branch },
    {0, NULL, NULL}
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
    const opcode_info_t *opcodeEntry = lookup_opcode(special_opcodes, opcode.std.fn);

    if(opcodeEntry == NULL)
    {
        return 0;
    }

    int res = opcodeEntry->decode(out, pc, opcode, opcodeEntry->name);

    return res;
}

int decode_regimm(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    const opcode_info_t *opcodeEntry = lookup_opcode(regimm_opcodes, opcode.regimm.regimm);

    if(opcodeEntry == NULL)
    {
        return 0;
    }

    int res = opcodeEntry->decode(out, pc, opcode, opcodeEntry->name);
    return res;
}

int decode_cop1(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    const opcode_info_t *opcodeEntry;
    
    // check if fmt field indicates an mt or mf operation
    opcodeEntry = lookup_opcode(cop1_mtmf_opcodes, opcode.cop1.fmt);
    
    if(opcodeEntry == NULL)
    {
       opcodeEntry = lookup_opcode(cop1_opcodes, opcode.cop1.fn);
    }

    if(opcodeEntry == NULL)
    {
        return 0;
    }

    int res = opcodeEntry->decode(out, pc, opcode, opcodeEntry->name);
    return res;
}

int decode_cop1_bc(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    const opcode_info_t *opcodeEntry;
    opcodeEntry = lookup_opcode(cop1_bc_opcodes, opcode.cop1_bc.bcop);

    if(opcodeEntry == NULL)
    {
        return 0;
    }

    int res = opcodeEntry->decode(out, pc, opcode, opcodeEntry->name);
    return res;
}

int decode_cop1_branch(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    uint32_t target = pc + ((int16_t)opcode.cop1_bc.imm16 + 1) * 4;
    sprintf(out, "%-9s 0x%08X", name, target);
    return 1;
}

int decode_cop1_mtmf(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-9s %s, %s", name,
        gprname(opcode.cop1_mtmf.rt),
        fprname(opcode.cop1_mtmf.fs));

    return 1;
}

int decode_dst(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-9s %s, %s, %s", name,
        gprname(opcode.std.d),
        gprname(opcode.std.s),
        gprname(opcode.std.t));

    return 1;
}

// shift var
int decode_dts(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-9s %s, %s, %s", name,
        gprname(opcode.std.d),
        gprname(opcode.std.t),
        gprname(opcode.std.s));

    return 1;
}

int decode_d(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-9s %s", name,
        gprname(opcode.std.d));

    return 1;
}

int decode_ts_imm(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-9s %s, %s, 0x%04X", name,
        gprname(opcode.sti.t),
        gprname(opcode.sti.s),
        opcode.sti.imm16);

    return 1;
}

int decode_t_imm(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-9s %s, 0x%04X", name,
        gprname(opcode.sti.t),
        opcode.sti.imm16);

    return 1;
}

int decode_st_offs(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    uint32_t target = pc + ((int16_t)opcode.sti.imm16 + 1) * 4;

    sprintf(out, "%-9s %s, %s, 0x%08X", name,
        gprname(opcode.sti.s),
        gprname(opcode.sti.t),
        target);

    return 1;
}

int decode_st(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-9s %s, %s", name,
        gprname(opcode.sti.s),
        gprname(opcode.sti.t));

    return 1;
}

int decode_dt_shamt(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-9s %s, %s, %d", name,
        gprname(opcode.shifti.d),
        gprname(opcode.shifti.t),
        opcode.shifti.sa);

    return 1;
}

int decode_s_offs(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    uint32_t target = pc + (opcode.sti.imm16 * 4);

    sprintf(out, "%-9s %s, 0x%04X", name,
        gprname(opcode.sti.s),
        target);

    return 1;
}

int decode_target26(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    uint32_t target = (pc & 0xF0000000) | (opcode.i26.imm26 * 4);
    sprintf(out, "%-9s 0x%08X", name, target);
    return 1;
}

int decode_loadstore(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-9s %s, 0x%04X(%s)", name,
        gprname(opcode.sti.t),
        opcode.sti.imm16,
        gprname(opcode.sti.s));

    return 1;
}

int decode_loadstore_c1(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-9s %s, 0x%04X(%s)", name,
        fprname(opcode.sti.t),
        opcode.sti.imm16,
        gprname(opcode.sti.s));

    return 1;
}

int decode_s(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    sprintf(out, "%-9s %s", name,
        gprname(opcode.std.s));

    return 1;
}

int decode_jalr(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    if(opcode.std.d == 31)
    {
        sprintf(out, "%-9s %s", name,
            gprname(opcode.std.s));
    }
    else
    {
        sprintf(out, "%-9s %s, %s", name,
            gprname(opcode.std.d),
            gprname(opcode.std.s));
    }

    return 1;
}

const char *fmtname(int fmt)
{
    // https://www.cs.cmu.edu/afs/cs/academic/class/15740-f97/public/doc/mips-isa.pdf
    // B 7 Valid Operands for FP Instructions

    switch(fmt)
    {
    case 16: return "s";
    case 17: return "d";
    case 20: return "w";
    case 21: return "l";
    }

    return NULL;
}

int decode_cop1_ds(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    char nameWithFmt[64];

    sprintf(nameWithFmt, "%s%s", name,
        fmtname(opcode.cop1.fmt)); 

    sprintf(out, "%-9s %s, %s", nameWithFmt,
        fprname(opcode.cop1.d),
        fprname(opcode.cop1.s));

    return 1;
}

int decode_cop1_st(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    char nameWithFmt[64];

    sprintf(nameWithFmt, "%s%s", name,
        fmtname(opcode.cop1.fmt)); 

    sprintf(out, "%-9s %s, %s", nameWithFmt,
        fprname(opcode.cop1.s),
        fprname(opcode.cop1.t));

    return 1;
}

int decode_cop1_dst(char *out, uint32_t pc, opcode_t opcode, const char *name)
{
    char nameWithFmt[64];

    sprintf(nameWithFmt, "%s%s", name,
        fmtname(opcode.cop1.fmt)); 

    sprintf(out, "%-9s %s, %s, %s", nameWithFmt,
        fprname(opcode.cop1.d),
        fprname(opcode.cop1.s),
        fprname(opcode.cop1.t));

    return 1;
}

const opcode_info_t *lookup_opcode(const opcode_info_t *opcodeLut, int tag)
{
    for(int i = 0;; i++)
    {
        if(opcodeLut[i].name == NULL)
        {
            return NULL;
        }

        if(opcodeLut[i].tag == tag)
        {
            return &opcodeLut[i];
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

    const opcode_info_t *opcodeEntry = lookup_opcode(opcodes, opcode.sti.op);

    if(opcodeEntry == NULL)
    {
        return 0;
    }

    int res = opcodeEntry->decode(out, pc, opcode, opcodeEntry->name);

    return res;
}



void u32_vector_init(u32_vector_t *vec)
{
    vec->count = 0;
    vec->slots = 64;
    vec->array = malloc(sizeof(uint32_t) * vec->slots);
}

void u32_vector_free(u32_vector_t *vec)
{
    free(vec->array);
}

int u32_vector_indexof(u32_vector_t *vec, uint32_t value)
{
    for(int i = 0; i < vec->count; i++)
    {
        if(vec->array[i] == value)
        {
            return i;
        }
    }
    return -1;
}

void u32_vector_push(u32_vector_t *vec, uint32_t value)
{
    if(vec->count == vec->slots)
    {
        vec->slots *= 2;
        vec->array = realloc(vec->array, sizeof(uint32_t) * vec->slots);
    }

    vec->array[vec->count++] = value;
}

void u32_vector_push_unique(u32_vector_t *vec, uint32_t value)
{
    if(u32_vector_indexof(vec, value) == -1)
    {
        u32_vector_push(vec, value);
    }
}

/////////////////

void mips_analysis_init(mips_analysis_t *analysis)
{
    u32_vector_init(&analysis->jalTargets);
    u32_vector_init(&analysis->branchTargets);
}

void mips_analysis_free(mips_analysis_t *analysis)
{
    u32_vector_free(&analysis->jalTargets);
    u32_vector_free(&analysis->branchTargets);
}

int mips_analysis_run(mips_analysis_t *analysis, uint32_t pc, uint8_t *code, size_t size)
{
    int bLastOpWasNop = 0;

    for(size_t i = 0; i < size; i += 4)
    {
        opcode_t opcode;
        opcode.bits = U32_BE(code, i);
        
        if(opcode.i26.op == 0b000011) // jal
        {
            uint32_t target = (pc & 0xF0000000) | (opcode.i26.imm26 * 4);
            u32_vector_push_unique(&analysis->jalTargets, target);
        }

        if(opcode.bits == 0) // nop
        {
            if(bLastOpWasNop == 1)
            {
                printf("// possible split @ %08X\n", pc);
            }
            bLastOpWasNop = 1;
        }
        else
        {
            bLastOpWasNop = 0;
        }

        pc += 4;
    }

    //for(int i = 0; i < analysis->jalTargets.count; i++)
    //{
    //    printf("func_%08X\n", analysis->jalTargets.array[i]);
    //}
}

int mips_analysis_have_jal_target(mips_analysis_t *analysis, uint32_t address)
{
    return (u32_vector_indexof(&analysis->jalTargets, address) != -1);
}
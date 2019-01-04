#ifndef _MIPS_DISASM_H_
#define _MIPS_DISASM_H_
#include <stdint.h>

typedef union
{
    uint32_t bits;
    struct {
        uint32_t imm16 : 16;
        uint32_t t : 5;
        uint32_t s : 5;
        uint32_t op : 6;
    } sti;

    struct {
        uint32_t imm26 : 26;
        uint32_t op : 6;
    } i26;

    struct {
        uint32_t fn : 6;
        uint32_t : 5;
        uint32_t d : 5;
        uint32_t t : 5;
        uint32_t s : 5;
        uint32_t op : 6;
    } std;

    struct {
        uint32_t imm16 : 16;
        uint32_t regimm : 5;
        uint32_t s : 5;
        uint32_t op : 5;
    } regimm;
} opcode_t;

typedef int (*decode_fn_t)(char *out, uint32_t pc, opcode_t opcode, const char *name);

typedef struct 
{
    int tag; // unique bits in op, fn, regimm, etc fields
    const char *name;
    decode_fn_t decode;
} opcode_entry_t;

int disasm_opcode(char *out, uint32_t pc, opcode_t opcode);

const opcode_entry_t *lookup_opcode(const opcode_entry_t *opcodes, int tag);

int decode_special(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_ts_imm(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_t_imm(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_target26(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_loadstore(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_loadstore_c1(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_s(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_st_offs(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_regimm(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_s_offs(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_dst(char *out, uint32_t pc, opcode_t opcode, const char *name);

#endif // _MIPS_DISASM_H_
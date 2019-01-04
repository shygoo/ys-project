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

    struct {
        uint32_t fn : 6;
        uint32_t sa : 5;
        uint32_t d : 5;
        uint32_t t : 5;
        uint32_t : 5;
        uint32_t op : 6;
    } shifti;

    struct {
        uint32_t fn : 6;
        uint32_t d : 5;
        uint32_t s : 5;
        uint32_t t : 5;
        uint32_t fmt : 5;
        uint32_t op : 6;
    } cop1;

    struct {
        uint32_t : 11;
        uint32_t fs : 5;
        uint32_t rt : 5;
        uint32_t mt : 5;
        uint32_t op : 6;
    } cop1_mtmf;

    struct {
        uint32_t imm16 : 16;
        uint32_t bcop : 5;
        uint32_t bc : 5;
        uint32_t op : 6;
    } cop1_bc;

} opcode_t;

typedef int (*decode_fn_t)(char *out, uint32_t pc, opcode_t opcode, const char *name);

typedef struct 
{
    int tag; // unique bits in op, fn, regimm, etc fields
    const char *name;
    decode_fn_t decode;
} opcode_info_t;

int disasm_opcode(char *out, uint32_t pc, opcode_t opcode);

const opcode_info_t *lookup_opcode(const opcode_info_t *opcodeLut, int tag);

int decode_special(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_regimm(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_cop1(char *out, uint32_t pc, opcode_t opcode, const char *name);

int decode_ts_imm(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_t_imm(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_target26(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_loadstore(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_loadstore_c1(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_s(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_st_offs(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_st(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_s_offs(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_dst(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_dts(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_dt_shamt(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_jalr(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_d(char *out, uint32_t pc, opcode_t opcode, const char *name);

int decode_cop1_ds(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_cop1_st(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_cop1_dst(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_cop1_bc(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_cop1_mtmf(char *out, uint32_t pc, opcode_t opcode, const char *name);
int decode_cop1_branch(char *out, uint32_t pc, opcode_t opcode, const char *name);

typedef struct
{
    uint32_t *array;
    int count;
    int slots;
} u32_vector_t;

typedef struct
{
    u32_vector_t jalTargets;
    u32_vector_t branchTargets;
} mips_analysis_t;

void mips_analysis_init(mips_analysis_t *analysis);
void mips_analysis_free(mips_analysis_t *analysis);
int mips_analysis_run(mips_analysis_t *analysis, uint32_t pc, uint8_t *code, size_t size);
int mips_analysis_have_jal_target(mips_analysis_t *analysis, uint32_t address);

#endif // _MIPS_DISASM_H_

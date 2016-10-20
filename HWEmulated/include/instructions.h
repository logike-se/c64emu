/*
 * instructions.h
 *
 *  Created on: 17 Oct 2016
 *      Author: johanwestlund
 */

#ifndef INCLUDE_INSTRUCTIONS_H_
#define INCLUDE_INSTRUCTIONS_H_

typedef enum{
    BRK,
    ORA,
    ASL,
    PHP,
    BPL,
    CLC,
    NOP,
    /* Illegal Instructions */
    KIL,
    SLO,
    DOP,
    ANC,
    TOP
} Instruction;

typedef enum{
    IMP,
    INX,
    INY,
    ZP,
    ZPX,
    ZPY,
    IMM,
    ACC,
    ABS,
    REL,
    ABX,
    ABY
} AddrMode;

typedef struct{
    Instruction instr;      /* Instruction Name */
    AddrMode mode;          /* Addressing mode */
    size_t size;            /* Size of operation in bytes */
    size_t cycles;          /* Minimum number of clock cycles */
} InstructionInfo;

static InstructionInfo Decode[/*OpCode*/] = {
        /* 0x00 */
        {BRK, IMP, 1, 7},
        {ORA, INX, 2, 6},
        {KIL, IMP, 1, 0},
        {SLO, INX, 2, 8},
        {DOP, ZP,  2, 3},
        {ORA, ZP,  2, 3},
        {ASL, ZP,  2, 5},
        {SLO, ZP,  2, 5},
        {PHP, IMP, 1, 3},
        {ORA, IMM, 2, 2},
        {ASL, ACC, 1, 2},
        {ANC, IMM, 2, 2},
        {TOP, ABS, 3, 4},
        {ORA, ABS, 3, 4},
        {ASL, ABS, 3, 6},
        {SLO, ABS, 3, 6},
        /* 0x10 */
        {BPL, REL, 2, 2},
        {ORA, INY, 2, 5},
        {KIL, IMP, 1, 0},
        {SLO, INY, 2, 8},
        {DOP, ZPX, 2, 4},
        {ORA, ZPX, 2, 4},
        {ASL, ZPX, 2, 6},
        {SLO, ZPY, 2, 6},
        {CLC, IMP, 1, 2},
        {ORA, ABY, 3, 4},
        {NOP, IMP, 1, 2},
        {SLO, ABY, 3, 7},
        {TOP, ABX, 3, 4},
        {ORA, ABX, 3, 4},
        {ASL, ABX, 3, 7},
        {SLO, ABX, 3, 7}
        /* 0x20 */
};

#endif /* INCLUDE_INSTRUCTIONS_H_ */

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
    /* Illegal Instructions */
    KIL,
    SLO,
    DOP,
    ANC,
    TOP
} Instruction;

typedef enum{
    IMPL,
    INX,
    ZP,
    IMM,
    ACC,
    ABS
} AddrMode;

typedef struct{
    Instruction instr;
    AddrMode mode;
    size_t size;
    size_t cycles;
} InstructionInfo;

static InstructionInfo Decode[/*OpCode*/] = {
        /* 0x00 */
        {BRK, IMPL, 1, 7},
        {ORA, INX,  2, 6},
        {KIL, IMPL, 1, 0},
        {SLO, INX,  2, 8},
        {DOP, ZP,   2, 3},
        {ORA, ZP,   2, 3},
        {ASL, ZP,   2, 5},
        {SLO, ZP,   2, 5},
        {PHP, IMPL, 1, 3},
        {ORA, IMM,  2, 2},
        {ASL, ACC,  1, 2},
        {ANC, IMM,  2, 2},
        {TOP, ABS,  3, 4},
        {ORA, ABS,  3, 4},
        {ASL, ABS,  3, 6},
        {SLO, ABS,  3, 6}
        /* 0x10 */
};

#endif /* INCLUDE_INSTRUCTIONS_H_ */

/*
 * cia.h
 *
 *  Created on: 21 Oct 2016
 *      Author: johanwestlund
 */

#ifndef INCLUDE_CIA_H_
#define INCLUDE_CIA_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "common.h"

#define KEYB_ROW    8
#define KEYB_COL    8
#define NO_CIA      2
#define NO_REGISTER 16

typedef enum{
    PRA = 0,
    PRB,
    DDRA,
    DDRB
} Registers;

/* This map corresponds to the keyboard matrix defined by Port A and Port B of CIA1 */
static const char KeyboardMap[KEYB_ROW][KEYB_COL];

static uint8_t KeyPressed_n[KEYB_ROW];              // Set/clear when keyboard key is pressed or released (active low)
static uint8_t CiaRegisters[NO_CIA][NO_REGISTER];   // CIA registers

/* CIA functions */
void CiaInit();
void CiaWrite(IO_TYPE type, uint16_t address, uint8_t data);
uint8_t CiaRead(IO_TYPE type, uint16_t address);
void CiaUpdate();

#endif /* INCLUDE_CIA_H_ */

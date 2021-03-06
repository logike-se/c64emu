/*
 * memory
 *
 * The memmgr.c implementation will be responsible for all memory calls,
 * bank switching and dispatching of calls to other hardware modules such
 * as the VIC-II, CIA etc.
 *
 *  Created on: 5 Oct 2016
 *      Author: Johan Westlund
 */

#ifndef MEMORY_
#define MEMORY_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "c64emu.h"
#include "common.h"

/* CPU memory map control bits */
#define LORAM    0x01
#define HIRAM    0x02
#define CHAREN   0x04

typedef enum{
    TYPE_UNMAPPED,
    TYPE_RAM,
    TYPE_KERNAL,
    TYPE_CHAR,
    TYPE_BASIC,
    TYPE_CART_HI_GAME,
    TYPE_CART_HI_EXT,
    TYPE_CART_LO,
    TYPE_IO
} MEM_TYPE;

typedef enum{
	RAM_SIZE        = 0xFFFF,   //64k
	ROM_KERNAL_SIZE = 0x2000,   //8k
	ROM_BASIC_SIZE  = 0x2000,   //8k
	ROM_CHAR_SIZE   = 0x1000,   //4k
	ROM_CART_SIZE   = 0x2000,   //8k
	IO_MEM_SIZE     = 0x1000,   //4k
	MEM_PAGE_SIZE   = 256
} MEMORY_SIZE;

typedef enum{
	BASE_RAM            = 0x0000,
	BASE_KERNAL         = 0xE000,
	BASE_CHAR           = 0xD000,
	BASE_BASIC          = 0xA000,
	BASE_CART_HI_GAME   = 0xE000,
	BASE_CART_HI_EXT    = 0xA000,
	BASE_CART_LO        = 0x8000,
	BASE_IO             = 0xD000,
	BASE_UNMAPPED       = 0xFFFF
} MEM_BASE_ADDRESS;

/* Note: Real base address is IO_BASE_ADDRESS + MEM_BASE_ADDRESS */
typedef enum{
	BASE_VIC        = 0x000,
	BASE_SID        = 0x400,
	BASE_COLOR_RAM  = 0x800,
	BASE_CIA1       = 0xC00,
	BASE_CIA2       = 0xD00,
	BASE_IO1        = 0xE00,
	BASE_IO2        = 0xF00
} IO_BASE_ADDRESS;

typedef enum{
	SIZE_VIC        = 0x400,
	SIZE_SID        = 0x400,
	SIZE_COLOR_RAM  = 0x400,
	SIZE_CIA        = 0x100,
	SIZE_IO         = 0x100
} IO_SIZE;

typedef enum{
	MEM_READ,
	MEM_WRITE
} MEM_ACCESS;

typedef enum{
    CPU_PORT_REG    = 0x0001
} CPU_REGISTERS;

typedef enum{
    ZONE1,
    ZONE2,
    ZONE3,
    ZONE4,
    ZONE5,
    ZONE6,
    ZONE7
} BANK_SWITCHING_ZONE;

/* Memory declarations */
static uint8_t RAM[RAM_SIZE];
static uint8_t ROM_BASIC[ROM_BASIC_SIZE];
static uint8_t ROM_KERNAL[ROM_KERNAL_SIZE];
static uint8_t ROM_CHAR[ROM_CHAR_SIZE];
static uint8_t ROM_CART_HI[ROM_CART_SIZE];
static uint8_t ROM_CART_LO[ROM_CART_SIZE];
static IO_TYPE IO_MEM[IO_MEM_SIZE];

/* System functions */
void MemInit();
void Mem(uint16_t address, uint8_t* data, MEM_ACCESS rw);

/* Internal help functions */
static BANK_SWITCHING_ZONE getBankSwitchZone(uint8_t page);
static MEM_TYPE getMemType(BANK_SWITCHING_ZONE zone);
static MEM_BASE_ADDRESS getBaseAddress(MEM_TYPE type);
static IO_BASE_ADDRESS getIOBaseAddress(IO_TYPE type);
static void dispatchIOMemCall(IO_TYPE type, uint16_t address, uint8_t* data, MEM_ACCESS rw);
static uint8_t* getMemory(MEM_TYPE type);

#endif /* MEMORY_ */

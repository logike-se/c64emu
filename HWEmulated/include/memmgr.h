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

typedef enum{
	RAM_SIZE            = 0xFFFF,		//64k
	ROM_KERNAL_SIZE     = 0x2000,		//8k
	ROM_CHAR_SIZE		= 0x1000,		//4k
	ROM_CART_SIZE		= 0x2000,		//8k
	IO_MEM_SIZE			= 0x1000,		//4k
	MEM_PAGE_SIZE		= 256
} E_MEMORY_SIZE;

typedef enum{
	BASE_RAM			= 0x0000,
	BASE_KERNAL			= 0xE000,
	BASE_CHAR			= 0xD000,
	BASE_BASIC			= 0xB000,
	BASE_CART_HI_GAME	= 0xE000,
	BASE_CART_HI_EXT	= 0xA000,
	BASE_CART_LO		= 0x8000,
	BASE_IO				= 0xD000
} E_MEM_BASE_ADDRESS;

typedef enum{
	TYPE_VIC,
	TYPE_SID,
	TYPE_COLOR_RAM,
	TYPE_CIA1,
	TYPE_CIA2,
	TYPE_IO1,
	TYPE_IO2
} E_IO_TYPE;

/* Note: Real base address is IO_BASE_ADDRESS + MEM_BASE_ADDRESS */
typedef enum{
	BASE_VIC		= 0x000,
	BASE_SID		= 0x400,
	BASE_COLOR_RAM	= 0x800,
	BASE_CIA1		= 0xC00,
	BASE_CIA2		= 0xD00,
	BASE_IO1		= 0xE00,
	BASE_IO2		= 0xF00
} E_IO_BASE_ADDRESS;

typedef enum{
	SIZE_VIC		= 0x400,
	SIZE_SID		= 0x400,
	SIZE_COLOR_RAM	= 0x400,
	SIZE_CIA		= 0x100,
	SIZE_IO			= 0x100
} E_IO_SIZE;

typedef enum{
	LORAM 	= 0x01,
	HIRAM 	= 0x02,
	CHAREN	= 0x04,
	GAME	= 0x08,
	EXROM	= 0x10
} E_BANK_SWITCH_MASK;

typedef enum{
	MEM_READ,
	MEM_WRITE
} E_MEM_ACCESS;

static uint8_t RAM[RAM_SIZE];
static uint8_t ROM_KERNAL[ROM_KERNAL_SIZE];
static uint8_t ROM_CHAR[ROM_CHAR_SIZE];
static uint8_t ROM_CART_HI[ROM_CART_SIZE];
static uint8_t ROM_CART_LO[ROM_CART_SIZE];
static E_IO_TYPE IO_MEM[IO_MEM_SIZE];

void 	MemInit();
void 	Mem(uint16_t address, uint8_t* data, E_MEM_ACCESS rw);
void 	MemLoad(uint16_t address, uint8_t* data, uint16_t length);


#endif /* MEMORY_ */

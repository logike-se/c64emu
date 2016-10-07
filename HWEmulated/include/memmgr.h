/*
 * memory
 *
 * The memory.c implementation will be responsible for all memory calls,
 * bank switching and dispatching of calls to other hardware modules such
 * as the VIC-II, CIA etc.
 *
 *  Created on: 5 Oct 2016
 *      Author: johanwestlund
 */

#ifndef MEMORY_
#define MEMORY_

#include <stdint.h>

#define RAM_SIZE 			0xFFFF		//64k
#define ROM_KERNAL_SIZE		0x2000		//8k
#define ROM_CHAR_SIZE		0x1000		//4k
#define ROM_CART_SIZE		0x2000		//8k
#define HW_IO_SIZE			0x1000		//4k
#define MEM_PAGE_SIZE		256u
#define MEM_PAGE_SIZE_LS	8			//Left Shift

typedef enum{
	VIC,
	SID,
	COLOR_RAM,
	CIA1,
	CIA2,
	IO1,
	IO2
} IO_TYPE;

static uint8_t RAM[RAM_SIZE];
static uint8_t ROM_KERNAL[ROM_KERNAL_SIZE];
static uint8_t ROM_CHAR[ROM_CHAR_SIZE];
static uint8_t ROM_CART_HI[ROM_CART_SIZE];
static uint8_t ROM_CART_LO[ROM_CART_SIZE];
static IO_TYPE HW_IO[HW_IO_SIZE];


#endif /* MEMORY_ */

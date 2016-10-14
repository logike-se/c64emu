/*
 * c64emu.h
 *
 *  Created on: 14 Oct 2016
 *      Author: johanwestlund
 */

#ifndef INCLUDE_C64EMU_H_
#define INCLUDE_C64EMU_H_

typedef enum{
    CART_GAME,
    CART_EXROM
} CARTRIDGE_TYPE;


/* Exported functions */
extern void MemLoad(uint16_t address, uint8_t* data, uint16_t length);
extern void Cartridge(CARTRIDGE_TYPE t, bool insert);

#endif /* INCLUDE_C64EMU_H_ */

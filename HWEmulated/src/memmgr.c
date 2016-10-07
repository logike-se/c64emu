#include "memmgr.h"

uint8_t CONTROL_BITS = LORAM | HIRAM | CHAREN | GAME | EXROM;
uint8_t GameEnabled_n = GAME;
uint8_t ExpansionEnabled_n = EXROM;

/* Initialize all memories */
void MemInit(){
	/* Clear RAM */
	memset(RAM, 0, RAM_SIZE);

	/* Clear Kernal ROM */
	memset(ROM_KERNAL, 0, ROM_KERNAL_SIZE);

	/* Clear Character ROM */
	memset(ROM_CHAR, 0, ROM_CHAR_SIZE);

	/* Clear Cartridge ROM */
	memset(ROM_CART_HI, 0, ROM_CART_SIZE);
	memset(ROM_CART_LO, 0, ROM_CART_SIZE);

	/* Initialize IO memory with IO type to make it easier when dispatching memory calls */
	memset(&IO_MEM[BASE_VIC], TYPE_VIC, SIZE_VIC);
	memset(&IO_MEM[BASE_SID], TYPE_SID, SIZE_SID);
	memset(&IO_MEM[BASE_COLOR_RAM], TYPE_COLOR_RAM, SIZE_COLOR_RAM);
	memset(&IO_MEM[BASE_CIA1], TYPE_CIA1, SIZE_CIA);
	memset(&IO_MEM[BASE_CIA2], TYPE_CIA2, SIZE_CIA);
	memset(&IO_MEM[BASE_IO1], TYPE_IO1, SIZE_IO);
	memset(&IO_MEM[BASE_IO2], TYPE_IO2, SIZE_IO);
}

/* This function performs reads and writes to the memory */
void Mem(uint16_t address, uint8_t* data, MEM_ACCESS rw){
    /* Check memory configuration */
    CONTROL_BITS = (RAM[CPU_PORT_REG] & 0x03) | GameEnabled_n | ExpansionEnabled_n;
}

/* Insert or remove cartridge */
void Cardridge(CARTRIDGE_TYPE t, bool insert){
    switch(t){
    case CART_GAME:
        GameEnabled_n = (insert) ? 0 : GAME;
        break;
    case CART_EXROM:
        ExpansionEnabled_n = (insert) ? 0 : EXROM;
        break;
    default:
        break;
    }
}

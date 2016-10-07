#include "memmgr.h"

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


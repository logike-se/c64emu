#include "memmgr.h"

static uint8_t GameEnabled_n = GAME;
static uint8_t ExpansionEnabled_n = EXROM;
static uint8_t PreviousPage = 0;

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

    /* Check memory configuration for bank switching */
    uint8_t ctrlBits = (RAM[CPU_PORT_REG] & 0x03) | GameEnabled_n | ExpansionEnabled_n;

    /* Handle page crossing */
    uint8_t memPage = address / MEM_PAGE_SIZE;
    if (PreviousPage != memPage){
        // TODO: if page crossed then tick()
    }
    PreviousPage = memPage;

    /* Calculate the currently mapped memory for the specified address */
    uint8_t zone = getBankSwitchZone(memPage);
    MEM_TYPE memType = getMemType(zone, ctrlBits);
    MEM_BASE_ADDRESS base = getBaseAddress(zone);
    uint16_t localAddress = address - base;

    if (memType == TYPE_IO){
        /* If the call is to another HW module, a.k.a IO, then dispatch the call to that module */
        IO_TYPE ioType = IO_MEM[localAddress];
        uint16_t ioBase = getIOBaseAddress(ioType);
        uint16_t ioAddress = localAddress - ioBase;
        dispatchIOMemCall(ioType, ioAddress, data, rw);
    }
    else{
        if (rw == MEM_READ){
            /* Fetch the memory for read */
            uint8_t* mem = getMemory(memType);
            *data = mem[localAddress];
        }
        else{
            /* All writes that are not to IO will be written thru to RAM */
            RAM[localAddress] = *data;
        }
    }
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

static uint8_t getBankSwitchZone(uint8_t page){
    // TODO: Implement
    return 0;
}

static MEM_TYPE getMemType(uint8_t zone, uint8_t ctrl){
    // TODO: Implement
    return TYPE_UNMAPPED;
}

static MEM_BASE_ADDRESS getBaseAddress(uint8_t zone){
    // TODO: Implement
    return BASE_RAM;
}

static IO_BASE_ADDRESS getIOBaseAddress(IO_TYPE type){
    // TODO: Implement
    return BASE_VIC;
}

static void dispatchIOMemCall(IO_TYPE type, uint16_t address, uint8_t* data, MEM_ACCESS rw){
    // TODO: Implement
}

static uint8_t* getMemory(MEM_TYPE type){
    // TODO: Implement
    return RAM;
}

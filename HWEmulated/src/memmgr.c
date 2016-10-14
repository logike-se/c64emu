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

	/* Clear Basic ROM */
	memset(ROM_BASIC, 0, ROM_BASIC_SIZE);

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

     /* Handle page crossing */
    uint8_t memPage = address / MEM_PAGE_SIZE;
    if (PreviousPage != memPage){
        // TODO: if page crossed then tick()
    }
    PreviousPage = memPage;

    /* Get the current memory bank and calculate its local address */
    BANK_SWITCHING_ZONE zone = getBankSwitchZone(memPage);
    MEM_TYPE memType = getMemType(zone);
    MEM_BASE_ADDRESS base = getBaseAddress(memType);
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

/* Returns bank switching zone based on memory page */
static BANK_SWITCHING_ZONE getBankSwitchZone(uint8_t page){
    if (page >= 0 && page <= 15)
        return ZONE1;
    else if(page >=16 && page <= 127)
        return ZONE2;
    else if(page >=128 && page <= 159)
        return ZONE3;
    else if(page >= 160 && page <= 191)
        return ZONE4;
    else if(page >= 192 && page <= 207)
        return ZONE5;
    else if(page >= 208 && page <= 223)
        return ZONE6;
    else
        return ZONE7;
}

/* This function decodes the current memory configuration by looking at the CPU port register bits
 * as well as connected cartridges. This is done for each memory bank zone to make the mapping a little
 * more easy */
static MEM_TYPE getMemType(BANK_SWITCHING_ZONE zone){
    /* Check configuration for bank switching */
    uint8_t ctrlBits = (RAM[CPU_PORT_REG] & 0x03);
    bool hiram = (ctrlBits & HIRAM);
    bool loram = (ctrlBits & LORAM);
    bool charen_n = (ctrlBits & CHAREN);

    /* Always RAM in all bank switching zones when */
    if ((!ExpansionEnabled_n && !GameEnabled_n && !charen_n && !hiram && loram) ||
            (!hiram && !loram && !(!GameEnabled_n && ExpansionEnabled_n))){
        return TYPE_RAM;
    }

    switch(zone){
    case ZONE1: // fall thru
    case ZONE2:
        return TYPE_RAM;
        break;
    case ZONE3:
        if ((ExpansionEnabled_n && !GameEnabled_n) || (!ExpansionEnabled_n && hiram && loram))
            return TYPE_CART_LO;
        else
            return TYPE_RAM;
        break;
    case ZONE4:
        if (GameEnabled_n && hiram && loram)
            return TYPE_BASIC;
        else if (!GameEnabled_n && !ExpansionEnabled_n && hiram)
            return TYPE_CART_HI_EXT;
        else if (!GameEnabled_n && ExpansionEnabled_n)
            return TYPE_UNMAPPED;
        else
            return TYPE_RAM;
        break;
    case ZONE5:
        if (!GameEnabled_n)
            return TYPE_UNMAPPED;
        else
            return TYPE_RAM;
        break;
    case ZONE6:
        /* Note that all RAM cases are covered above before this switch statement */
        if (!charen_n && !(ExpansionEnabled_n && !GameEnabled_n))
            return TYPE_CHAR;
        else
            return TYPE_IO;
        break;
    case ZONE7:
        if (!GameEnabled_n && ExpansionEnabled_n)
            return TYPE_CART_HI_GAME;
        else if(hiram)
            return TYPE_KERNAL;
        else
            return TYPE_RAM;
        break;
    default:
        break;
    }
    return TYPE_UNMAPPED;
}


/* This function returns the base address for a given memory type */
static MEM_BASE_ADDRESS getBaseAddress(MEM_TYPE type){
    switch(type){
    case TYPE_RAM:
        return BASE_RAM;
        break;
    case TYPE_CART_LO:
        return BASE_CART_LO;
        break;
    case TYPE_CART_HI_EXT:
        return BASE_CART_HI_EXT;
        break;
    case TYPE_BASIC:
        return BASE_BASIC;
        break;
    case TYPE_CHAR:
        return BASE_CHAR;
        break;
    case TYPE_IO:
        return BASE_IO;
        break;
    case TYPE_CART_HI_GAME:
        return BASE_CART_HI_GAME;
        break;
    case TYPE_KERNAL:
        return BASE_KERNAL;
        break;
    default:
        break;
    }
    return BASE_UNMAPPED;
}

static IO_BASE_ADDRESS getIOBaseAddress(IO_TYPE type){
    switch(type){
    case TYPE_VIC:
        return BASE_VIC;
        break;
    case TYPE_SID:
        return BASE_SID;
        break;
    case TYPE_COLOR_RAM:
        return BASE_COLOR_RAM;
        break;
    case TYPE_CIA1:
        return BASE_CIA1;
        break;
    case TYPE_CIA2:
        return BASE_CIA2;
        break;
    case TYPE_IO1:
        return BASE_IO1;
        break;
    case TYPE_IO2:
        return BASE_IO2;
        break;
    default:
        break;
    }
    /* dummy return */
    return 0xFFFF;
}

static void dispatchIOMemCall(IO_TYPE type, uint16_t address, uint8_t* data, MEM_ACCESS rw){
    // TODO: Implement
}

/* Returns the addressed memory */
static uint8_t* getMemory(MEM_TYPE type){
    switch(type){
    case TYPE_RAM:
        return RAM;
        break;
    case TYPE_CART_LO:
        return ROM_CART_LO;
        break;
    case TYPE_CART_HI_EXT:
    case TYPE_CART_HI_GAME:
        return ROM_CART_HI;
        break;
    case TYPE_BASIC:
        return ROM_BASIC;
        break;
    case TYPE_KERNAL:
        return ROM_KERNAL;
        break;
    case TYPE_CHAR:
        return ROM_CHAR;
        break;
    default:
        break;
    }

    return NULL;
}

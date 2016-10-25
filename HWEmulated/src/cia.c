/*
 * cia.c
 *
 *  Created on: 21 Oct 2016
 *      Author: Johan Westlund
 *
 */

#include "cia.h"

void KeyPressed(char key){
    //TODO: implement
}

void KeyReleased(char key){
    //TODO: implement
}

void CiaInit(){
    memset(KeyPressed_n, 0xFF, sizeof(KeyPressed_n));
}

void CiaWrite(IO_TYPE type, uint16_t address, uint8_t data){
    Registers reg = (Registers)(address & 0xF);     // Only 16 registers, mirrored on all other addresses
    int nCia = (TYPE_CIA1) ? 0 : 1;                 // Select CIA

    switch(reg){
    case PRA:
        CiaRegisters[nCia][PRA] &= ~CiaRegisters[nCia][DDRA];           // Inputs will not be affected by write, outputs will be zeroed
        CiaRegisters[nCia][PRA] |= (data & CiaRegisters[nCia][DDRA]);   // Write data to outputs only
        break;
    case PRB:
        CiaRegisters[nCia][PRB] &= ~CiaRegisters[nCia][DDRB];           // Inputs will not be affected by write, outputs will be zeroed
        CiaRegisters[nCia][PRB] |= (data & CiaRegisters[nCia][DDRB]);   // Write data to outputs only
        break;
    default:

        break;
    }

}

uint8_t CiaRead(IO_TYPE type, uint16_t address){
    Registers reg = (Registers)(address & 0xF);     // Only 16 registers, mirrored on all other addresses
    int nCia = (TYPE_CIA1) ? 0 : 1;                 // Select CIA

    return CiaRegisters[nCia][reg];                 // All registers can be read, even output ports
}

/* This function is called every clock cycle to update all registers */
void CiaUpdate(){

}

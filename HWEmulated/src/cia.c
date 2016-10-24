/*
 * cia.c
 *
 *  Created on: 21 Oct 2016
 *      Author: johanwestlund
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
    Registers reg = (Registers)(address & 0xF);
    switch(type){
    case TYPE_CIA1:
        cia1Write(reg, data);
        break;
    case TYPE_CIA2:
        cia2Write(reg, data);
    }
    default:
        break;
}

#ifndef REGISTERS_H
#define REGISTERS_H

#include<stdint.h>

uint16_t getHL();
void setHL(uint16_t value);

uint16_t getDE();
void setDE(uint16_t value);

uint16_t getBC();
void setBC(uint16_t value);

uint16_t getAF();
void setAF(uint16_t value);

#endif

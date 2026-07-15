#ifndef MEMORY_H
#define MEMORY_H

#include<stdint.h>

extern uint8_t memory[0xFFFF]; // extern prevents multiple allocations
			       // of the same data

void loader(unsigned char data,unsigned int offset);
void push(uint8_t value);
uint8_t pop();
void memory_write(uint16_t mem_addr,uint8_t val);
uint8_t memory_read(uint16_t mem_addr);

#endif

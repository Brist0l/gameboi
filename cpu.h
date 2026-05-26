#ifndef CPU_H
#define CPU_H

#include<stdint.h>


struct registers{
	uint16_t AF; // Accumulator and Flag
	uint16_t BC; // High register with B and lo with C
	uint16_t DE; // High register with D and lo with E
	uint16_t HL; // High register with H and lo with L
	uint16_t SP; // Stack Pointer pointing on top of the stack
	uint16_t PC; // Program Counter
};

extern struct registers cpu; // an extern struct with the name "cpu"

#endif

#ifndef CPU_H
#define CPU_H

#include<stdint.h>

#define GET7BIT 0b10000000
#define GET0BIT 0b00000001

struct registers{
	uint8_t A; // Accumulator and Flag
	uint8_t B;// High register with B and lo with C
	uint8_t C;// High register with B and lo with C
	uint8_t D; // High register with D and lo with E
	uint8_t E; // High register with D and lo with E
	uint8_t H; // High register with H and lo with L
	uint8_t L; // High register with H and lo with L
		   
	uint16_t SP; // Stack Pointer pointing on top of the stack
	uint16_t PC; // Program Counter
	
	uint8_t F; // Flag register , used with operations such as BIT
};

/* Flag register:
 *
 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 |
 * | Z | N | H | C | 0 | 0 | 0 |
 *
 * Z => Zero flag
 * N => Subtract flag
 * H => Half carry flag
 * C => Carry flag
 *
 */

extern struct registers cpu; // an extern struct with the name "cpu"
			     
void execute();
unsigned short get_u16();


extern unsigned short msb;
extern unsigned short lsb;
extern unsigned short u16;
extern uint8_t u8;
extern int8_t  s8;
extern unsigned short bit;
extern uint8_t addr;
extern int8_t signed_offset;
extern unsigned short buffer;
extern uint16_t result;

extern uint16_t AF;
extern uint16_t BC;
extern uint16_t DE;
extern uint16_t HL;

#endif

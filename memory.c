#include<stdint.h>

#include"cpu.h"

uint8_t memory[0xFFFF];

/*

Interrupt Enable Register
--------------------------- FFFF
Internal RAM
--------------------------- FF80
Empty but unusable for I/O
--------------------------- FF4C
I/O ports
--------------------------- FF00
Empty but unusable for I/O
--------------------------- FEA0
Sprite Attrib Memory (OAM)
--------------------------- FE00
Echo of 8kB Internal RAM
--------------------------- E000
8kB Internal RAM
--------------------------- C000
8kB switchable RAM bank
--------------------------- A000
8kB Video RAM
--------------------------- 8000 --
16kB switchable ROM bank |
--------------------------- 4000 |= 32kB Cartrigbe
16kB ROM bank #0 |
--------------------------- 0000 --
* NOTE: b = bit, B = byte
*/

void loader(unsigned char data,unsigned int offset){
	*(memory + offset) = data;
}

// Over here SP is the top so I would need to subtract first and then 
// store as if I don't then overflow is happening.
void push(uint8_t value){
	memory[--cpu.SP] = value;
}

uint8_t pop(){
	return memory[cpu.SP++];
}

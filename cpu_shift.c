#include "debug.h"
#include "flags.h"
#include "cpu.h"

void opcd_shift_a(){
	// SWAP A
	// Swap the first 4 bits with the last 4 bits
	//
	// b7 b6 b5 b4 b3 b2 b1 b0
	// 	    ||
	// b3 b2 b1 b0 b7 b6 b5 b4
	//
	// Z = set flag
	// N = 0
	// H = 0
	// C = 0
		
	dprintf("SWAP A\n");
	dprintf("value of register A before is : 0b%08b\n", cpu.A);

	cpu.A = (cpu.A >> 4) | (cpu.A << 4);

	setSWAPflags(cpu.A);

	dprintf("value of register A after is  : 0b%08b\n", cpu.A);
}

void opcd_srl_b(){

	// SRL B
	// lenght is 2 bytes
	// B's value is shifted to the right
	// by 1 bit.
	// The MSB is set to 0.
	// The carry flag is set to LSB
	// N and H are set to 0

	dprintf("SRL B\n");
	dprintf("value of register B before is : 0b%08b\n",cpu.B);

	setc(cpu.B & 0x01); //set the carry flag to the lsb

	cpu.B >>= 1; // Shift by 1 bit
	cpu.B = cpu.B & 0b01111111; // set the MSB to 0

	setz(cpu.B == 0);
	setn(0);
	seth(0);

	dprintf("value of register B after is : 0b%08b\n",cpu.B);

}

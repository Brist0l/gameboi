#include<stdint.h>

#include "cpu.h"

uint16_t getHL(){
	return (cpu.H << 8) | cpu.L;
}

void setHL(uint16_t value){
	unsigned short msb;
	unsigned short lsb;

	lsb = value & 0x00ff;
	msb = (value & 0xff00) >> 8;

	cpu.H = msb;
	cpu.L = lsb;
}

uint16_t getDE(){
	return (cpu.D << 8) | cpu.E;
}

void setDE(uint16_t value){
	unsigned short msb;
	unsigned short lsb;

	lsb = value & 0x00ff;
	msb = (value & 0xff00) >> 8;

	cpu.D = msb;
	cpu.E = lsb;
}

uint16_t getBC(){
	return (cpu.B << 8) | cpu.C;
}

void setBC(uint16_t value){
	unsigned short msb;
	unsigned short lsb;

	lsb = value & 0x00ff;
	msb = (value & 0xff00) >> 8;

	cpu.B = msb;
	cpu.C = lsb;
}

uint16_t getAF(){
	return (cpu.A << 8) | cpu.F;
}

void setAF(uint16_t value){
	unsigned short msb;
	unsigned short lsb;

	lsb = value & 0x00ff;
	msb = (value & 0xff00) >> 8;

	cpu.A = msb;
	cpu.F = lsb;
}

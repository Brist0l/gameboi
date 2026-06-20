#include "cpu.h"
#include "debug.h"

#define GET6BIT 0b01000000
#define GETZFLG 0b01111111
#define GETNFLG 0b10111111
#define GETHFLG 0b11011111
#define GETCFLG 0b11101111

// if val = 1:
// 0b01010101 => 0b11010101
// 0b11010101 => 0b11010101
//
// if val = 0:

// 0b11010101 => 0b01010101
void setz(const unsigned short val){

	dprintf("Register value F before setting Z to %b: 0b%08b\n",val,cpu.F);

	unsigned short restofbits = cpu.F & GETZFLG;

	if(val == 1)
		cpu.F = 0b10000000 | restofbits; else if(val == 0) cpu.F = 0b01111111 & restofbits;

	dprintf("Register value F after setting Z to %b : 0b%08b\n",val,cpu.F);
}

int getz(){
	return ((cpu.F & 0b10000000) >> 7);
}

// if val = 1:
// 0b01010101 => 0b01010101
// 0b11010101 => 0b11010101
//
// if val = 0:
// 0b01010101 => 0b00010101
// 0b11010101 => 0b10010101
void setn(const unsigned short val){
	dprintf("Register value F before setting N to %b : 0b%08b\n",val,cpu.F);

	unsigned short restofbits = cpu.F & GETNFLG;

	if(val == 1)
		cpu.F = 0b01000000 | restofbits;
	else if(val == 0)
		cpu.F = 0b10111111 & restofbits;

	dprintf("Register value F after setting N to %b : 0b%08b\n",val,cpu.F);
}

int getn(){
	return ((cpu.F & 0b01000000) >> 6);
}

void seth(const unsigned short val){
	dprintf("Register value F before setting H to %b : 0b%08b\n",val,cpu.F);

	unsigned short restofbits = cpu.F & GETHFLG;

	if(val == 1)
		cpu.F = 0b00100000 | restofbits;
	else if(val == 0)
		cpu.F = 0b11011111 & restofbits;

	dprintf("Register value F after setting H to %b : 0b%08b\n",val,cpu.F);
}

int geth(){
	return ((cpu.F & 0b00100000) >> 5);
}

void setc(const unsigned short val){
	dprintf("Register value F before setting C to %b : 0b%08b\n",val,cpu.F);

	unsigned short restofbits = cpu.F & GETCFLG;

	if(val == 1)
		cpu.F = 0b00010000 | restofbits;
	else if(val == 0)
		cpu.F = 0b11101111 & restofbits;

	dprintf("Register value F after setting C to %b : 0b%08b\n",val,cpu.F);
}

int getC(){
	return ((cpu.F & 0b00010000) >> 4);
}

void setADDflags(uint8_t a,uint8_t b,uint8_t result){
	if(result == 0)
		setz(1);
	else
		setz(0);

	setn(0);
	seth(((a & 0xF) + (b & 0xF)) > 0xF);
	setc(((uint16_t)a + (uint16_t)b) > 0xFF);
}

void setADCflags(uint8_t a,uint8_t b,uint8_t c){
	if(a == 0)
		setz(1);
	else
		setz(0);

	setn(0);
	seth(((a & 0xF) + (b & 0xF) + c) > 0xF);
	setc(((uint16_t)a + (uint16_t)b + c) > 0xFF);
}

void setSUBflags(uint8_t a,uint8_t b){
	if(a == 0)
		setz(1);
	else
		setz(0);

	setn(1);
	seth((a & 0xF) < (b & 0xF));
	setc(a < b);
}

void setINCflags(uint8_t r,uint8_t result){
	if(result == 0)
		setz(1);
	else
		setz(0);

	setn(0);
	seth((((r) & 0x0f) + 1) > 0xF);
}

void setDECflags(uint8_t r,uint8_t result){
	if(result == 0)
		setz(1);
	else
		setz(0);

	setn(1);
	seth((r & 0xF)  < 1);
}

void setORflags(uint8_t r,uint8_t result){
	if(result == 0)
		setz(1);
	else
		setz(0);

	setn(0);
	seth(0);
	setc(0);
}

void setXORflags(uint8_t r){
	if(r == 0)
		setz(1);
	else
		setz(0);

	setn(0);
	seth(0);
	setc(0);
}

void setANDflags(uint8_t r){
	if(r == 0)
		setz(1);
	else
		setz(0);

	setn(0);
	seth(1);
	setc(0);
}

void setSWAPflags(uint8_t r){

	setz(r == 0);
	setn(0);
	seth(0);
	setc(0);

}

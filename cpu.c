#include<stdio.h>
#include<stdint.h>

#include "cpu.h"
#include "memory.h"
#include "debug.h"

#define GET7BIT 0b10000000
#define GET6BIT 0b01000000
#define GETZFLG 0b01111111
#define GETNFLG 0b10111111
#define GETHFLG 0b11011111
#define GETCFLG 0b11101111

/* CPU is little endian. The property is of how bytes are stored in
 * the memory and not of the "CPU" itself. CPU is the dumbest layer
 * but the fastest , the endianness comes on top of that layer.
 * i.e. someone else will interpret the endianness for it , it will
 * just work with the bytes. Another thing is that CPU hence works
 * on multiples of 4 so that it's easy to maintain endianness.
 * 0x1234 gets stored as 34 12 in little endian. 0x123456 gets
 * converted to 0x00123456 and now is stored as 56 34 12 00.*/

struct registers cpu;

// if val = 1:
// 0b01010101 => 0b11010101
// 0b11010101 => 0b11010101
//
// if val = 0:
// 0b01010101 => 0b01010101
// 0b11010101 => 0b01010101
void setz(const unsigned short val){
	dprintf("Register value F before setting Z to %b : 0b%08b\n",val,cpu.F);

	unsigned short restofbits = cpu.F & GETZFLG;

	if(val == 1)
		cpu.F = 0b10000000 | restofbits;
	else if(val == 0)
		cpu.F = 0b01111111 & restofbits;

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

void execute(unsigned int file_size){
	logmsg("execute",true);
	unsigned short msb;
	unsigned short lsb;
	unsigned short u16;
	unsigned short u8;
	unsigned short seventh_bit;
	uint8_t addr;

	uint16_t HL;


	if(cpu.PC >= 0x00a8 && cpu.PC < 0x00e0){
		dprintf(ANSI_COLOR_BLUE);
		dprintf(".DB:\t");
		dprintf(ANSI_COLOR_RESET);
		dprintf(ANSI_COLOR_GREEN);
		dprintf("0x%02x\n",memory[cpu.PC]);
		dprintf(ANSI_COLOR_RESET);
	}

	unsigned char opcode = memory[cpu.PC];
	HL = (cpu.H << 8) | cpu.L;

	//printf(ANSI_COLOR_RED);
	//dprintf("0x%04x\t",i);
	//printf(ANSI_COLOR_RESET);

	//printf(ANSI_COLOR_GREEN);

	dprintf("\nRegister PC before: 0x%04x\n\n",cpu.PC);
	dprintf("opcode: 0x%02x\n",opcode);

	switch(opcode){
		case 0x04:
			// INC B
			// lenght is 1 byte

			printf("INC B\n");
			break;

		case 0x05:
			// DEC B
			// lenght is 1 byte

			printf("DEC B\n");
			break;

		case 0x06:
			// LOAD B,u8
			// lenght is 2 bytes

			u8 = memory[++cpu.PC];
			dprintf("u8: 0x%02x\n",u8);

			printf("LD B, 0x%02x\n",u8);
			break;


		case 0x0c:
			// INCREASE C
			// lenght is 1 byte

			printf("INC C\n");
			break;

		case 0x0d:
			// DECREASE C
			// lenght is 1 byte
			printf("DEC C\n");
			break;

		case 0x0e:
			// LOAD C , u8
			// lenght is 2 bytes
			// Put the values of u8 into C

			dprintf("LD C, u8\n");

			dprintf("Register C value before : 0x%02x\n",cpu.C);
			u8 = memory[++cpu.PC];
			dprintf("u8: 0x%02x\n",u8);

			dprintf("LD C, 0x%02x\n",u8);

			cpu.C = u8;
			dprintf("Register C value after : 0x%02x\n",cpu.C);

			break;

		case 0x11:
			// LOAD DE, u16
			// lenght is 3 bytes

			lsb = memory[++cpu.PC];
			dprintf("LSB: 0x%04x\n",lsb);
			dprintf("LSB: 0b%b\n",lsb);

			msb = memory[++cpu.PC];
			dprintf("MSB: 0x%04x\n",msb);
			dprintf("MSB: 0b%b\n",msb);

			u16 = (msb << 8) | lsb;
			dprintf("u16: 0x%04x\n",u16);

			printf("LD DE, 0x%04x\n",u16);

			break;

		case 0x13:
			// INC DE
			// lenght is 1 byte

			printf("INC DE\n");
			break;

		case 0x15:
			// DEC D
			// lenght is 1 byte

			printf("DEC D\n");
			break;

		case 0x16:
			// LOAD D , u8
			// lenght is 2 bytes

			u8 = memory[++cpu.PC];
			dprintf("u8: 0x%02x\n",u8);

			printf("LD D, 0x%02x\n",u8);
			break;

		case 0x17:
			// RLA
			// lenght is 1 byte

			printf("RLA\n");
			break;

		case 0x18:
			// JR u8
			// JUMP to (current addr + u8)
			// lenght is 2 bytes

			addr = memory[++cpu.PC];
			dprintf("Add by: 0x%2x\n",addr);
			dprintf("Add by: %d\n",addr);

			addr += cpu.PC + 1; // address is calculated after the instruction hence
				     // the +1
			dprintf("Address is: 0x%04x\n",addr);

			printf("JR (0x%04x)\n",addr);

			break;

		case 0x1a:
			// LOAD A,(DE)
			// lenght is 1 byte

			printf("LD A, (DE)\n");
			break;

		case 0x1d:
			// DECREASE E
			// lenght is 1 byte

			printf("DEC E\n");
			break;

		case 0x1e:
			// LOAD E,u8
			// lenght is 2 bytes

			u8 = memory[++cpu.PC];
			dprintf("u8: 0x%02x\n",u8);

			printf("LD E, 0x%02x\n",u8);
			break;

		case 0x20:
			// JUMP if NotZero to addr
			// lenght is 2 bytes
			// if Z flag is 0:
			// jump to (current_addr + addr)

			dprintf("JR NZ, u8\n");

			addr = memory[++cpu.PC];
			dprintf("Add by(u8) : 0x%2x (0d%d) \n",addr,addr);

			addr += cpu.PC + 1; // address is calculated after the instruction hence
				     	   // the +1
			dprintf("Address is: 0x%04x\n",addr);
			dprintf("JR NZ, (0x%04x)\n",addr);
			dprintf("Z : 0b%b\n",getz());

			if(getz() == 0)
				cpu.PC = addr - 1; //as a +1 will happen after the end of switch case

			break;

		case 0x21:
			// LOAD HL,u16
			// 16-bit load instruction
			// length is 3 bytes
			// Put u16's msb in H and lsb in L

			dprintf("LD HL, u16\n");
			lsb = memory[++cpu.PC];
			dprintf("LSB: 0x%04x\n",lsb);
			dprintf("LSB: 0b%b\n",lsb);

			msb = memory[++cpu.PC];
			dprintf("MSB: 0x%04x\n",msb);
			dprintf("MSB: 0b%b\n",msb);

			u16 = (msb << 8) | lsb;
			dprintf("u16: 0x%04x\n",u16);

			dprintf("LD HL, 0x%04x\n",u16);

			dprintf("HL register before: 0x%04x\n",(cpu.H<< 8) | cpu.L);
			cpu.H = msb;
			cpu.L = lsb;

			dprintf("HL register before: 0x%04x\n",(cpu.H<< 8) | cpu.L);


			break;

		case 0x22:
			// LOAD (HL+),A
			// lenght is 1 byte
			// put data of A at the memoryory location of HL and
			// increment HL

			printf("LD (HL+), A\n");
			break;

		case 0x23:
			// INC HL
			// lenght is 1 byte

			printf("INC HL\n");
			break;

		case 0x24:
			// INC HL
			// lenght is 1 byte

			printf("INC H\n");
			break;

		case 0x28:
			// JR Z, u8
			// JUMP if Zero to (current addr + n)
			// lenght is 2 bytes

			addr = memory[++cpu.PC];
			dprintf("Add by: 0x%2x\n",addr);
			dprintf("Add by: %d\n",addr);

			addr += cpu.PC + 1; // address is calculated after the instruction hence
				     // the +1
			dprintf("Address is: 0x%04x\n",addr);

			printf("JR Z, (0x%04x)\n",addr);

			break;

		case 0x2e:
			// LOAD L , u8
			// lenght is 2 bytes

			u8 = memory[++cpu.PC];
			dprintf("u8: 0x%02x\n",u8);

			printf("LD L, 0x%02x\n",u8);
			break;

		case 0x30:
			// JR NC, u8
			// JUMP if NotC to (current addr + n)
			// lenght is 2 bytes

			addr = memory[++cpu.PC];
			dprintf("Add by: 0x%2x\n",addr);
			dprintf("Add by: %d\n",addr);

			addr += cpu.PC + 1; // address is calculated after the instruction hence
				     // the +1
			dprintf("Address is: 0x%04x\n",addr);

			printf("JR NC, (0x%04x)\n",addr);

			break;


		case 0x31:
			// LOAD SP,u16
			// 16-bit load instruction
			// length is 3 bytes
			// put the u16 in the SP register

			dprintf("LD SP, u16\n");

			lsb = memory[++cpu.PC];
			dprintf("LSB: 0x%04x\n",lsb);
			dprintf("LSB: 0b%b\n",lsb);

			msb = memory[++cpu.PC];
			dprintf("MSB: 0x%04x\n",msb);
			dprintf("MSB: 0b%b\n",msb);

			u16 = (msb << 8) | lsb;
			dprintf("u16: 0x%04x\n",u16);

			dprintf("LD SP, 0x%04x\n",u16);

			dprintf("SP Register value before: 0x%04x\n",cpu.SP);
			cpu.SP = u16;
			dprintf("SP Register value after: 0x%04x\n",cpu.SP);

			break;

		case 0x32:
			// LOAD (HL-),A
			// 16-bit load instruction
			// length is 1 bytes
			// Put A into memory address HL and then decrement HL

			dprintf("LD (HL-), A\n");
			dprintf("HL Register before: 0x%04x\n",HL);
			dprintf("H Register before: 0x%04x\n",cpu.H);
			dprintf("L Register before: 0x%04x\n",cpu.L);
			dprintf("A Register before: 0x%02x\n",cpu.A);
			dprintf("memory at HL before: 0x%02x\n",memory[HL]);

			memory[HL] = cpu.A;
			HL--;

			lsb = HL & 0x00ff;
			msb = (HL & 0xff00) >> 8;

			cpu.H = msb;
			cpu.L = lsb;

			dprintf("HL Register after: 0x%04x\n",HL);
			dprintf("H Register after: 0x%02x\n",cpu.H);
			dprintf("L Register after: 0x%02x\n",cpu.L);
			dprintf("A Register after: 0x%02x\n",cpu.A);
			dprintf("memory at HL after: 0x%02x\n",memory[HL + 1]);

			break;

		case 0x38:
			// JR C, u8
			// JUMP if C , to (current addr + n)
			// lenght is 2 bytes

			addr = memory[++cpu.PC];
			dprintf("Add by: 0x%2x\n",addr);
			dprintf("Add by: %d\n",addr);

			addr += cpu.PC + 1; // address is calculated after the instruction hence
				     // the +1
			dprintf("Address is: 0x%04x\n",addr);

			printf("JR C, (0x%04x)\n",addr);

			break;

		case 0x3d:
			// DEC A
			// lenght is 1 byte

			printf("DEC A\n");

			break;

		case 0x3e:
			// LOAD A , u8
			// lenght is 2 bytes

			dprintf("LD A, u8\n");
			dprintf("Register A value before : 0x%04x\n",cpu.A);

			u8 = memory[++cpu.PC];
			dprintf("u8: 0x%02x\n",u8);

			dprintf("LD A, 0x%02x\n",u8);

			cpu.A = u8;

			dprintf("Register A value before : 0x%04x\n",cpu.A);
			break;

		case 0x47:
			// LOAD B,A
			// lenght is 1 byte

			printf("LD B, A\n");
			break;

		case 0x4f:
			// LOAD C,A
			// lenght is 1 byte

			printf("LD C, A\n");
			break;

		case 0x57:
			// LOAD D,A
			// lenght is 1 byte

			printf("LD D, A\n");
			break;

		case 0x67:
			// LOAD H,A
			// lenght is 1 byte

			printf("LD H, A\n");
			break;

		case 0x77:
			// LOAD (HL),A
			// lenght is 1 byte
			// put data of A into HL

			printf("LD HL, A\n");
			break;

		case 0x78:
			printf("LD A, B\n");
			break;

		case 0x7b:
			// LOAD A,E
			// lenght is 1 byte

			printf("LD A, E\n");
			break;

		case 0x7c:
			// LOAD A,H
			// lenght is 1 byte

			printf("LD A, H\n");
			break;

		case 0x7D:
			printf("LD A, L\n");
			break;

		case 0x86:
			// ADD A,(HL)
			// lenght is 1 byte
			// add value in HL to A

			printf("ADD A, (HL)\n");
			break;

		case 0x90:
			// SUB A , B
			// lenght is 1 byte
			// subtract B from A

			printf("SUB B\n");
			break;

		case 0xaf:
			// XOR A
			// ALU operation
			// lenght is 1 byte
			// XOR's the value which is in A with A and stores in A

			dprintf("XOR A, A\n");
			dprintf("A Register value before: 0x%02x\n",cpu.A);
			cpu.A ^= cpu.A;
			dprintf("A Register value after: 0x%02x\n",cpu.A);

			break;

		case 0xbe:
			printf("CP A, (HL)\n");
			break;

		case 0xc1:
			// POP BC
			// lenght is 1 byte

			printf("POP BC\n");

			break;


		case 0xc5:
			// PUSH BC
			// lenght is 1 byte
			// PUSH's the value which is in BC
			// and decrements the SP twice

			printf("PUSH BC\n");

			break;

		case 0xc9:
			// RET
			// lenght is 1 byte

			printf("RET\n");

			break;

		case 0xcb:
			// PREFIX CB

			unsigned int nxtbyt = memory[++cpu.PC];

			switch(nxtbyt){
				case 0x11:
					// RL C
					// lenght is 2 bytes

					printf("RL C\n");
					break;

				case 0x4f:
					// BIT 1,A
					// lenght is 2 bytes

					printf("BIT 1,A\n");
					break;

				case 0x7c:
					// BIT 7,H
					// lenght is 2 bytes
					// basically get the 7th bit
					// of H and see if it's 1 or 0
					// changes:
					//
					// Z = 1 ( if bit is 0)
					// Z = 0 ( if bit is 1)
					// N = 0
					// H = 1
					// C = same


					printf("BIT 7,H\n");
					dprintf("value of register H is : 0b%b\n",cpu.H);

					seventh_bit = cpu.H & GET7BIT;
					seventh_bit >>= 7;

					dprintf("value of seventh bit of H is : 0b%b\n",seventh_bit);

					setz(!seventh_bit);
					setn(0);
					seth(1);

					break;

				default:
					printf("NULL RN\n");
					break;
			}

			break;
		case 0xcd:
			// CALL u16
			// lenght is 3 bytes

			lsb = memory[++cpu.PC];
			dprintf("LSB: 0x%04x\n",lsb);
			dprintf("LSB: 0b%b\n",lsb);

			msb = memory[++cpu.PC];
			dprintf("MSB: 0x%04x\n",msb);
			dprintf("MSB: 0b%b\n",msb);

			u16 = (msb << 8) | lsb;
			dprintf("u16: 0x%04x\n",u16);

			printf("CALL 0x%04x\n",u16);

			break;

		case 0xd5:
			// PUSH DE
			// lenght is 1 byte
			// PUSH's the value which is in DE
			// and decrements the SP twice

			printf("PUSH DE\n");

			break;

		case 0xe0:
			// LOAD (FF00 + u8),A
			// lenght is 2 bytes
			// Put A into addr of val u8+ 0xff00

			u8 = memory[++cpu.PC];
			dprintf("u8: 0x%02x\n",u8);

			printf("LD (0xff00 + 0x%02x),A\n",u8);
			break;

		case 0xe2:
			// LOAD (FF00 + C), A
			// lenght is 1 byte
			// Put A into addr of val at C + 0xff00

			printf("LD (0xff00 + C),A\n");

			break;

		case 0xe5:
			// PUSH HL
			// lenght is 1 byte
			// PUSH's the value which is in HL
			// and decrements the SP twice

			printf("PUSH HL\n");

			break;

		case 0xea:
			// LD u16, A
			// lenght is 3 bytes

			lsb = memory[++cpu.PC];
			dprintf("LSB: 0x%04x\n",lsb);
			dprintf("LSB: 0b%b\n",lsb);

			msb = memory[++cpu.PC];
			dprintf("MSB: 0x%04x\n",msb);
			dprintf("MSB: 0b%b\n",msb);

			u16 = (msb << 8) | lsb;
			dprintf("u16: 0x%04x\n",u16);

			printf("LD 0x%04x, A\n",u16);

			break;

		case 0xf0:
			// LOAD A , (0xFF00 + u8)
			// lenght is 2 bytes
			// put the memory addr (0xff00 + u8) into A

			u8 = memory[++cpu.PC];
			dprintf("u8: 0x%02x\n",u8);

			printf("LD A, (0xff00 + 0x%02x),A\n",u8);

			break;

		case 0xf5:
			// PUSH AF
			// lenght is 1 byte
			// PUSH's the value which is in AF
			// and decrements the SP twice

			printf("PUSH AF\n");

			break;

		case 0xfe:
			// COMPARE A,u8
			// lenght is 2 bytes
			// Basically sets flag after A-u8 and throws away the result

			u8 = memory[++cpu.PC];
			dprintf("u8: 0x%02x\n",u8);

			printf("CP 0x%02x\n",u8);
			break;

		default:
			printf("\n");
			break;

	}

	cpu.PC++;
	printf("\nRegister PC after: 0x%04x\n",cpu.PC);
	logmsg("execute",false);
}

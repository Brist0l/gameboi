#include<stdio.h>
#include<stdint.h>
#include<unistd.h>

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

// 0b11010101 => 0b01010101
void setz(const unsigned short val){
	dprintf("Register value F before setting Z to %b: 0b%08b\n",val,cpu.F);

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

void execute(){
	logmsg("execute",true);
	unsigned short msb;
	unsigned short lsb;
	unsigned short u16;
	unsigned short u8;
	unsigned short seventh_bit;
	uint8_t addr;

	uint16_t HL;
	uint16_t BC;

	if(cpu.PC >= 0x00a8 && cpu.PC < 0x00e0){
		dprintf(ANSI_COLOR_BLUE);
		dprintf(".DB:\t");
		dprintf(ANSI_COLOR_RESET);
		dprintf(ANSI_COLOR_GREEN);
		dprintf("0x%02x\n",memory[cpu.PC]);
		dprintf(ANSI_COLOR_RESET);
	}

	unsigned char opcode = memory[cpu.PC];

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

			dprintf("INC B\n");
			dprintf("Value of register B before is: 0x%04x\n",cpu.B);
			cpu.B++;
			dprintf("Value of register B after is: 0x%04x\n",cpu.B);
			break;

		case 0x05:
			// DEC B
			// lenght is 1 byte

			dprintf("DEC B\n");

			dprintf("Value of register B before is: 0x%02x\n",cpu.B);

			cpu.B--;

			if(cpu.B == 0)
				setz(1);
			else
				setz(0);

			dprintf("Value of register B after is: 0x%02x\n",cpu.B);
			break;

		case 0x06:
			// LOAD B,u8
			// lenght is 2 bytes
			// Put u8 into B

			u8 = memory[++cpu.PC];
			dprintf("u8: 0x%02x\n",u8);

			dprintf("LD B, 0x%02x\n",u8);
			dprintf("Value of Register B before: 0x%02x\n",cpu.B);

			cpu.B = u8;

			dprintf("Value of Register B before: 0x%02x\n",cpu.B);

			break;


		case 0x0c:
			// INCREASE C
			// lenght is 1 byte
			// increase val of C by 1

			dprintf("INC C\n");
			dprintf("Value of Register C before: 0x%02x\n",cpu.C);

			cpu.C++;

			dprintf("Value of Register C after: 0x%02x\n",cpu.C);
			break;

		case 0x0d:
			// DECREASE C
			// lenght is 1 byte

			dprintf("DEC C\n");
			dprintf("Value of register C before is: 0x%04x\n",cpu.C);
			cpu.C--;
			dprintf("Value of register C after is: 0x%04x\n",cpu.C);

			//sleep(1);
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

			//sleep(5);

			break;

		case 0x11:
			// LOAD DE, u16
			// lenght is 3 bytes
			// store u16 in DE

			lsb = memory[++cpu.PC];
			dprintf("LSB: 0x%04x\n",lsb);
			dprintf("LSB: 0b%b\n",lsb);

			msb = memory[++cpu.PC];
			dprintf("MSB: 0x%04x\n",msb);
			dprintf("MSB: 0b%b\n",msb);

			u16 = (msb << 8) | lsb;
			dprintf("u16: 0x%04x\n",u16);

			dprintf("LD DE, 0x%04x\n",u16);

			dprintf("Value of Register DE before: 0x%04x\n",getDE());

			setDE(u16);

			dprintf("Value of Register DE after: 0x%04x\n",getDE());

			break;

		case 0x13:
			// INC DE
			// lenght is 1 byte

			dprintf("INC DE\n");

			dprintf("Value of Register DE before: 0x%04x\n",getDE());

			setDE(getDE() + 1);

			dprintf("Value of Register DE after: 0x%04x\n",getDE());


			break;

		case 0x15:
			// DEC D
			// lenght is 1 byte

			dprintf("DEC D\n");

			dprintf("Value of register D before is: 0x%02x\n",cpu.D);

			cpu.D--;

			if(cpu.D == 0)
				setz(1);
			else
				setz(0);

			dprintf("Value of register D after is: 0x%02x\n",cpu.D);
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
			// Same as RLC but Z flag always 0

			dprintf("RLA\n");

			dprintf("C Flag before is: 0b%b\n",getC());
			dprintf("Register A before is: 0x%2x\n",cpu.A);
			dprintf("Register A before is: 0b%b\n",cpu.A);

			lsb = getC();
			setc(cpu.C >> 7);

			cpu.A <<= 1;
			cpu.A = lsb | cpu.A ;

			dprintf("C Flag after is: 0b%b\n",getC());
			dprintf("Register A after is: 0x%2x\n",cpu.A);
			dprintf("Register A after is: 0b%b\n",cpu.A);

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

			dprintf("JR (0x%04x)\n",addr);

			cpu.PC = addr - 1;

			break;

		case 0x1a:
			// LOAD A,(DE)
			// lenght is 1 byte
			// put contents at addr specified by DE into A

			printf("LD A, (DE)\n");
			printf("Value of Register DE is: 0x%04x\n",getDE());
			printf("Value of Register A before is: 0x%02x\n",cpu.A);
			printf("Value at 0x%04x is: 0x%02x\n",getDE(),memory[getDE()]);

			cpu.A = memory[getDE()];

			printf("Value of Register A after is: 0x%02x\n",cpu.A);

			break;

		case 0x1d:
			// DECREASE E
			// lenght is 1 byte

			dprintf("DEC E\n");
			dprintf("Value of register E before is: 0x%02x\n",cpu.E);

			cpu.E--;

			if(cpu.E == 0)
				setz(1);
			else
				setz(0);

			dprintf("Value of register D after is: 0x%02x\n",cpu.E);
			break;

		case 0x1e:
			// LOAD E,u8
			// lenght is 2 bytes

			u8 = memory[++cpu.PC];
			dprintf("u8: 0x%02x\n",u8);

			dprintf("LD E, 0x%02x\n",u8);

			dprintf("Register E value before : 0x%02x\n",cpu.E);

			cpu.E = u8;

			dprintf("Register E value after : 0x%02x\n",cpu.E);
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

			if(getz() == 0){
				dprintf("Jumping to 0x%04x\n",addr);
				cpu.PC = addr - 1; //as a +1 will happen after the end of switch case
			}
			else{
				dprintf("Not Jumping\n");
			}

			//sleep(1);

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

			dprintf("HL register before: 0x%04x\n",getHL());

			setHL(u16);

			dprintf("HL register after: 0x%04x\n",getHL());


			break;

		case 0x22:
			// LOAD (HL+),A
			// lenght is 1 byte
			// put data of A at the memory location of HL and
			// increment HL

			dprintf("LD (HL+), A\n");

			dprintf("HL Register before: 0x%04x\n",getHL());
			dprintf("H Register before: 0x%02x\n",cpu.H);
			dprintf("L Register before: 0x%02x\n",cpu.L);
			dprintf("Value of Register A : 0x%02x\n",cpu.A);
			dprintf("memory at HL before: 0x%02x\n",memory[getHL()]);

			HL = getHL();

			memory[HL] = cpu.A;
			HL++;
			setHL(HL);

			dprintf("HL Register after: 0x%04x\n",getHL());
			dprintf("H Register after: 0x%02x\n",cpu.H);
			dprintf("L Register after: 0x%02x\n",cpu.L);
			dprintf("memory at HL after: 0x%02x\n",memory[getHL() - 1]);

			break;

		case 0x23:
			// INC HL
			// lenght is 1 byte
			// Add 1 to HL

			dprintf("INC HL\n");

			dprintf("HL Register before: 0x%04x\n",getHL());
			dprintf("H Register before: 0x%02x\n",cpu.H);
			dprintf("L Register before: 0x%02x\n",cpu.L);

			HL = getHL();
			HL++;
			setHL(HL);

			dprintf("HL Register after: 0x%04x\n",getHL());
			dprintf("H Register after: 0x%02x\n",cpu.H);
			dprintf("L Register after: 0x%02x\n",cpu.L);

			break;

		case 0x24:
			// INC HL
			// lenght is 1 byte

			printf("INC H\n");
			break;

		case 0x28:
			// JR Z, u8
			// JUMP if Zero flag is 1 to (current addr + n)
			// lenght is 2 bytes

			addr = memory[++cpu.PC];

			dprintf("Add by: 0x%2x\n",addr);
			dprintf("Add by: %d\n",addr);

			addr += cpu.PC + 1; // address is calculated after the instruction hence
				     	   // the +1
			dprintf("Address is: 0x%04x\n",addr);


			dprintf("Address is: 0x%04x\n",addr);
			dprintf("JR Z, (0x%04x)\n",addr);
			dprintf("Z : 0b%b\n",getz());

			if(getz() == 1){
				dprintf("Jumping to 0x%04x\n",addr);
				cpu.PC = addr - 1; //as a +1 will happen after the end of switch case
			}
			else{
				dprintf("Not Jumping\n");
			}

			break;

		case 0x2e:
			// LOAD L , u8
			// lenght is 2 bytes
			// Put the value of u8 in the L register

			u8 = memory[++cpu.PC];
			dprintf("u8: 0x%02x\n",u8);

			dprintf("LD L, 0x%02x\n",u8);
			dprintf("Value of register L before : 0x%02x\n",cpu.L);

			cpu.L = u8;

			dprintf("Value of register L after : 0x%02x\n",cpu.L);

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
			dprintf("HL Register before: 0x%04x\n",getHL());
			dprintf("H Register before: 0x%04x\n",cpu.H);
			dprintf("L Register before: 0x%04x\n",cpu.L);
			dprintf("Value of Register A : 0x%02x\n",cpu.A);
			dprintf("memory at HL before: 0x%02x\n",memory[getHL()]);

			HL = getHL();

			memory[HL] = cpu.A;
			HL--;
			setHL(HL);

			dprintf("HL Register after: 0x%04x\n",getHL());
			dprintf("H Register after: 0x%02x\n",cpu.H);
			dprintf("L Register after: 0x%02x\n",cpu.L);
			dprintf("memory at HL after: 0x%02x\n",memory[getHL() + 1]);

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

			dprintf("DEC A\n");

			dprintf("Value of register A before is: 0x%02x\n",cpu.A);

			cpu.A--;

			if(cpu.A == 0)
				setz(1);
			else
				setz(0);

			dprintf("Value of register A after is: 0x%02x\n",cpu.A);

			break;

		case 0x3e:
			// LOAD A , u8
			// lenght is 2 bytes

			dprintf("LD A, u8\n");
			dprintf("Register A value before : 0x%02x\n",cpu.A);

			u8 = memory[++cpu.PC];
			dprintf("u8: 0x%02x\n",u8);

			dprintf("LD A, 0x%02x\n",u8);

			cpu.A = u8;

			dprintf("Register A value after : 0x%02x\n",cpu.A);
			break;

		case 0x47:
			// LOAD B,A
			// lenght is 1 byte

			printf("LD B, A\n");
			break;

		case 0x4f:
			// LOAD C,A
			// lenght is 1 byte
			// Put value of A into C

			dprintf("LD C, A\n");
			dprintf("Register C value before : 0x%02x\n",cpu.C);
			dprintf("Register A value : 0x%02x\n",cpu.A);

			cpu.C = cpu.A;

			dprintf("Register C value after : 0x%02x\n",cpu.C);

			break;

		case 0x57:
			// LOAD D,A
			// lenght is 1 byte

			dprintf("LD D, A\n");

			dprintf("Register D value before : 0x%02x\n",cpu.D);
			dprintf("Register A value : 0x%02x\n",cpu.A);

			cpu.D = cpu.A;

			dprintf("Register H value after : 0x%02x\n",cpu.D);

			break;

		case 0x67:
			// LOAD H,A
			// lenght is 1 byte
			// Put the contents of A into the H register

			dprintf("LD H, A\n");
			dprintf("Register H value before : 0x%02x\n",cpu.H);
			dprintf("Register A value : 0x%02x\n",cpu.A);

			cpu.H = cpu.A;

			dprintf("Register H value after : 0x%02x\n",cpu.H);

			break;

		case 0x77:
			// LOAD (HL),A
			// lenght is 1 byte
			// put data of A into memory of HL

			dprintf("LD HL, A\n");
			dprintf("Value of Register HL : 0x%04x\n",getHL());
			dprintf("Value of Register A : 0x%02x\n",cpu.A);
			dprintf("before : 0x%02x is at 0x%04x\n",memory[getHL()],getHL());
			memory[getHL()] = cpu.A;

			dprintf("after : 0x%02x is at 0x%04x\n",memory[getHL()],getHL());

			break;

		case 0x78:
			// LOAD A,B
			// lenght is 1 byte
			// Put contents of B into A
			
			dprintf("LD A, B\n");
			dprintf("Register A value before : 0x%02x\n",cpu.A);
			dprintf("Register B value : 0x%02x\n",cpu.B);

			cpu.A = cpu.B;

			dprintf("Register A value after : 0x%02x\n",cpu.A);

			break;

		case 0x7b:
			// LOAD A,E
			// lenght is 1 byte
			// Put contents of E into A

			dprintf("LD A, E\n");

			dprintf("Register A value before : 0x%02x\n",cpu.A);
			dprintf("Register E value : 0x%02x\n",cpu.E);

			cpu.A = cpu.E;

			dprintf("Register A value after : 0x%02x\n",cpu.A);

			break;

		case 0x7c:
			// LOAD A,H
			// lenght is 1 byte
			// Put contents of H into A

			dprintf("LD A, H\n");
			dprintf("Register A value before : 0x%02x\n",cpu.A);
			dprintf("Register H value : 0x%02x\n",cpu.H);

			cpu.A = cpu.H;

			dprintf("Register A value after : 0x%02x\n",cpu.A);
			break;

		case 0x7d:
			// LOAD A ,L
			// lenght is 1 byte
			// Put contents of L into A
			
			dprintf("LD A, L\n");
			dprintf("Register A value before : 0x%02x\n",cpu.A);
			dprintf("Register L value : 0x%02x\n",cpu.L);

			cpu.A = cpu.L;

			dprintf("Register A value after : 0x%02x\n",cpu.A);
			
			break;

		case 0x86:
			// ADD A,(HL)
			// lenght is 1 byte
			// add value at the addr HL to A
			// and store in A

			dprintf("ADD A, (HL)\n");
			dprintf("Value of Register HL : 0x%04x\n",getHL());
			dprintf("Value of Register A before: 0x%02x\n",cpu.A);
			dprintf("0x%02x is at 0x%04x\n",memory[getHL()],getHL());

			cpu.A += memory[getHL()];

			dprintf("Value of Register A after: 0x%02x\n",cpu.A);

			break;

		case 0x90:
			// SUB A , B
			// lenght is 1 byte
			// subtract B from A

			dprintf("SUB B\n");
			dprintf("Value of register A before : 0x%02x\n",cpu.A);
			dprintf("Value of register B : 0x%02x\n",cpu.B);

			cpu.A -= cpu.B;

			dprintf("Value of register A after : 0x%02x\n",cpu.A);
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
			// COMPARE A , (HL)
			// Same as CP u8 but this time compare with the content
			// at the addr (HL)
			// Basically sets flag after A-memory[HL] and throws away the result
			// So if A == memory[HL] then A - memory[HL] is 0
			// hence ,
			// Z = 1

			dprintf("CP A, (HL)\n");
			dprintf("Value of Register HL is: 0x%04x\n",getHL());
			dprintf("Value of Register A is: 0x%04x\n",cpu.A);
			dprintf("Value at 0x%04x is: 0x%04x\n",getHL(),memory[getHL()]);

			if(cpu.A - memory[getHL()] == 0){
				dprintf("Setting Zero flag to 1\n");
				setz(1);
			}else{
				dprintf("Setting Zero flag to 0\n");
				setz(0);
			}

			break;

		case 0xc1:
			// POP BC
			// lenght is 1 byte

			dprintf("POP BC\n");
			dprintf("SP before: 0x%04x\n",cpu.SP);

			lsb = pop(); // C
			msb = pop();  // B

			u16 = (msb << 8) | lsb;

			setBC(u16);

			dprintf("Value of register BC : 0x%04x\n",getBC());
			dprintf("SP after: 0x%04x\n",cpu.SP);

			break;


		case 0xc5:
			// PUSH BC
			// lenght is 1 byte
			// PUSH's the value which is in BC
			// and decrements the SP twice

			dprintf("PUSH BC\n");

			BC = getBC();

			dprintf("SP val before: 0x%04x\n",cpu.SP);
			dprintf("Value of Register BC is 0x%04x\n",BC);

			lsb = BC & 0x00ff; 	  // C
			msb = (BC & 0xff00) >> 8; // B

			push(msb);
			push(lsb);

			dprintf("Pushed 0x%02x to stack\n",lsb);
			dprintf("Pushed 0x%02x to stack\n",msb);

			dprintf("stack: \n0x%02x\n0x%02x\n",msb,lsb);

			dprintf("Pushed 0x%04x to stack\n",BC);
			dprintf("SP val after: 0x%04x\n",cpu.SP);

			break;

		case 0xc9:
			// RET
			// lenght is 1 byte
			// POP the stack and put it into the PC

			dprintf("RET\n");
			dprintf("SP before: 0x%04x\n",cpu.SP);

			lsb = pop(); // P of the PC
			msb = pop();  // C of the PC

			u16 = (msb << 8) | lsb;

			cpu.PC = u16;

			dprintf("Value of register PC : 0x%04x\n",cpu.PC + 1);
			dprintf("SP after: 0x%04x\n",cpu.SP);

			break;

		case 0xcb:
			// PREFIX CB
			// the zero flag is dependent
			// zero = depends , set 1 if result is 0
			// N = 0
			// H = 0
			// C = old

			unsigned int nxtbyt = memory[++cpu.PC];

			switch(nxtbyt){
				case 0x11:
					// RL C
					// lenght is 2 bytes
					// Shift the value in C by 1
					// and put carry flag value in
					// the LSB and copy the shifted
					// out bit to the carry flag

					dprintf("RL C\n");

					dprintf("C Flag before is: 0b%b\n",getC());
					dprintf("Z Flag before is: 0b%b\n",getz());
					dprintf("Register C before is: 0x%2x\n",cpu.C);
					dprintf("Register C before is: 0b%b\n",cpu.C);

					lsb = getC();
					setc(cpu.C >> 7);

					cpu.C <<= 1;
					cpu.C = lsb | cpu.C ;

					setz(cpu.C == 0);

					dprintf("C Flag after is: 0b%b\n",getC());
					dprintf("Z Flag after is: 0b%b\n",getz());
					dprintf("Register C after is: 0x%2x\n",cpu.C);
					dprintf("Register C after is: 0b%b\n",cpu.C);

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

			//store the current addr to the stack
			lsb = cpu.PC & 0x00ff;
			msb = (cpu.PC & 0xff00) >> 8;

			dprintf("Storing 0x%04x first\n",msb);
			push(msb);
			dprintf("Storing 0x%04x next\n",lsb);
			push(lsb);

			cpu.PC = u16 - 1; // +1 will be done at the end

			dprintf("CALL 0x%04x\n",u16);

			dprintf("Jumping to 0x%04x\n",u16);

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

			dprintf("LD (FF00 + u8),A\n");

			u8 = memory[++cpu.PC];
			dprintf("u8: 0x%02x\n",u8);

			addr = 0xff00 + u8;
			dprintf("LD (0xff00 + 0x%02x),A\n",u8);
			dprintf("before : 0x%02x is at 0x%04x\n",memory[addr],addr);

			memory[addr] = cpu.A;
			dprintf("after : 0x%02x is at 0x%04x\n",memory[addr],addr);

			break;

		case 0xe2:
			// LOAD (FF00 + C), A
			// lenght is 1 byte
			// Put A into addr of val at C + 0xff00

			dprintf("LD (0xff00 + C),A\n");
			dprintf("Putting 0x%02x at 0x%04x\n",cpu.A,cpu.C + 0xff00);
			memory[cpu.C + 0xff00] = cpu.A;

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
			// store the value of A at memory address u16

			lsb = memory[++cpu.PC];
			dprintf("LSB: 0x%04x\n",lsb);
			dprintf("LSB: 0b%b\n",lsb);

			msb = memory[++cpu.PC];
			dprintf("MSB: 0x%04x\n",msb);
			dprintf("MSB: 0b%b\n",msb);

			u16 = (msb << 8) | lsb;
			dprintf("u16: 0x%04x\n",u16);

			dprintf("LD 0x%04x, A\n",u16);

			dprintf("Storing 0x%02x at 0x%04x\n",cpu.A,u16);

			dprintf("Value at 0x%04x before: 0x%02x\n",u16,memory[u16]);

			memory[u16] = cpu.A;

			dprintf("Value at 0x%04x after: 0x%02x\n",u16,memory[u16]);

			break;

		case 0xf0:
			// LOAD A , (0xFF00 + u8)
			// lenght is 2 bytes
			// put the values from the memory addr (0xff00 + u8) into A

			u8 = memory[++cpu.PC];
			dprintf("u8: 0x%02x\n",u8);

			dprintf("LD A, (0xff00 + 0x%02x)\n",u8);

			u16 = 0xff00 + u8;

			dprintf("Memory 0x%04x has 0x%02x\n",u16,memory[u16]);
			dprintf("Value of Register A before: 0x%02x\n",cpu.A);

			cpu.A = memory[u16];

			dprintf("Value of Register A before: 0x%02x\n",cpu.A);

			break;

		case 0xf5:
			// PUSH AF
			// lenght is 1 byte
			// PUSH's the value which is in AF
			// and decrements the SP twice

			printf("PUSH AF\n");

			break;

		case 0xfe:
			// COMPARE A, u8
			// lenght is 2 bytes
			// Basically sets flag after A-u8 and throws away the result
			// So if A == u8 then A - u8 is 0
			// hence ,
			// Z = 1
			//

			u8 = memory[++cpu.PC];
			dprintf("u8: 0x%02x\n",u8);

			dprintf("CP A, 0x%02x\n",u8);

			if(cpu.A - u8 == 0){
				dprintf("Setting Zero flag to 1\n");
				setz(1);
			}else{
				dprintf("Setting Zero flag to 0\n");
				setz(0);
			}

			//sleep(1);

			break;

		default:
			printf("\n");
			break;

	}

	cpu.PC++;
	printf("\nRegister PC after: 0x%04x\n",cpu.PC);
	logmsg("execute",false);
}

#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<sys/types.h>

#include"rom_disass.h"

#define dprintf(...)            \
    do {                            \
        if (debug_flag)             \
            printf(__VA_ARGS__);    \
    } while (0)


uint8_t memory[0xffff];
bool debug_flag = false;

off_t getsize(const char *filename){
	// https://en.wikipedia.org/wiki/Stat_(system_call)

	struct stat st;

	if(stat(filename, &st) == 0)
		return st.st_size;

	    return -1;
}

void loader(uint8_t* mem,unsigned char data,unsigned int offset){
	*(mem + offset) = data;
}

void decode(uint8_t* mem,unsigned int file_size){
	unsigned short msb;
	unsigned short lsb;
	unsigned short u16;
	unsigned short u8;
	uint8_t addr;


	printf(ANSI_COLOR_MAGENTA);
	printf("Disassembly:\n");
	printf(ANSI_COLOR_RESET);

	for(short i = 0; i < file_size;i++){
		if(i >= 0x00a8 && i < 0x00e0){
			printf(ANSI_COLOR_BLUE);
			printf(".DB:\t");
			printf(ANSI_COLOR_RESET);
			printf(ANSI_COLOR_GREEN);
			printf("0x%02x\n",*(mem + i));
			printf(ANSI_COLOR_RESET);

			continue;
		}

		unsigned char opcode = *(mem + i);

		printf(ANSI_COLOR_RED);
		printf("0x%04x\t",i);
		printf(ANSI_COLOR_RESET);

		printf(ANSI_COLOR_GREEN);
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

				u8 = *(mem + ++i);
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

				u8 = *(mem + ++i);
				dprintf("u8: 0x%02x\n",u8);

				printf("LD C, 0x%02x\n",u8);
				break;

			case 0x11:
				// LOAD DE, u16
				// lenght is 3 bytes

				lsb = *(mem + ++i);
				dprintf("LSB: 0x%04x\n",lsb);
				dprintf("LSB: 0b%b\n",lsb);

				msb = *(mem + ++i);
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

				u8 = *(mem + ++i);
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

				addr = *(mem + ++i);
				dprintf("Add by: 0x%2x\n",addr);
				dprintf("Add by: %d\n",addr);

				addr += i+1; // address is calculated after the instruction hence
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

				u8 = *(mem + ++i);
				dprintf("u8: 0x%02x\n",u8);

				printf("LD E, 0x%02x\n",u8);
				break;

			case 0x20:
				// JUMP if NotZero to addr
				// lenght is 2 bytes

				addr = *(mem + ++i);
				dprintf("Add by: 0x%2x\n",addr);
				dprintf("Add by: %d\n",addr);

				addr += i+1; // address is calculated after the instruction hence
					     // the +1
				dprintf("Address is: 0x%04x\n",addr);

				printf("JR NZ, (0x%04x)\n",addr);

				break;

			case 0x21:
				// LOAD HL,u16
				// 16-bit load instruction
				// length is 3 bytes

				lsb = *(mem + ++i);
				dprintf("LSB: 0x%04x\n",lsb);
				dprintf("LSB: 0b%b\n",lsb);

				msb = *(mem + ++i);
				dprintf("MSB: 0x%04x\n",msb);
				dprintf("MSB: 0b%b\n",msb);

				u16 = (msb << 8) | lsb;
				dprintf("u16: 0x%04x\n",u16);

				printf("LD HL, 0x%04x\n",u16);

				break;

			case 0x22:
				// LOAD (HL+),A
				// lenght is 1 byte
				// put data of A at the memory location of HL and
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

				addr = *(mem + ++i);
				dprintf("Add by: 0x%2x\n",addr);
				dprintf("Add by: %d\n",addr);

				addr += i+1; // address is calculated after the instruction hence
					     // the +1
				dprintf("Address is: 0x%04x\n",addr);

				printf("JR Z, (0x%04x)\n",addr);

				break;

			case 0x2e:
				// LOAD L , u8
				// lenght is 2 bytes

				u8 = *(mem + ++i);
				dprintf("u8: 0x%02x\n",u8);

				printf("LD L, 0x%02x\n",u8);
				break;

			case 0x30:
				// JR NC, u8
				// JUMP if NotC to (current addr + n)
				// lenght is 2 bytes

				addr = *(mem + ++i);
				dprintf("Add by: 0x%2x\n",addr);
				dprintf("Add by: %d\n",addr);

				addr += i+1; // address is calculated after the instruction hence
					     // the +1
				dprintf("Address is: 0x%04x\n",addr);

				printf("JR NC, (0x%04x)\n",addr);

				break;


			case 0x31:
				// LOAD SP,u16
				// 16-bit load instruction
				// length is 3 bytes

				lsb = *(mem + ++i);
				dprintf("LSB: 0x%04x\n",lsb);
				dprintf("LSB: 0b%b\n",lsb);

				msb = *(mem + ++i);
				dprintf("MSB: 0x%04x\n",msb);
				dprintf("MSB: 0b%b\n",msb);

				u16 = (msb << 8) | lsb;
				dprintf("u16: 0x%04x\n",u16);

				printf("LD SP, 0x%04x\n",u16);

				break;

			case 0x32:
				// LOAD (HL-),A
				// 16-bit load instruction
				// length is 1 bytes
				// Put A into memory address HL and then decrement HL

				printf("LD (HL-),A\n");

				break;

			case 0x38:
				// JR C, u8
				// JUMP if C to (current addr + n)
				// lenght is 2 bytes

				addr = *(mem + ++i);
				dprintf("Add by: 0x%2x\n",addr);
				dprintf("Add by: %d\n",addr);

				addr += i+1; // address is calculated after the instruction hence
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

				u8 = *(mem + ++i);
				dprintf("u8: 0x%02x\n",u8);

				printf("LD A, 0x%02x\n",u8);
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

				printf("XOR A\n");

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

				unsigned int nxtbyt = *(mem + ++i);

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

						printf("BIT 7,H\n");
						break;

					default:
						printf("NULL RN\n");
						break;
				}

				break;
			case 0xcd:
				// CALL u16
				// lenght is 3 bytes

				lsb = *(mem + ++i);
				dprintf("LSB: 0x%04x\n",lsb);
				dprintf("LSB: 0b%b\n",lsb);

				msb = *(mem + ++i);
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

				u8 = *(mem + ++i);
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

				lsb = *(mem + ++i);
				dprintf("LSB: 0x%04x\n",lsb);
				dprintf("LSB: 0b%b\n",lsb);

				msb = *(mem + ++i);
				dprintf("MSB: 0x%04x\n",msb);
				dprintf("MSB: 0b%b\n",msb);

				u16 = (msb << 8) | lsb;
				dprintf("u16: 0x%04x\n",u16);

				printf("LD 0x%04x, A\n",u16);

				break;

			case 0xf0:
				// LOAD A , (0xFF00 + u8)
				// lenght is 2 bytes
				// put the mem addr (0xff00 + u8) into A

				u8 = *(mem + ++i);
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

				u8 = *(mem + ++i);
				dprintf("u8: 0x%02x\n",u8);

				printf("CP 0x%02x\n",u8);
				break;

			default:
				printf("\n");
				break;

		}

	}
}

int read(){
	unsigned char bytecode;
	const char *filename = "dmg_boot.bin";

	unsigned int byt_cnt = 0;
	unsigned int size = getsize(filename);
	FILE* rom_file = fopen(filename,"rb");

	//printf("Size: %d\n",getsize(filename));

	while(byt_cnt != size){
		bytecode = fgetc(rom_file);
		loader(memory,bytecode,byt_cnt++);

		printf(ANSI_COLOR_YELLOW);
		printf("%02x ",bytecode);
		printf(ANSI_COLOR_RESET);

		if(byt_cnt % 32 == 0)
			printf("\n");
	}

	printf("\n");

	fclose(rom_file);
	return size;
}

int main(){
	int size = read();
	decode(memory,size);

	printf(ANSI_COLOR_MAGENTA);
	printf("\n== END OF DISASSEMBLY ==\n");
	printf(ANSI_COLOR_RESET);

}

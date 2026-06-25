#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<unistd.h>

#include "cpu.h"
#include "cpu_ld.h"
#include "cpu_jump.h"
#include "cpu_alu.h"
#include "cpu_incdec.h"
#include "cpu_rotate.h"
#include "cpu_stack.h"
#include "cpu_shift.h"
#include "cpu_misc.h"
#include "registers.h"
#include "flags.h"

#include "memory.h"
#include "debug.h"


/* CPU is little endian. The property is of how bytes are stored in
 * the memory and not of the "CPU" itself. CPU is the dumbest layer
 * but the fastest , the endianness comes on top of that layer.
 * i.e. someone else will interpret the endianness for it , it will
 * just work with the bytes. Another thing is that CPU hence works
 * on multiples of 4 so that it's easy to maintain endianness.
 * 0x1234 gets stored as 34 12 in little endian. 0x123456 gets
 * converted to 0x00123456 and now is stored as 56 34 12 00.*/

/*
	├── cpu.c              // fetch-decode-execute loop, interrupt checks
	├── cpu_ld.c           // LD instructions
	├── cpu_alu.c          // ADD, ADC, SUB, SBC, AND, OR, XOR, CP
	├── cpu_incdec.c       // INC, DEC
	├── cpu_rotate.c       // RLCA, RLA, RRCA, RRA, RLC, RL, RRC, RR
	├── cpu_shift.c        // SLA, SRA, SRL, SWAP
	├── cpu_bit.c          // BIT, SET, RES
	├── cpu_jump.c         // JP, JR, CALL, RET, RST
	├── cpu_stack.c        // PUSH, POP
	├── cpu_misc.c         // NOP, HALT, STOP, DI, EI, DAA, CPL, CCF, SCF
	└── cpu_cb.c       	// CB-prefixed opcode
*/

struct registers cpu;

unsigned short msb;
unsigned short lsb;
unsigned short u16;
uint8_t u8;
int8_t  s8;
unsigned short seventh_bit;
uint8_t addr;
int8_t signed_offset;
unsigned short buffer;
uint16_t result;

uint16_t AF;
uint16_t BC;
uint16_t DE;
uint16_t HL;

long long instr_cnt = 1;

unsigned short get_u16(){
	lsb = memory_read(++cpu.PC);
	dprintf("LSB: 0x%04x\n",lsb);
	dprintf("LSB: 0b%b\n",lsb);

	msb = memory_read(++cpu.PC);
	dprintf("MSB: 0x%04x\n",msb);
	dprintf("MSB: 0b%b\n",msb);

	u16 = (msb << 8) | lsb;
	dprintf("u16: 0x%04x\n",u16);

	return u16;
}

void execute(){

	logmsg("execute",true);


	//if(cpu.PC >= 0x00a8 && cpu.PC < 0x00e0){
		//dprintf(ANSI_COLOR_BLUE);
		//dprintf(".DB:\t");
		//dprintf(ANSI_COLOR_RESET);
		//dprintf(ANSI_COLOR_GREEN);
		//dprintf("0x%02x\n",memory[cpu.PC]);
		//dprintf(ANSI_COLOR_RESET);
	//}

	unsigned char opcode = memory_read(cpu.PC);

	//printf(ANSI_COLOR_RED);
	//dprintf("0x%04x\t",i);
	//printf(ANSI_COLOR_RESET);

	//printf(ANSI_COLOR_GREEN);

	dprintf("\nRegister PC before: 0x%04x\n\n",cpu.PC);
	dprintf("opcode: 0x%02x\n",opcode);

	switch(opcode){
		case 0x00:
			// NOP
			// lenght is 1 byte
			// Do nothing

			dprintf("NOP\n");
			break;

		case 0x01:
			// LD BC, u16
			// lenght is 3 bytes
			// store u16 in BC

			opcd_ld_bc_u16();
			break;

		case 0x02:
			// LD (BC),A

			opcd_ld_bc_a();
			break;

		case 0x03:
			// INC BC
			// lenght is 1 byte

			opcd_inc_bc();
			break;

		case 0x04:
			// INC B
			// lenght is 1 byte

			opcd_inc_b();
			break;

		case 0x05:
			// DEC B
			// lenght is 1 byte

			opcd_dec_b();
			break;

		case 0x06:
			// LOAD B,u8
			// lenght is 2 bytes
			// Put u8 into B

			opcd_ld_b_u8();
			break;

		case 0x07:
			// RLCA

			opcd_rlca();
			break;

		case 0x08:
			// LD u16 , SP
			// Put the SP at the addr u16

			opcd_ld_u16_sp();
			break;

		case 0x09:
			// ADD HL,BC
			// add BC to HL and store it again in HL

			opcd_add_hl_bc();
			break;

		case 0x0b:
			// DEC BC

			opcd_dec_bc();
			break;

		case 0x0c:
			// INCREASE C
			// lenght is 1 byte
			// increase val of C by 1

			opcd_inc_c();
			break;

		case 0x0d:
			// DECREASE C
			// lenght is 1 byte

			opcd_dec_c();
			break;

		case 0x0e:
			// LOAD C , u8
			// lenght is 2 bytes
			// Put the values of u8 into C

			opcd_ld_c_u8();
			break;

		case 0x0f:
			// RRCA

			opcd_rrca();
			break;

		case 0x11:
			// LOAD DE, u16
			// lenght is 3 bytes
			// store u16 in DE

			opcd_ld_de_u16();
			break;

		case 0x12:
			// LOAD (DE), A
			// lenght is 1 byte
			// store A in the memory location DE

			opcd_ld_de_a();
			break;

		case 0x13:
			// INC DE
			// lenght is 1 byte

			opcd_inc_de();
			break;

		case 0x14:
			// INC D
			// lenght is 1 byte

			opcd_inc_d();
			break;

		case 0x15:
			// DEC D
			// lenght is 1 byte

			opcd_dec_d();
			break;

		case 0x16:
			// LOAD D , u8
			// lenght is 2 bytes

			opcd_ld_d_u8();
			break;

		case 0x17:
			// RLA
			// lenght is 1 byte
			// Same as RLC but Z flag always 0

			opcd_rla();
			break;

		case 0x18:
			// JR u8
			// JUMP Relative to (current addr + u8)
			// lenght is 2 bytes

			opcd_jr_u8();
			break;

		case 0x19:
			// ADD HL, DE

			opcd_add_hl_de();
			break;

		case 0x1a:
			// LOAD A,(DE)
			// lenght is 1 byte
			// put contents at addr specified by DE into A

			opcd_ld_a_de();
			break;

		case 0x1b:
			// DEC DE

			opcd_dec_de();
			break;

		case 0x1c:
			// INCREASE E
			// lenght is 1 byte

			opcd_inc_e();
			break;

		case 0x1d:
			// DECREASE E
			// lenght is 1 byte

			opcd_dec_e();
			break;

		case 0x1e:
			// LOAD E,u8
			// lenght is 2 bytes

			opcd_ld_e_u8();
			break;

		case 0x1f:
			// RRA
			// Rotate the values of A with the C flag
			// i.e just shift the values to the right
			// and the value of A goes into MSB and
			// LSB into the C flag
			// Just like RR A but Z flag is always 0

			opcd_rra();
			break;

		case 0x20:
			// JUMP if NotZero to addr
			// lenght is 2 bytes
			// if Z flag is 0:
			// jump relative to (current_addr + addr)

			opcd_jr_nz_u8();
			break;

		case 0x21:
			// LOAD HL,u16
			// 16-bit load instruction
			// length is 3 bytes
			// Put u16's msb in H and lsb in L

			opcd_ld_hl_u16();
			break;

		case 0x22:
			// LOAD (HL+),A
			// lenght is 1 byte
			// put data of A at the memory location of HL and
			// increment HL

			opcd_ld_hlplus_a();
			break;

		case 0x23:
			// INC HL
			// lenght is 1 byte
			// Add 1 to HL

			opcd_inc_hl();
			break;

		case 0x24:
			// INC H
			// lenght is 1 byte

			opcd_inc_h();
			break;

		case 0x25:
			// DEC H
			// lenght is 1 byte

			opcd_dec_h();
			break;

		case 0x26:
			// LOAD H,u8
			// lenght is 2 bytes
			// Put u8 into H

			opcd_ld_h_u8();
			break;

		case 0x28:
			// JR Z, u8
			// JUMP relative if Zero flag is 1 to (current addr + n)
			// lenght is 2 bytes

			opcd_jr_z_u8();
			break;

		case 0x29:
			// ADD HL,HL
			// lenght is 1 byte
			// Add HL to HL and store in HL

			opcd_add_hl_hl();
			break;

		case 0x2a:
			// LOAD A,(HL+)
			// lenght is 1 byte
			// put data at HL into  A and increment HL

			opcd_ld_a_hlplus();
			break;

		case 0x2b:
			// DEC HL

			opcd_dec_hl();
			break;

		case 0x2c:
			// INC L
			// lenght is 1 byte

			opcd_inc_l();
			break;

		case 0x2d:
			// DEC L
			// lenght is 1 byte

			opcd_dec_l();
			break;

		case 0x2e:
			// LOAD L , u8
			// lenght is 2 bytes
			// Put the value of u8 in the L register

			opcd_ld_l_u8();
			break;

		case 0x2f:
			// CPL
			// Take the one's complement
			// (i.e., flip all bits) of the
			// contents of register A.

			opcd_cpl();
			break;

		case 0x30:
			// JR NC, u8
			// JUMP relative if NotC to (current addr + n)
			// lenght is 2 bytes
			opcd_jr_nc_u8();
			break;

		case 0x31:
			// LOAD SP,u16
			// 16-bit load instruction
			// length is 3 bytes
			// put the u16 in the SP register

			opcd_ld_sp_u16();
			break;

		case 0x32:
			// LOAD (HL-),A
			// 16-bit load instruction
			// length is 1 bytes
			// Put A into memory address HL and then decrement HL

			opcd_ld_hlminus_a();
			break;

		case 0x33:
			// INC SP

			opcd_inc_sp();
			break;

		case 0x35:
			// DEC (HL)
			// Decrement the value at HL by 1

			opcd_dec_at_hl();
			break;

		case 0x36:
			// LD (HL), u8
			// Store u8 at the address of HL

			opcd_ld_hl_u8();
			break;

		case 0x37:
			// SCF
			// Set the Carry flag to 1

			opcd_scf();
			break;

		case 0x38:
			// JR C, u8
			// JUMP relative if C , to (current addr + n)
			// lenght is 2 bytes

			opcd_jr_c_u8();
			break;

		case 0x39:
			// ADD HL, SP

			opcd_add_hl_sp();
			break;

		case 0x3b:
			// DEC SP

			opcd_dec_sp();
			break;

		case 0x3c:
			// INC A
			// lenght is 1 byte

			opcd_inc_a();
			break;

		case 0x3d:
			// DEC A
			// lenght is 1 byte

			opcd_dec_a();
			break;

		case 0x3e:
			// LOAD A , u8
			// lenght is 2 bytes

			opcd_ld_a_u8();
			break;

		case 0x3f:
			// CCF

			opcd_ccf();
			break;

		case 0x40:
			// LOAD B, B
			// lenght is 1 bytes
			// Put B into B

			opcd_ld_b_b();
			break;

		case 0x41:
			// LOAD B,C
			// lenght is 1 byte

			opcd_ld_b_c();
			break;

		case 0x42:
			// LOAD B,D
			// lenght is 1 byte

			opcd_ld_b_d();
			break;

		case 0x43:
			// LOAD B,E
			// lenght is 1 byte

			opcd_ld_b_e();
			break;

		case 0x44:
			// LOAD B,H
			// lenght is 1 byte

			opcd_ld_b_h();
			break;

		case 0x45:
			// LOAD B,l
			// lenght is 1 byte

			opcd_ld_b_l();
			break;

		case 0x46:
			// LOAD B,(HL)
			// lenght is 1 byte
			// put data at HL into  B

			opcd_ld_b_hl();
			break;

		case 0x47:
			// LOAD B,A
			// lenght is 1 byte

			opcd_ld_b_a();
			break;

		case 0x48:
			// LOAD C,B
			// lenght is 1 byte
			// Put value of B into C

			opcd_ld_c_b();
			break;

		case 0x49:
			// LOAD C,C
			// lenght is 1 byte
			// Put value of C into C

			opcd_ld_c_c();
			break;

		case 0x4a:
			// LOAD C,D
			// lenght is 1 byte
			// Put value of D into C

			opcd_ld_c_d();
			break;

		case 0x4b:
			// LOAD C,E
			// lenght is 1 byte
			// Put value of E into C

			opcd_ld_c_e();
			break;

		case 0x4c:
			// LOAD C,H
			// lenght is 1 byte
			// Put value of H into C

			opcd_ld_c_h();
			break;

		case 0x4d:
			// LOAD C,L
			// lenght is 1 byte
			// Put value of L into C

			opcd_ld_c_l();
			break;

		case 0x4e:
			// LOAD C,(HL)
			// lenght is 1 byte
			// put data at HL into  C

			opcd_ld_c_hl();
			break;

		case 0x4f:
			// LOAD C,A
			// lenght is 1 byte
			// Put value of A into C

			opcd_ld_c_a();
			break;

		case 0x50:
			// LOAD D,B
			// lenght is 1 byte

			opcd_ld_d_b();
			break;

		case 0x51:
			// LOAD D,C
			// lenght is 1 byte

			opcd_ld_d_c();
			break;

		case 0x52:
			// LOAD D,D
			// lenght is 1 byte

			opcd_ld_d_d();
			break;

		case 0x53:
			// LOAD D,E
			// lenght is 1 byte

			opcd_ld_d_e();
			break;

		case 0x54:
			// LOAD D,H
			// lenght is 1 byte

			opcd_ld_d_h();
			break;

		case 0x55:
			// LOAD D,L
			// lenght is 1 byte

			opcd_ld_d_l();
			break;

		case 0x56:
			// LOAD D,(HL)
			// lenght is 1 byte
			// put data at HL into  D

			opcd_ld_d_hl();
			break;

		case 0x57:
			// LOAD D,A
			// lenght is 1 byte

			opcd_ld_d_a();
			break;

		case 0x58:
			// LOAD E, B

			opcd_ld_e_b();
			break;

		case 0x59:
			// LOAD E, C

			opcd_ld_e_c();
			break;

		case 0x5a:
			// LOAD E, D

			opcd_ld_e_d();
			break;

		case 0x5b:
			// LOAD E, E

			opcd_ld_e_e();
			break;

		case 0x5c:
			// LOAD E, H

			opcd_ld_e_h();
			break;


		case 0x5d:
			//LD E, L

			opcd_ld_e_l();
			break;

		case 0x5e:
			//LD E,(HL)

			opcd_ld_e_hl();
			break;

		case 0x5f:
			// LOAD E,A
			// lenght is 1 byte

			opcd_ld_e_a();
			break;

		case 0x60:
			// LOAD H, B

			opcd_ld_h_b();
			break;

		case 0x61:
			// LOAD H, C

			opcd_ld_h_c();
			break;

		case 0x62:
			// LOAD H, D

			opcd_ld_h_d();
			break;

		case 0x63:
			// LOAD H, E

			opcd_ld_h_e();
			break;

		case 0x64:
			// LOAD H, H

			opcd_ld_h_h();
			break;

		case 0x65:
			// LOAD H, L

			opcd_ld_h_l();
			break;

		case 0x66:
			// LOAD H, (HL)

			opcd_ld_h_hl();
			break;

		case 0x67:
			// LOAD H,A
			// lenght is 1 byte
			// Put the contents of A into the H register

			opcd_ld_h_a();
			break;

		case 0x68:
			// LD L, B

			opcd_ld_l_b();
			break;

		case 0x69:
			// LD L, C

			opcd_ld_l_c();
			break;

		case 0x6a:
			// LD L, D

			opcd_ld_l_d();
			break;

		case 0x6b:
			// LD L, E

			opcd_ld_l_e();
			break;

		case 0x6c:
			// LD L, H

			opcd_ld_l_h();
			break;

		case 0x6d:
			// LD L, L

			opcd_ld_l_l();
			break;


		case 0x6e:
			// LOAD L , (HL)
			// Put values at mem address HL into L

			opcd_ld_l_hl();
			break;

		case 0x6f:
			// LOAD L,A
			// lenght is 1 byte
			// Put the contents of A into the L register

			opcd_ld_l_a();
			break;

		case 0x70:
			// LOAD (HL),B
			// lenght is 1 byte
			// put data of B into memory of HL

			opcd_ld_hl_b();
			break;

		case 0x71:
			// LOAD (HL),C
			// lenght is 1 byte
			// put data of C into memory of HL

			opcd_ld_hl_c();
			break;

		case 0x72:
			// LOAD (HL),D
			// lenght is 1 byte
			// put data of D into memory of HL

			opcd_ld_hl_d();
			break;

		case 0x73:
			// LOAD (HL),E
			// lenght is 1 byte
			// put data of E into the memory of HL

			opcd_ld_hl_e();
			break;

		case 0x74:
			// LD (HL), H

			opcd_ld_hl_h();
			break;

		case 0x75:
			// LD (HL), L

			opcd_ld_hl_l();
			break;

		case 0x77:
			// LOAD (HL),A
			// lenght is 1 byte
			// put data of A into memory of HL

			opcd_ld_hl_a();
			break;

		case 0x78:
			// LOAD A,B
			// lenght is 1 byte
			// Put contents of B into A

			opcd_ld_a_b();
			break;

		case 0x79:
			// LOAD A,C
			// lenght is 1 byte
			// Put contents of C into A
			opcd_ld_a_c();
			break;

		case 0x7a:
			// LOAD A,D
			// lenght is 1 byte
			// Put contents of D into A

			opcd_ld_a_d();
			break;

		case 0x7b:
			// LOAD A,E
			// lenght is 1 byte
			// Put contents of E into A

			opcd_ld_a_e();
			break;

		case 0x7c:
			// LOAD A,H
			// lenght is 1 byte
			// Put contents of H into A

			opcd_ld_a_h();
			break;

		case 0x7d:
			// LOAD A ,L
			// lenght is 1 byte
			// Put contents of L into A

			opcd_ld_a_l();
			break;

		case 0x7e:
			// LOAD A ,(HL)
			// lenght is 1 byte
			// Put contents at (HL) into A

			opcd_ld_a_hl();
			break;

		case 0x7f:
			// LD A,A

			opcd_ld_a_a();
			break;

		case 0x80:
			// ADD A,B
			// lenght is 1 byte
			// Add B to A and store in A

			opcd_add_a_b();
			break;

		case 0x81:
			// ADD A,C
			// lenght is 1 byte
			// Add C to A and store in A

			opcd_add_a_c();
			break;

		case 0x82:
			// ADD A, D

			opcd_add_a_d();
			break;

		case 0x83:
			// ADD A, E

			opcd_add_a_e();
			break;

		case 0x84:
			// ADD A, H

			opcd_add_a_h();
			break;

		case 0x85:
			// ADD A, L

			opcd_add_a_l();
			break;


		case 0x86:
			// ADD A,(HL)
			// lenght is 1 byte
			// add value at the addr HL to A
			// and store in A

			opcd_add_a_hl();
			break;

		case 0x87:
			// ADD A,A
			// lenght is 1 byte
			// Add A to A and store in A

			opcd_add_a_a();
			break;

		case 0x88:
			// ADC A,B

			opcd_adc_a_b();
			break;

		case 0x89:
			// ADC A,C

			opcd_adc_a_c();
			break;

		case 0x8a:
			// ADC A,D

			opcd_adc_a_d();
			break;

		case 0x8b:
			// ADC A,E

			opcd_adc_a_e();
			break;

		case 0x8c:
			// ADC A,H

			opcd_adc_a_h();
			break;

		case 0x8d:
			// ADC A,L

			opcd_adc_a_l();
			break;

		case 0x8e:
			// ADC A,(HL)

			opcd_adc_a_hl();
			break;

		case 0x8f:
			// ADC A. A

			opcd_adc_a_a();
			break;

		case 0x90:
			// SUB A , B
			// lenght is 1 byte
			// subtract B from A

			opcd_sub_a_b();
			break;

		case 0x91:
			// SUB A , C
			// lenght is 1 byte
			// subtract C from A

			opcd_sub_a_c();
			break;

		case 0x92:
			// SUB D

			opcd_sub_a_d();
			break;

		case 0x93:
			// SUB E

			opcd_sub_a_e();
			break;

		case 0x94:
			// SUB H

			opcd_sub_a_h();
			break;

		case 0x95:
			// SUB L

			opcd_sub_a_l();
			break;

		case 0x96:
			// SUB (HL)

			opcd_sub_a_hl();
			break;

		case 0x97:
			// SUB A

			opcd_sub_a_a();
			break;

		case 0x98:
			// SBC A, B

			opcd_sbc_a_b();
			break;

		case 0x99:
			// SBC A, C

			opcd_sbc_a_c();
			break;

		case 0x9a:
			// SBC A, D

			opcd_sbc_a_d();
			break;

		case 0x9b:
			// SBC A, E

			opcd_sbc_a_e();
			break;

		case 0x9c:
			// SBC A, H

			opcd_sbc_a_h();
			break;

		case 0x9d:
			// SBC A, L

			opcd_sbc_a_l();
			break;

		case 0x9e:
			// SBC A , (HL)

			opcd_sbc_a_hl();
			break;

		case 0x9f:
			// SBC A, A

			opcd_sbc_a_a();
			break;

		case 0xa0:
			// AND B

			opcd_and_b();
			break;

		case 0xa1:
			// AND C

			opcd_and_c();
			break;

		case 0xa2:
			// AND D

			opcd_and_d();
			break;

		case 0xa3:
			// AND E

			opcd_and_e();
			break;

		case 0xa4:
			// AND H

			opcd_and_h();
			break;

		case 0xa5:
			// AND L

			opcd_and_l();
			break;

		case 0xa6:
			// AND (HL)

			opcd_and_hl();
			break;

		case 0xa7:
			// AND A

			opcd_and_a();
			break;

		case 0xa8:
			// XOR B

			opcd_xor_b();
			break;

		case 0xa9:
			// XOR C
			// ALU operation
			// lenght is 1 byte
			// XOR's the value which is in A with A and stores in A

			opcd_xor_c();
			break;

		case 0xaa:
			// XOR D

			opcd_xor_d();
			break;

		case 0xab:
			// XOR E

			opcd_xor_e();
			break;

		case 0xac:
			// XOR H

			opcd_xor_h();
			break;

		case 0xad:
			// XOR L
			// ALU operation
			// lenght is 1 byte
			// XOR's the value which is in L with A and stores in A

			opcd_xor_l();
			break;

		case 0xae:
			// XOR (HL)
			// ALU operation
			// lenght is 1 byte
			// XOR's the value which is in A with value at HL and stores in A

			opcd_xor_memhl();
			break;

		case 0xaf:
			// XOR A
			// ALU operation
			// lenght is 1 byte
			// XOR's the value which is in A with A and stores in A

			opcd_xor_a();
			break;

		case 0xb0:
			// OR B
			// ALU operation
			// lenght is 1 byte
			// OR's the value which is in B with A and stores in A

			opcd_or_b();
			break;

		case 0xb1:
			// OR C
			// ALU operation
			// lenght is 1 byte
			// OR's the value which is in C with A and stores in A

			opcd_or_c();
			break;
		case 0xb2:
			// OR D

			opcd_or_d();
			break;

		case 0xb3:
			// OR E

			opcd_or_e();
			break;

		case 0xb4:
			// OR H

			opcd_or_h();
			break;

		case 0xb5:
			// OR L

			opcd_or_l();
			break;

		case 0xb6:
			// OR (HL)
			// ALU operation
			// lenght is 1 byte
			// OR's the value which is at memory address HL with A and stores in A

			opcd_or_hl();
			break;

		case 0xb7:
			// OR A
			// ALU operation
			// lenght is 1 byte
			// OR's the value which is in A with A and stores in A

			opcd_or_a();
			break;

		case 0xb8:
			// CP B

			opcd_cp_b();
			break;

		case 0xb9:
			// CP C
			// Calculate A - C and set Z flag

			opcd_cp_c();
			break;

		case 0xba:
			// CP D

			opcd_cp_d();
			break;

		case 0xbb:
			// CP E

			opcd_cp_e();
			break;

		case 0xbc:
			// CP H

			opcd_cp_h();
			break;

		case 0xbd:
			// CP L

			opcd_cp_l();
			break;

		case 0xbe:
			// COMPARE A , (HL)
			// Same as CP u8 but this time compare with the content
			// at the addr (HL)
			// Basically sets flag after A-memory[HL] and throws away the result
			// So if A == memory[HL] then A - memory[HL] is 0
			// hence ,
			// Z = 1

			opcd_cp_a_hl();
			break;

		case 0xbf:
			// CP A

			opcd_cp_a();
			break;

		case 0xc0:
			// RET NZ
			// if Z flag 0 then ret

			opcd_ret_nz();
			break;

		case 0xc1:
			// POP BC
			// lenght is 1 byte

			opcd_pop_bc();
			break;

		case 0xc3:
			// JP u16
			// JUMP to addr u16
			// lenght is 3 bytes

			opcd_jp_u16();
			break;

		case 0xc5:
			// PUSH BC
			// lenght is 1 byte
			// PUSH's the value which is in BC
			// and decrements the SP twice

			opcd_push_bc();
			break;

		case 0xc6:
			// ADD A,u8
			// lenght is 1 byte
			// Add u8 to A and store in A

			opcd_add_a_u8();
			break;

		case 0xc8:
			// RET Z
			// Ret only if Z is 1

			opcd_ret_z();
			break;

		case 0xc9:
			// RET
			// lenght is 1 byte
			// POP the stack and put it into the PC

			opcd_ret();
			break;

		case 0xcb:
			// PREFIX CB
			// the zero flag is dependent
			// zero = depends , set 1 if result is 0
			// N = 0
			// H = 0
			// C = old

			unsigned int nxtbyt = memory_read(++cpu.PC);

			switch(nxtbyt){
				case 0x00:
					// RLC B

					opcd_rlc_b();
					break;

				case 0x01:
					// RLC C

					opcd_rlc_c();
					break;

				case 0x02:
					// RLC D

					opcd_rlc_d();
					break;

				case 0x03:
					// RLC E

					opcd_rlc_e();
					break;

				case 0x04:
					// RLC H

					opcd_rlc_h();
					break;

				case 0x05:
					// RLC L

					opcd_rlc_l();
					break;

				case 0x06:
					// RLC (HL)

					opcd_rlc_hl();
					break;

				case 0x7:
					// RLC A

					opcd_rlc_a();
					break;

				case 0x8:
					// RRC B

					opcd_rrc_b();
					break;

				case 0x9:
					// RRC C

					opcd_rrc_c();
					break;

				case 0xa:
					// RRC D

					opcd_rrc_d();
					break;

				case 0xb:
					// RRC E

					opcd_rrc_e();
					break;

				case 0xc:
					// RRC H

					opcd_rrc_h();
					break;

				case 0xd:
					// RRC L

					opcd_rrc_l();
					break;

				case 0xe:
					// RRC (HL)

					opcd_rrc_hl();
					break;

				case 0xf:
					// RRC A

					opcd_rrc_a();
					break;

				case 0x10:
					// RL B

					opcd_rl_b();
					break;

				case 0x11:
					// RL C
					// lenght is 2 bytes
					// Shift the value in C by 1
					// and put carry flag value in
					// the LSB and copy the shifted
					// out bit to the carry flag

					opcd_rl_c();
					break;

				case 0x12:
					// RL D

					opcd_rl_d();
					break;

				case 0x13:
					// RL E

					opcd_rl_e();
					break;

				case 0x14:
					// RL H

					opcd_rl_h();
					break;

				case 0x15:
					// RL L

					opcd_rl_l();
					break;

				case 0x16:
					// RL (HL)

					opcd_rl_hl();
					break;

				case 0x17:
					// RL A

					opcd_rl_a();
					break;

				case 0x18:
					// RR B

					opcd_rr_b();
					break;

				case 0x19:
					// RR C
					// Rotate the values of C with the C flag
					// i.e just shift the values to the right
					// and the value of C goes into MSB and
					// LSB into the C flag


					opcd_rr_c();
					//exit(1);
					break;

				case 0x1a:
					// RR D
					// Rotate the values of D with the C flag
					// i.e just shift the values to the right
					// and the value of D goes into MSB and
					// LSB into the C flag

					opcd_rr_d();
					break;

				case 0x1b:
					// RR E
					// Rotate the values of E with the C flag
					// i.e just shift the values to the right
					// and the value of E goes into MSB and
					// LSB into the C flag

					opcd_rr_e();
					break;

				case 0x1c:
					// RR H

					opcd_rr_h();
					break;

				case 0x1d:
					// RR L

					opcd_rr_l();
					break;

				case 0x1e:
					// RR HL

					opcd_rr_hl();
					break;

				case 0x1f:
					// RR A
					// Rotate the values of A with the C flag
					// i.e just shift the values to the right
					// and the value of A goes into MSB and
					// LSB into the C flag

					opcd_rr_a();
					break;

				case 0x20:
					// SLA B

					opcd_sla_b();
					break;

				case 0x21:
					// SLA C

					opcd_sla_c();
					break;

				case 0x22:
					// SLA D

					opcd_sla_d();
					break;

				case 0x23:
					// SLA E

					opcd_sla_e();
					break;

				case 0x24:
					// SLA H

					opcd_sla_h();
					break;

				case 0x25:
					// SLA L

					opcd_sla_l();
					break;

				case 0x26:
					// SLA (HL)

					opcd_sla_hl();
					break;

				case 0x27:
					// SLA A

					opcd_sla_a();
					break;

				case 0x28:
					// SRA B

					opcd_sra_b();
					break;

				case 0x29:
					// SRA C

					opcd_sra_c();
					break;

				case 0x2a:
					// SRA D

					opcd_sra_d();
					break;

				case 0x2b:
					// SRA E

					opcd_sra_e();
					break;

				case 0x2c:
					// SRA H

					opcd_sra_h();
					break;

				case 0x2d:
					// SRA L

					opcd_sra_l();
					break;

				case 0x2e:
					// SRA (HL)

					opcd_sra_hl();
					break;

				case 0x2f:
					// SRA A

					opcd_sra_a();
					break;

				case 0x30:
					// SWAP B

					opcd_swap_b();
					break;

				case 0x31:
					// SWAP C

					opcd_swap_c();
					break;

				case 0x32:
					// SWAP D

					opcd_swap_d();
					break;

				case 0x33:
					// SWAP E

					opcd_swap_e();
					break;

				case 0x34:
					// SWAP H

					opcd_swap_h();
					break;

				case 0x35:
					// SWAP L

					opcd_swap_l();
					break;

				case 0x36:
					// SWAP (HL)
					// REDO

					opcd_swap_hl();
					break;

				case 0x37:
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

					opcd_swap_a();
					break;

				case 0x38:
					// SRL B
					// lenght is 2 bytes
					// B's value is shifted to the right
					// by 1 bit.
					// The MSB is set to 0.
					// The carry flag is set to LSB
					// N and H are set to 0

					opcd_srl_b();
					break;

				case 0x39:
					// SRL C

					opcd_srl_c();
					break;

				case 0x3a:
					// SRL D

					opcd_srl_d();
					break;

				case 0x3b:
					// SRL E

					opcd_srl_e();
					break;

				case 0x3c:
					// SRL H

					opcd_srl_h();
					break;

				case 0x3d:
					// SRL L

					opcd_srl_l();
					break;

				case 0x3f:
					// SRL A

					opcd_srl_a();
					break;


				case 0x4f:
					// BIT 1,A
					// lenght is 2 bytes

					printf("BIT 1,A\n");
					exit(1);
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


					dprintf("BIT 7,H\n");
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
					printf("[%lld]Opcode to implement: 0xCB%02x\n",instr_cnt,memory_read(cpu.PC));
					exit(1);

					break;
			}

			break;

		case 0xc4:
			// CALL NZ , u16
			// lenght is 3 bytes

			opcd_call_nz_u16();
			break;


		case 0xcd:
			// CALL u16
			// lenght is 3 bytes

			opcd_call_u16();
			//sleep(5);
			break;

		case 0xce:
			// ADC A,u8
			// Add u8 and C flag to A
			// Set Z flags, N = 0, H and C

			opcd_adc_a_u8();
			break;

		case 0xd0:
			// RET NC
			// lenght is 1 byte
			// POP the stack and put it into the PC if C flag is 0

			opcd_ret_nc();
			break;

		case 0xd1:
			// POP DE
			// lenght is 1 byte

			opcd_pop_de();
			break;
		case 0xd4:
			// CALL NC , u16

			opcd_call_nc_u16();
			break;

		case 0xd5:
			// PUSH DE
			// lenght is 1 byte
			// PUSH's the value which is in DE
			// and decrements the SP twice

			opcd_push_de();
			break;

		case 0xd6:
			// SUB u8
			// lenght is 2 byte
			// subtract u8 from A

			opcd_sub_u8();
			break;

		case 0xd8:
			// RET C
			// POP the stack and put
			// it in the PC if C is 1
			opcd_ret_c();
			break;

		case 0xde:
			// SBC A, u8
			// Subtract register A , u8 and carry
			// flag and store in A
			// Z = set
			// N = 1
			// H , C = set

			opcd_sbc_a_u8();
			break;

		case 0xe0:
			// LOAD (FF00 + u8),A
			// lenght is 2 bytes
			// Put A into addr of val u8+ 0xff00

			opcd_ld_ff00_u8_a();

			break;

		case 0xe1:
			// POP HL
			// lenght is 1 byte

			//if(cpu.PC == 0xc16b)
				//exit(1);

			opcd_pop_hl();
			break;

		case 0xe2:
			// LOAD (FF00 + C), A
			// lenght is 1 byte
			// Put A into addr of val at C + 0xff00

			opcd_ld_ff00_c_a();

			break;

		case 0xe5:
			// PUSH HL
			// lenght is 1 byte
			// PUSH's the value which is in HL
			// and decrements the SP twice

			opcd_push_hl();
			break;

		case 0xe6:
			// AND u8
			// lenght is 2 bytes
			// AND u8 with A and store it in A

			opcd_and_u8();
			break;

		case 0xe8:
			// ADD SP, u8
			// add u8 into SP

			opcd_add_sp_u8();
			break;

		case 0xe9:
			// JP HL
			// JUMP to addr in HL
			// lenght is 3 bytes

			opcd_jp_hl();
			break;

		case 0xea:
			// LD (u16), A
			// lenght is 3 bytes
			// store the value of A at memory address u16

			opcd_ld_u16_a();

			break;

		case 0xee:
			// XOR u8
			// lenght is 2 bytes
			// XOR u8 with A and store it in A

			dprintf("XOR u8\n");

			u8 = memory_read(++cpu.PC);

			dprintf("XOR with 		    :0b%08b\n",u8);
			dprintf("Value of register A before : 0b%08b\n",cpu.A);

			cpu.A ^= u8;
			setXORflags(cpu.A);

			dprintf("Value of register A after : 0b%08b\n",cpu.A);

			break;

		case 0xf0:
			// LOAD A , (0xFF00 + u8)
			// lenght is 2 bytes
			// put the values from the memory addr (0xff00 + u8) into A

			opcd_ld_a_ff00_u8();

			break;

		case 0xf1:
			// POP AF
			// lenght is 1 byte

			dprintf("POP AF\n");
			dprintf("SP before: 0x%04x\n",cpu.SP);

			lsb = pop(); // C
			msb = pop();  // B

			u16 = (msb << 8) | lsb;

			setAF(u16);

			dprintf("Value of register AF : 0x%04x\n",getAF());
			dprintf("SP after: 0x%04x\n",cpu.SP);

			break;

		case 0xf2:
			// LOAD A , (C + 0xff00)
			// lenght is 1 bytes
			// put the values from the memory addr
			// specified by register C into A.
			// Add the contents of C with 0xff00 as
			//  contents of the internal RAM, port register
			// or mode register at the address in the range

			opcd_ld_a_c_ff00();
			break;

		case 0xf3:
			// DI
			// 1 byte long
			dprintf("DI (need to implement interrupts)\n");
			break;

		case 0xf5:
			// PUSH AF
			// lenght is 1 byte
			// PUSH's the value which is in AF
			// and decrements the SP twice

			opcd_push_af();
			break;

		case 0xf6:
			// OR u8
			// OR u8 with A and store in A

			opcd_or_u8();
			break;

		case 0xf8:
			// LD HL, SP + u8

			opcd_ld_hl_sp_u8();
			break;

		case 0xf9:
			// LD SP, HL
			// Put HL in SP

			opcd_ld_sp_hl();
			break;

		case 0xfa:
			// LD A, (u16)
			// Lenght is 3 bytes
			// put the contents at memory location u16
			// into register A

			opcd_ld_a_u16();

			break;

		case 0xfe:
			// COMPARE A, u8
			// lenght is 2 bytes
			// Basically sets flag after A-u8 and throws away the result
			// So if A == u8 then A - u8 is 0
			// hence ,
			// Z = 1
			//
			// N = 1 (always)
			// set H and C

			u8 = memory_read(++cpu.PC);
			dprintf("u8: 0x%02x\n",u8);

			dprintf("CP A, 0x%02x\n",u8);

			if(cpu.A - u8 == 0){
				dprintf("Setting Zero flag to 1\n");
				setz(1);
			}else{
				dprintf("Setting Zero flag to 0\n");
				setz(0);
			}

			setn(1);
			seth((cpu.A & 0xF) < (u8 & 0xF));
			setc(cpu.A < u8);

			//sleep(1);

			break;

		default:
			//sleep(2);true
    			printf(
        		"[%lld] UNIMPLEMENTED OPCODE 0x%02x at PC=0x%04x\n",
			instr_cnt,
        		opcode,
        		cpu.PC
    			);
    			exit(1);
			break;

	}

	if(cpu.PC == 0x100)
		gb_doc_log();

	cpu.PC++;
	instr_cnt++;

	if(gb_doc == true)
		gb_doc_log();

	//if(instr_cnt == 730268)
		//exit(1);

	dprintf("\nRegister PC after: 0x%04x\n",cpu.PC);

	logmsg("execute",false);
}

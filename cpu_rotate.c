#include "debug.h"
#include "flags.h"
#include "cpu.h"
#include "memory.h"
#include "registers.h"


void opcd_rla(){
	// RLA
	// lenght is 1 byte
	// Same as RL A but Z flag always 0
	// C is b7
	// and b0 C

	dprintf("RLA\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register A before is: 0x%2x\n",cpu.A);
	dprintf("Register A before is: 0b%b\n",cpu.A);

	lsb = getC();
	setc((cpu.A & GET7BIT) >> 7);

	cpu.A <<= 1;
	cpu.A = lsb | cpu.A ;

	setz(0);
	seth(0);
	setn(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register A after is: 0x%2x\n",cpu.A);
	dprintf("Register A after is: 0b%b\n",cpu.A);

}

void opcd_rlc_b(){
	// RLC B
	// lenght is 1 byte
	// Rotate the register A left with C flag
	// before: C  b7 b6 b5 b4 b3 b2 b1 b0
	// after : b7 b6 b5 b4 b3 b2 b1 b0 b7
	//
	// b7 is both in the LSB and C flag
	//
	// Z = set
	// N = 0
	// H = 0
	// C = set

	dprintf("RLC B\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register B before is: 0x%2x\n",cpu.B);
	dprintf("Register B before is: 0b%8b\n",cpu.B);

	lsb = cpu.B & GET7BIT;
	lsb >>= 7; // b7
	setc(lsb);

	cpu.B <<= 1;
	cpu.B = lsb | cpu.B ;

	setz(cpu.B == 0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register B after is: 0x%2x\n",cpu.B);
	dprintf("Register B after is: 0b%b\n",cpu.B);

}

void opcd_rlc_e(){
	// RLC E
	// lenght is 1 byte
	// Rotate the register A left with C flag
	// before: C  b7 b6 b5 b4 b3 b2 b1 b0
	// after : b7 b6 b5 b4 b3 b2 b1 b0 b7
	//
	// b7 is both in the LSE and C flag
	//
	// Z = set
	// N = 0
	// H = 0
	// C = set

	dprintf("RLC E\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register E before is: 0x%2x\n",cpu.E);
	dprintf("Register E before is: 0b%8b\n",cpu.E);

	lsb = cpu.E & GET7BIT;
	lsb >>= 7; // b7
	setc(lsb);

	cpu.E <<= 1;
	cpu.E = lsb | cpu.E ;

	setz(cpu.E == 0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register E after is: 0x%2x\n",cpu.E);
	dprintf("Register E after is: 0b%b\n",cpu.E);

}

void opcd_rlc_a(){
	// RLC A
	// lenght is 1 byte
	// Rotate the register A left with C flag
	// before: C  b7 b6 b5 b4 b3 b2 b1 b0
	// after : b7 b6 b5 b4 b3 b2 b1 b0 b7
	//
	// b7 is both in the LSA and C flag
	//
	// Z = set
	// N = 0
	// H = 0
	// C = set

	dprintf("RLC A\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register A before is: 0x%2x\n",cpu.A);
	dprintf("Register A before is: 0b%8b\n",cpu.A);

	lsb = cpu.A & GET7BIT;
	lsb >>= 7; // b7
	setc(lsb);

	cpu.A <<= 1;
	cpu.A = lsb | cpu.A ;

	setz(cpu.A == 0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register A after is: 0x%2x\n",cpu.A);
	dprintf("Register A after is: 0b%b\n",cpu.A);

}
void opcd_rlc_d(){
	// RLC D
	// lenght is 1 byte
	// Rotate the register A left with C flag
	// before: C  b7 b6 b5 b4 b3 b2 b1 b0
	// after : b7 b6 b5 b4 b3 b2 b1 b0 b7
	//
	// b7 is both in the LSD and C flag
	//
	// Z = set
	// N = 0
	// H = 0
	// C = set

	dprintf("RLC D\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register D before is: 0x%2x\n",cpu.D);
	dprintf("Register D before is: 0b%8b\n",cpu.D);

	lsb = cpu.D & GET7BIT;
	lsb >>= 7; // b7
	setc(lsb);

	cpu.D <<= 1;
	cpu.D = lsb | cpu.D ;

	setz(cpu.D == 0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register D after is: 0x%2x\n",cpu.D);
	dprintf("Register D after is: 0b%b\n",cpu.D);

}

void opcd_rlc_hl(){
	// RLC (HL)
	// lenght is 1 byte
	// Rotate the val at mem HL left with C flag
	// before: C  b7 b6 b5 b4 b3 b2 b1 b0
	// after : b7 b6 b5 b4 b3 b2 b1 b0 b7
	//
	// b7 is both in the LSD and C flag
	//
	// Z = set
	// N = 0
	// H = 0
	// C = set

	dprintf("RLC D\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register D before is: 0x%2x\n",memory_read(getHL()));
	dprintf("Register D before is: 0b%8b\n",memory_read(getHL()));

	lsb = memory_read(getHL()) & GET7BIT;
	lsb >>= 7; // b7
	setc(lsb);

	u8 = memory_read(getHL());

	u8 <<= 1;
	u8 = lsb | u8;

	memory_write(getHL(),u8);

	setz(memory_read(getHL()) == 0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register D after is: 0x%2x\n",memory_read(getHL()));
	dprintf("Register D after is: 0b%8b\n",memory_read(getHL()));

}

void opcd_rlc_l(){
	// RLC L
	// lenght is 1 byte
	// Rotate the register A left with C flag
	// before: C  b7 b6 b5 b4 b3 b2 b1 b0
	// after : b7 b6 b5 b4 b3 b2 b1 b0 b7
	//
	// b7 is both in the LSL and C flag
	//
	// Z = set
	// N = 0
	// H = 0
	// C = set

	dprintf("RLC L\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register L before is: 0x%2x\n",cpu.L);
	dprintf("Register L before is: 0b%8b\n",cpu.L);

	lsb = cpu.L & GET7BIT;
	lsb >>= 7; // b7
	setc(lsb);

	cpu.L <<= 1;
	cpu.L = lsb | cpu.L ;

	setz(cpu.L == 0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register L after is: 0x%2x\n",cpu.L);
	dprintf("Register L after is: 0b%b\n",cpu.L);

}
void opcd_rlc_h(){
	// RLC H
	// lenght is 1 byte
	// Rotate the register A left with C flag
	// before: C  b7 b6 b5 b4 b3 b2 b1 b0
	// after : b7 b6 b5 b4 b3 b2 b1 b0 b7
	//
	// b7 is both in the LSH and C flag
	//
	// Z = set
	// N = 0
	// H = 0
	// C = set

	dprintf("RLC H\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register H before is: 0x%2x\n",cpu.H);
	dprintf("Register H before is: 0b%8b\n",cpu.H);

	lsb = cpu.H & GET7BIT;
	lsb >>= 7; // b7
	setc(lsb);

	cpu.H <<= 1;
	cpu.H = lsb | cpu.H ;

	setz(cpu.H == 0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register H after is: 0x%2x\n",cpu.H);
	dprintf("Register H after is: 0b%b\n",cpu.H);

}

void opcd_rlc_c(){
	// RLC C
	// lenght is 1 byte
	// Rotate the register A left with C flag
	// before: C  b7 b6 b5 b4 b3 b2 b1 b0
	// after : b7 b6 b5 b4 b3 b2 b1 b0 b7
	//
	// b7 is both in the LSC and C flag
	//
	// Z = set
	// N = 0
	// H = 0
	// C = set

	dprintf("RLC C\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register C before is: 0x%2x\n",cpu.C);
	dprintf("Register C before is: 0b%8b\n",cpu.C);

	lsb = cpu.C & GET7BIT;
	lsb >>= 7; // b7
	setc(lsb);

	cpu.C <<= 1;
	cpu.C = lsb | cpu.C ;

	setz(cpu.C == 0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register C after is: 0x%2x\n",cpu.C);
	dprintf("Register C after is: 0b%b\n",cpu.C);

}

void opcd_rlca(){
	// RLCA
	// lenght is 1 byte
	// Rotate the register A left with C flag
	// before: C  b7 b6 b5 b4 b3 b2 b1 b0
	// after : b7 b6 b5 b4 b3 b2 b1 b0 b7
	//
	// b7 is both in the LSB and C flag
	//
	// Z = 0
	// N = 0
	// H = 0
	// C = set

	dprintf("RLCA\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register A before is: 0x%2x\n",cpu.A);
	dprintf("Register A before is: 0b%8b\n",cpu.A);

	lsb = cpu.A & GET7BIT;
	lsb >>= 7; // b7
	setc(lsb);

	cpu.A <<= 1;
	cpu.A = lsb | cpu.A ;

	setz(0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register A after is: 0x%2x\n",cpu.A);
	dprintf("Register A after is: 0b%b\n",cpu.A);

}

void opcd_rrc_c(){
	// RRC C
	// lenght is 1 byte
	// Rotate the register C right with C flag
	// before:  b7 b6 b5 b4 b3 b2 b1 b0 C
	// after :  b0 b7 b6 b5 b4 b3 b2 b1 b0
	//
	// b0 is both in the MSC and C flag
	//
	// Z = set
	// N = 0
	// H = 0
	// C = set

	dprintf("RRC C\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register C before is: 0x%2x\n",cpu.C);
	dprintf("Register C before is: 0b%8b\n",cpu.C);

	lsb = cpu.C & GET0BIT; // b0
	setc(lsb);

	cpu.C >>= 1;
	lsb <<= 7;
	cpu.C = lsb | cpu.C ;

	setz(cpu.C == 0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register C after is: 0x%2x\n",cpu.C);
	dprintf("Register C after is: 0b%b\n",cpu.C);

}

void opcd_rrc_e(){
	// RRC E
	// lenght is 1 byte
	// Rotate the register E right with C flag
	// before:  b7 b6 b5 b4 b3 b2 b1 b0 C
	// after :  b0 b7 b6 b5 b4 b3 b2 b1 b0
	//
	// b0 is both in the MSE and C flag
	//
	// Z = set
	// N = 0
	// H = 0
	// C = set

	dprintf("RRC E\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register E before is: 0x%2x\n",cpu.E);
	dprintf("Register E before is: 0b%8b\n",cpu.E);

	lsb = cpu.E & GET0BIT; // b0
	setc(lsb);

	cpu.E >>= 1;
	lsb <<= 7;
	cpu.E = lsb | cpu.E ;

	setz(cpu.E == 0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register E after is: 0x%2x\n",cpu.E);
	dprintf("Register E after is: 0b%b\n",cpu.E);

}

void opcd_rrc_h(){
	// RRC H
	// lenght is 1 byte
	// Rotate the register H right with C flag
	// before:  b7 b6 b5 b4 b3 b2 b1 b0 C
	// after :  b0 b7 b6 b5 b4 b3 b2 b1 b0
	//
	// b0 is both in the MSH and C flag
	//
	// Z = set
	// N = 0
	// H = 0
	// C = set

	dprintf("RRC H\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register H before is: 0x%2x\n",cpu.H);
	dprintf("Register H before is: 0b%8b\n",cpu.H);

	lsb = cpu.H & GET0BIT; // b0
	setc(lsb);

	cpu.H >>= 1;
	lsb <<= 7;
	cpu.H = lsb | cpu.H ;

	setz(cpu.H == 0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register H after is: 0x%2x\n",cpu.H);
	dprintf("Register H after is: 0b%b\n",cpu.H);

}

void opcd_rrc_l(){
	// RRC L
	// lenght is 1 byte
	// Rotate the register L right with C flag
	// before:  b7 b6 b5 b4 b3 b2 b1 b0 C
	// after :  b0 b7 b6 b5 b4 b3 b2 b1 b0
	//
	// b0 is both in the MSL and C flag
	//
	// Z = set
	// N = 0
	// H = 0
	// C = set

	dprintf("RRC L\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register L before is: 0x%2x\n",cpu.L);
	dprintf("Register L before is: 0b%8b\n",cpu.L);

	lsb = cpu.L & GET0BIT; // b0
	setc(lsb);

	cpu.L >>= 1;
	lsb <<= 7;
	cpu.L = lsb | cpu.L ;

	setz(cpu.L == 0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register L after is: 0x%2x\n",cpu.L);
	dprintf("Register L after is: 0b%b\n",cpu.L);

}

void opcd_rrc_hl(){
	// RRC (HL)
	// lenght is 1 byte
	// Rotate the value at HL right with C flag
	// before:  b7 b6 b5 b4 b3 b2 b1 b0 C
	// after :  b0 b7 b6 b5 b4 b3 b2 b1 b0
	//
	// b0 is both in the MSL and C flag
	//
	// Z = set
	// N = 0
	// H = 0
	// C = set

	dprintf("RRC (HL)\n");

	u8 = memory_read(getHL());

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("value at HL before is: 0x%2x\n",u8);
	dprintf("value at HL before is: 0b%8b\n",u8);

	lsb = u8 & GET0BIT; // b0
	setc(lsb);

	u8 >>= 1;
	lsb <<= 7;
	u8 = lsb | u8 ;
	memory_write(getHL(),u8);

	setz(u8 == 0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("value at HL after is: 0x%2x\n",u8);
	dprintf("value at HL after is: 0b%8b\n",u8);

}

void opcd_rrc_a(){
	// RRC A
	// lenght is 1 byte
	// Rotate the register A right with C flag
	// before:  b7 b6 b5 b4 b3 b2 b1 b0 C
	// after :  b0 b7 b6 b5 b4 b3 b2 b1 b0
	//
	// b0 is both in the MSA and C flag
	//
	// Z = set
	// N = 0
	// H = 0
	// C = set

	dprintf("RRC A\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register A before is: 0x%2x\n",cpu.A);
	dprintf("Register A before is: 0b%8b\n",cpu.A);

	lsb = cpu.A & GET0BIT; // b0
	setc(lsb);

	cpu.A >>= 1;
	lsb <<= 7;
	cpu.A = lsb | cpu.A ;

	setz(cpu.A == 0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register A after is: 0x%2x\n",cpu.A);
	dprintf("Register A after is: 0b%b\n",cpu.A);

}

void opcd_rrc_d(){
	// RRC D
	// lenght is 1 byte
	// Rotate the register D right with C flag
	// before:  b7 b6 b5 b4 b3 b2 b1 b0 C
	// after :  b0 b7 b6 b5 b4 b3 b2 b1 b0
	//
	// b0 is both in the MSD and C flag
	//
	// Z = set
	// N = 0
	// H = 0
	// C = set

	dprintf("RRC D\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register D before is: 0x%2x\n",cpu.D);
	dprintf("Register D before is: 0b%8b\n",cpu.D);

	lsb = cpu.D & GET0BIT; // b0
	setc(lsb);

	cpu.D >>= 1;
	lsb <<= 7;
	cpu.D = lsb | cpu.D ;

	setz(cpu.D == 0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register D after is: 0x%2x\n",cpu.D);
	dprintf("Register D after is: 0b%b\n",cpu.D);

}

void opcd_rrc_b(){
	// RRC B
	// lenght is 1 byte
	// Rotate the register B right with C flag
	// before:  b7 b6 b5 b4 b3 b2 b1 b0 C
	// after :  b0 b7 b6 b5 b4 b3 b2 b1 b0
	//
	// b0 is both in the MSB and C flag
	//
	// Z = set
	// N = 0
	// H = 0
	// C = set

	dprintf("RRC B\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register B before is: 0x%2x\n",cpu.B);
	dprintf("Register B before is: 0b%8b\n",cpu.B);

	lsb = cpu.B & GET0BIT; // b0
	setc(lsb);

	cpu.B >>= 1;
	lsb <<= 7;
	cpu.B = lsb | cpu.B ;

	setz(cpu.B == 0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register B after is: 0x%2x\n",cpu.B);
	dprintf("Register B after is: 0b%b\n",cpu.B);

}

void opcd_rrca(){
	// RRCA
	// lenght is 1 byte
	// Rotate the register A right with C flag
	// before:  b7 b6 b5 b4 b3 b2 b1 b0 C
	// after :  b0 b7 b6 b5 b4 b3 b2 b1 b0
	//
	// b0 is both in the MSB and C flag
	//
	// Z = 0
	// N = 0
	// H = 0
	// C = set

	dprintf("RRCA\n");

	dprintf("C Flag before is: 0b%b\n",getC());
	dprintf("Register A before is: 0x%2x\n",cpu.A);
	dprintf("Register A before is: 0b%8b\n",cpu.A);

	lsb = cpu.A & GET0BIT; // b0
	setc(lsb);

	cpu.A >>= 1;
	lsb <<= 7;
	cpu.A = lsb | cpu.A ;

	setz(0);
	setn(0);
	seth(0);

	dprintf("C Flag after is: 0b%b\n",getC());
	dprintf("Register A after is: 0x%2x\n",cpu.A);
	dprintf("Register A after is: 0b%b\n",cpu.A);

}

void opcd_rra(){
	// RRA
	// Rotate the values of A with the C flag
	// i.e just shift the values to the right
	// and the value of A goes into MSB and
	// LSB into the C flag
	// Just like RR A but Z flag is always 0

	dprintf("RRA\n");

	buffer = getC();
	dprintf("C(buffer) is:0b%08b\n",buffer);

	dprintf("value of register A before is : 0b%08b\n",cpu.A);

	setc(cpu.A & 0x01); //set the carry flag to the lsb

	cpu.A >>= 1; // Shift by 1 bit
	dprintf("A shifted right by 1: 0b%08b\n",cpu.A);

	buffer <<= 7;
	dprintf("buffer after shifting 0b%08b\n",buffer);
	//buffer = buffer | 0b01111111;
	//dprintf("buffer after OR'ing   0b%08b\n",buffer);

	cpu.A = cpu.A | buffer; // set the MSB to 0

	setz(0);
	setn(0);
	seth(0);

	dprintf("value of register A after is : 0b%08b\n",cpu.A);

}

void opcd_rl_c(){
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
		setn(0);
		seth(0);

		dprintf("C Flag after is: 0b%b\n",getC());
		dprintf("Z Flag after is: 0b%b\n",getz());
		dprintf("Register C after is: 0x%2x\n",cpu.C);
		dprintf("Register C after is: 0b%b\n",cpu.C);


}

void opcd_rl_b(){
		// RL B
		// lenght is 2 bytes
		// Shift the value in B by 1
		// and put carry flag value in
		// the LSB and copy the shifted
		// out bit to the carry flag

		dprintf("RL B\n");

		dprintf("C Flag before is: 0b%b\n",getC());
		dprintf("Z Flag before is: 0b%b\n",getz());
		dprintf("Register B before is: 0x%2x\n",cpu.B);
		dprintf("Register B before is: 0b%b\n",cpu.B);

		lsb = getC();
		setc(cpu.B >> 7);

		cpu.B <<= 1;
		cpu.B = lsb | cpu.B ;

		setz(cpu.B == 0);
		setn(0);
		seth(0);

		dprintf("C Flag after is: 0b%b\n",getC());
		dprintf("Z Flag after is: 0b%b\n",getz());
		dprintf("Register B after is: 0x%2x\n",cpu.B);
		dprintf("Register B after is: 0b%b\n",cpu.B);
}

void opcd_rl_d(){
		// RL D
		// lenght is 2 bytes
		// Shift the value in D by 1
		// and put carry flag value in
		// the LSD and copy the shifted
		// out bit to the carry flag

		dprintf("RL D\n");

		dprintf("C Flag before is: 0b%b\n",getC());
		dprintf("Z Flag before is: 0b%b\n",getz());
		dprintf("Register D before is: 0x%2x\n",cpu.D);
		dprintf("Register D before is: 0b%b\n",cpu.D);

		lsb = getC();
		setc(cpu.D >> 7);

		cpu.D <<= 1;
		cpu.D = lsb | cpu.D ;

		setz(cpu.D == 0);
		setn(0);
		seth(0);

		dprintf("C Flag after is: 0b%b\n",getC());
		dprintf("Z Flag after is: 0b%b\n",getz());
		dprintf("Register D after is: 0x%2x\n",cpu.D);
		dprintf("Register D after is: 0b%b\n",cpu.D);
}

void opcd_rl_e(){
		// RL E
		// lenght is 2 bytes
		// Shift the value in E by 1
		// and put carry flag value in
		// the LSE and copy the shifted
		// out bit to the carry flag

		dprintf("RL E\n");

		dprintf("C Flag before is: 0b%b\n",getC());
		dprintf("Z Flag before is: 0b%b\n",getz());
		dprintf("Register E before is: 0x%2x\n",cpu.E);
		dprintf("Register E before is: 0b%b\n",cpu.E);

		lsb = getC();
		setc(cpu.E >> 7);

		cpu.E <<= 1;
		cpu.E = lsb | cpu.E ;

		setz(cpu.E == 0);
		setn(0);
		seth(0);

		dprintf("C Flag after is: 0b%b\n",getC());
		dprintf("Z Flag after is: 0b%b\n",getz());
		dprintf("Register E after is: 0x%2x\n",cpu.E);
		dprintf("Register E after is: 0b%b\n",cpu.E);
}

void opcd_rl_h(){
		// RL H
		// lenght is 2 bytes
		// Shift the value in H by 1
		// and put carry flag value in
		// the LSH and copy the shifted
		// out bit to the carry flag

		dprintf("RL H\n");

		dprintf("C Flag before is: 0b%b\n",getC());
		dprintf("Z Flag before is: 0b%b\n",getz());
		dprintf("Register H before is: 0x%2x\n",cpu.H);
		dprintf("Register H before is: 0b%b\n",cpu.H);

		lsb = getC();
		setc(cpu.H >> 7);

		cpu.H <<= 1;
		cpu.H = lsb | cpu.H ;

		setz(cpu.H == 0);
		setn(0);
		seth(0);

		dprintf("C Flag after is: 0b%b\n",getC());
		dprintf("Z Flag after is: 0b%b\n",getz());
		dprintf("Register H after is: 0x%2x\n",cpu.H);
		dprintf("Register H after is: 0b%b\n",cpu.H);
}

void opcd_rl_a(){
		// RL A
		// lenght is 2 bytes
		// Shift the value in A by 1
		// and put carry flag value in
		// the LSA and copy the shifted
		// out bit to the carry flag

		dprintf("RL A\n");

		dprintf("C Flag before is: 0b%b\n",getC());
		dprintf("Z Flag before is: 0b%b\n",getz());
		dprintf("Register A before is: 0x%2x\n",cpu.A);
		dprintf("Register A before is: 0b%b\n",cpu.A);

		lsb = getC();
		setc(cpu.A >> 7);

		cpu.A <<= 1;
		cpu.A = lsb | cpu.A ;

		setz(cpu.A == 0);
		setn(0);
		seth(0);

		dprintf("C Flag after is: 0b%b\n",getC());
		dprintf("Z Flag after is: 0b%b\n",getz());
		dprintf("Register A after is: 0x%2x\n",cpu.A);
		dprintf("Register A after is: 0b%b\n",cpu.A);
}

void opcd_rl_l(){
		// RL L
		// lenght is 2 bytes
		// Shift the value in L by 1
		// and put carry flag value in
		// the LSL and copy the shifted
		// out bit to the carry flag

		dprintf("RL L\n");

		dprintf("C Flag before is: 0b%b\n",getC());
		dprintf("Z Flag before is: 0b%b\n",getz());
		dprintf("Register L before is: 0x%2x\n",cpu.L);
		dprintf("Register L before is: 0b%b\n",cpu.L);

		lsb = getC();
		setc(cpu.L >> 7);

		cpu.L <<= 1;
		cpu.L = lsb | cpu.L ;

		setz(cpu.L == 0);
		setn(0);
		seth(0);

		dprintf("C Flag after is: 0b%b\n",getC());
		dprintf("Z Flag after is: 0b%b\n",getz());
		dprintf("Register L after is: 0x%2x\n",cpu.L);
		dprintf("Register L after is: 0b%b\n",cpu.L);
}

void opcd_rl_hl(){
		// RL (HL)
		// lenght is 2 bytes

		dprintf("RL (HL)\n");

		dprintf("C Flag before is: 0b%b\n",getC());
		dprintf("Z Flag before is: 0b%b\n",getz());

		u8 = memory_read(getHL());

		dprintf("val before is: 0x%2x\n",u8);
		dprintf("val before is: 0b%b\n",u8);

		lsb = getC();
		setc(u8 >> 7);

		u8 <<= 1;
		u8 = lsb | u8 ;
		memory_write(getHL(),u8);

		setz(u8 == 0);
		setn(0);
		seth(0);

		dprintf("C Flag after is: 0b%b\n",getC());
		dprintf("Z Flag after is: 0b%b\n",getz());
		dprintf("val after is: 0x%2x\n",u8);
		dprintf("val after is: 0b%b\n",u8);
}


void opcd_rr_c(){
	// RR C
	// Rotate the values of C with the C flag
	// i.e just shift the values to the right
	// and the value of C goes into MSB and
	// LSB into the C flag

	dprintf("RR C\n");

	buffer = getC();
	dprintf("C flag(buffer) is:0b%b\n",buffer);

	dprintf("value of register C before is : 0b%08b\n",cpu.C);

	setc(cpu.C & 0x01); //set the carry flag to the lsb

	cpu.C >>= 1; // Shift by 1 bit

	buffer <<= 7;
	dprintf("buffer after shifting 0b%08b\n",buffer);
	//buffer = buffer | 0b01111111;
	//dprintf("buffer after OR'ing   0b%08b\n",buffer);

	cpu.C = cpu.C | buffer; // set the MSB to 0

	setz(cpu.C == 0);
	setn(0);
	seth(0);

	dprintf("value of register C after is : 0b%08b\n",cpu.C);
}

void opcd_rr_d(){
		// RR D
		// Rotate the values of D with the C flag
		// i.e just shift the values to the right
		// and the value of D goes into MSB and
		// LSB into the C flag

		dprintf("RR D\n");

		buffer = getC();
		dprintf("C(buffer) is:0b%08b\n",buffer);

		dprintf("value of register D before is : 0b%08b\n",cpu.D);

		setc(cpu.D & 0x01); //set the carry flag to the lsb

		cpu.D >>= 1; // Shift by 1 bit

		buffer <<= 7;
		dprintf("buffer after shifting 0b%08b\n",buffer);

		cpu.D = cpu.D | buffer; // set the MSB to 0

		setz(cpu.D == 0);
		setn(0);
		seth(0);

		dprintf("value of register D after is : 0b%08b\n",cpu.D);

}

void opcd_rr_b(){
		// RR B
		// Rotate the values of B with the C flag
		// i.e just shift the values to the right
		// and the value of B goes into MSB and
		// LSB into the C flag

		dprintf("RR B\n");

		buffer = getC();
		dprintf("C(buffer) is:0b%08b\n",buffer);

		dprintf("value of register B before is : 0b%08b\n",cpu.B);

		setc(cpu.B & 0x01); //set the carry flag to the lsb

		cpu.B >>= 1; // Shift by 1 bit

		buffer <<= 7;
		dprintf("buffer after shifting 0b%08b\n",buffer);

		cpu.B = cpu.B | buffer; // set the MSB to 0

		setz(cpu.B == 0);
		setn(0);
		seth(0);

		dprintf("value of register B after is : 0b%08b\n",cpu.B);

}

void opcd_rr_a(){
		// RR A
		// Rotate the values of A with the C flag
		// i.e just shift the values to the right
		// and the value of A goes into MSB and
		// LSB into the C flag

		dprintf("RR A\n");

		buffer = getC();
		dprintf("C(buffer) is:0b%08b\n",buffer);

		dprintf("value of register A before is : 0b%08b\n",cpu.A);

		setc(cpu.A & 0x01); //set the carry flag to the lsb

		cpu.A >>= 1; // Shift by 1 bit

		buffer <<= 7;
		dprintf("buffer after shifting 0b%08b\n",buffer);

		cpu.A = cpu.A | buffer; // set the MSB to 0

		setz(cpu.A == 0);
		setn(0);
		seth(0);

		dprintf("value of register A after is : 0b%08b\n",cpu.A);

}

void opcd_rr_h(){
		// RR H
		// Rotate the values of H with the C flag
		// i.e just shift the values to the right
		// and the value of H goes into MSB and
		// LSB into the C flag

		dprintf("RR H\n");

		buffer = getC();
		dprintf("C(buffer) is:0b%08b\n",buffer);

		dprintf("value of register H before is : 0b%08b\n",cpu.H);

		setc(cpu.H & 0x01); //set the carry flag to the lsb

		cpu.H >>= 1; // Shift by 1 bit

		buffer <<= 7;
		dprintf("buffer after shifting 0b%08b\n",buffer);

		cpu.H = cpu.H | buffer; // set the MSB to 0

		setz(cpu.H == 0);
		setn(0);
		seth(0);

		dprintf("value of register H after is : 0b%08b\n",cpu.H);

}

void opcd_rr_l(){
		// RR L
		// Rotate the values of L with the C flag
		// i.e just shift the values to the right
		// and the value of L goes into MSB and
		// LSB into the C flag

		dprintf("RR L\n");

		buffer = getC();
		dprintf("C(buffer) is:0b%08b\n",buffer);

		dprintf("value of register L before is : 0b%08b\n",cpu.L);

		setc(cpu.L & 0x01); //set the carry flag to the lsb

		cpu.L >>= 1; // Shift by 1 bit

		buffer <<= 7;
		dprintf("buffer after shifting 0b%08b\n",buffer);

		cpu.L = cpu.L | buffer; // set the MSB to 0

		setz(cpu.L == 0);
		setn(0);
		seth(0);

		dprintf("value of register L after is : 0b%08b\n",cpu.L);

}

void opcd_rr_hl(){
		// RR (HL)
		// Rotate the values of D with the C flag
		// i.e just shift the values to the right
		// and the value of D goes into MSB and
		// LSB into the C flag

		dprintf("RR (HL)\n");

		buffer = getC();
		dprintf("C(buffer) is:0b%08b\n",buffer);

		dprintf("value of register D before is : 0b%08b\n",cpu.D);
		u8 = memory_read(getHL());

		setc(u8 & 0x01); //set the carry flag to the lsb

		u8 >>= 1; // Shift by 1 bit

		buffer <<= 7;
		dprintf("buffer after shifting 0b%08b\n",buffer);

		u8 = u8 | buffer; // set the MSB to 0
		memory_write(getHL(),u8);

		setz(u8 == 0);
		setn(0);
		seth(0);

		dprintf("value of register D after is : 0b%08b\n",u8);

}




void opcd_rr_e(){
		// RR E
		// Rotate the values of E with the C flag
		// i.e just shift the values to the right
		// and the value of E goes into MSB and
		// LSB into the C flag

		dprintf("RR E\n");

		buffer = getC();
		dprintf("C(buffer) is:0b%08b\n",buffer);

		dprintf("value of register E before is : 0b%08b\n",cpu.E);

		setc(cpu.E & 0x01); //set the carry flag to the lsb

		cpu.E >>= 1; // Shift by 1 bit

		buffer <<= 7;
		dprintf("buffer after shifting 0b%08b\n",buffer);

		cpu.E = cpu.E | buffer; // set the MSB to 0

		setz(cpu.E == 0);
		setn(0);
		seth(0);

		dprintf("value of register E after is : 0b%08b\n",cpu.E);

}

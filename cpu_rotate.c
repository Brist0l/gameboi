#include "debug.h"
#include "flags.h"
#include "cpu.h"

void opcd_rla(){
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

		dprintf("C Flag after is: 0b%b\n",getC());
		dprintf("Z Flag after is: 0b%b\n",getz());
		dprintf("Register C after is: 0x%2x\n",cpu.C);
		dprintf("Register C after is: 0b%b\n",cpu.C);


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
		buffer = buffer | 0b01111111;
		dprintf("buffer after OR'ing   0b%08b\n",buffer);

		cpu.A = cpu.A & buffer; // set the MSB to 0

		setz(cpu.A == 0);
		setn(0);
		seth(0);

		dprintf("value of register A after is : 0b%08b\n",cpu.A);

}

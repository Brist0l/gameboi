#include "debug.h"
#include "cpu.h"
#include "flags.h"
#include "registers.h"
#include "memory.h"

void opcd_inc_bc(){
	// INC BC
	// lenght is 1 byte

	dprintf("INC BC\n");

	dprintf("Value of Register BC before: 0x%04x\n",getBC());

	result = getBC() + 1;
	setINCflags(getBC(),result);

	setBC(result);

	dprintf("Value of Register BC after: 0x%04x\n",getBC());

}

void opcd_inc_b(){
	// INC B
	// lenght is 1 byte

	dprintf("INC B\n");
	dprintf("Value of register B before is: 0x%04x\n",cpu.B);

	result = cpu.B + 1;
	setINCflags(cpu.B,result);

	cpu.B = result;


	dprintf("Value of register B after is: 0x%04x\n",cpu.B);

}

void opcd_dec_b(){
	// DEC B
	// lenght is 1 byte

	dprintf("DEC B\n");

	dprintf("Value of register B before is: 0x%02x\n",cpu.B);

	result = cpu.B - 1;
	setDECflags(cpu.B,result);
	cpu.B = result;


	dprintf("Value of register B after is: 0x%02x\n",cpu.B);

}

void opcd_inc_c(){
	// INCREASE C
	// lenght is 1 byte
	// increase val of C by 1

	dprintf("INC C\n");
	dprintf("Value of Register C before: 0x%02x\n",cpu.C);

	result = cpu.C + 1;
	setINCflags(cpu.C,result);

	cpu.C = result;

	dprintf("Value of Register C after: 0x%02x\n",cpu.C);

}

void opcd_dec_c(){
	// DECREASE C
	// lenght is 1 byte

	dprintf("DEC C\n");
	dprintf("Value of register C before is: 0x%02x\n",cpu.C);

	result = cpu.C - 1;
	setDECflags(cpu.C,result);
	cpu.C = result;

	dprintf("Value of register C after is: 0x%02x\n",cpu.C);

}

void opcd_inc_de(){
	// INC DE
	// lenght is 1 byte

	dprintf("INC DE\n");

	dprintf("Value of Register DE before: 0x%04x\n",getDE());

	result = getDE() + 1;
	setINCflags(getDE(),result);
	setDE(result);

	dprintf("Value of Register DE after: 0x%04x\n",getDE());

}

void opcd_inc_d(){
	// INC D
	// lenght is 1 byte

	dprintf("INC D\n");

	dprintf("Value of register D before is: 0x%02x\n",cpu.D);

	result = cpu.D + 1;
	setINCflags(cpu.D,result);
	cpu.D = result;

	dprintf("Value of register D after is: 0x%02x\n",cpu.D);
}

void opcd_dec_d(){
	// DEC D
	// lenght is 1 byte

	dprintf("DEC D\n");

	dprintf("Value of register D before is: 0x%02x\n",cpu.D);

	result = cpu.D - 1;
	setDECflags(cpu.D,result);
	cpu.D = result;

	dprintf("Value of register D after is: 0x%02x\n",cpu.D);

}

void opcd_inc_e(){
	// INCREASE E
	// lenght is 1 byte

	dprintf("INC E\n");
	dprintf("Value of register E before is: 0x%02x\n",cpu.E);

	result = cpu.E + 1;
	setINCflags(cpu.E,result);
	cpu.E = result;

	dprintf("Value of register E after is: 0x%02x\n",cpu.E);

}

void opcd_dec_e(){
	// DECREASE E
	// lenght is 1 byte

	dprintf("DEC E\n");
	dprintf("Value of register E before is: 0x%02x\n",cpu.E);

	result = cpu.E - 1;
	setDECflags(cpu.E,result);
	cpu.E = result;

	dprintf("Value of register E after is: 0x%02x\n",cpu.E);
}

void opcd_inc_hl(){
	// INC HL
	// lenght is 1 byte
	// Add 1 to HL

	dprintf("INC HL\n");

	dprintf("HL Register before: 0x%04x\n",getHL());
	dprintf("H Register before: 0x%02x\n",cpu.H);
	dprintf("L Register before: 0x%02x\n",cpu.L);

	result = getHL() + 1;
	setINCflags(getHL(),result);

	setHL(result);

	dprintf("HL Register after: 0x%04x\n",getHL());
	dprintf("H Register after: 0x%02x\n",cpu.H);
	dprintf("L Register after: 0x%02x\n",cpu.L);


}

void opcd_inc_h(){
	// INC H
	// lenght is 1 byte

	dprintf("INC H\n");

	dprintf("Value of register H before is: 0x%04x\n",cpu.H);

	result = cpu.H + 1;
	setINCflags(cpu.H,result);

	cpu.H = result;

	dprintf("Value of register H after is: 0x%04x\n",cpu.H);

}

void opcd_dec_h(){
	// DEC H
	// lenght is 1 byte

	dprintf("DEC H\n");

	dprintf("Value of register H before is: 0x%02x\n",cpu.H);

	result = cpu.H - 1;
	setDECflags(cpu.H,result);
	cpu.H = result;


	dprintf("Value of register H after is: 0x%02x\n",cpu.H);

}

void opcd_inc_l(){
	// INC L
	// lenght is 1 byte

	dprintf("INC L\n");
	dprintf("Value of register L before is: 0x%02x\n",cpu.L);

	result = cpu.L + 1;
	setINCflags(cpu.L,result);

	cpu.L = result;


	dprintf("Value of register L after is: 0x%02x\n",cpu.L);

}

void opcd_dec_l(){
	// DEC L
	// lenght is 1 byte

	dprintf("DEC L\n");

	dprintf("Value of register L before is: 0x%02x\n",cpu.L);

	result = cpu.L - 1;
	setDECflags(cpu.L,result);
	cpu.L = result;

	dprintf("Value of register L after is: 0x%02x\n",cpu.L);
}

void opcd_dec_at_hl(){
	// DEC (HL)
	// Dec the value at HL by 1

	dprintf("DEC (HL)\n");

	dprintf("Value of register HL is: 0x%04x\n",getHL());
	dprintf("Value at register HL is before: 0x%02x\n",memory_read(getHL()));

	HL = getHL();
	result = memory_read(HL) - 1;
	setDECflags(memory_read(HL),result);
	memory_write(getHL(),result);

	dprintf("Value at register HL is after: 0x%02x\n",memory_read(getHL()));
}

void opcd_dec_a(){
	// DEC A
	// lenght is 1 byte

	dprintf("DEC A\n");

	dprintf("Value of register A before is: 0x%02x\n",cpu.A);

	result = cpu.A - 1;
	setDECflags(cpu.A,result);
	cpu.A = result;

	dprintf("Value of register A after is: 0x%02x\n",cpu.A);

}

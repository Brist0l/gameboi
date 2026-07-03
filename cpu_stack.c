#include "cpu.h"
#include "registers.h"
#include "memory.h"
#include "debug.h"

void opcd_pop_af(){
	// POP AF

	dprintf("POP AF\n");
	dprintf("SP before: 0x%04x\n",cpu.SP);

	lsb = pop(); // F
	msb = pop();  // A
	
	lsb = 0xf0 & lsb;
	u16 = (msb << 8) | lsb;

	setAF(u16);

	dprintf("Value of register AF : 0x%04x\n",getAF());
	dprintf("SP after: 0x%04x\n",cpu.SP);
}

void opcd_pop_bc(){
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
}

void opcd_push_bc(){
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
}

void opcd_push_af(){
	// PUSH AF
	// lenght is 1 byte
	// PUSH's the value which is in AF
	// and decrements the SP twice

	dprintf("PUSH AF\n");

	AF = getAF();

	dprintf("SP val before: 0x%04x\n",cpu.SP);
	dprintf("Value of Register AF is 0x%04x\n",AF);

	lsb = AF & 0x00ff; 	  // F
	msb = (AF & 0xff00) >> 8; // A

	push(msb);
	push(lsb);

	dprintf("Pushed 0x%02x to stack\n",lsb);
	dprintf("Pushed 0x%02x to stack\n",msb);

	dprintf("stack: \n0x%02x\n0x%02x\n",msb,lsb);

	dprintf("Pushed 0x%04x to stack\n",AF);
	dprintf("SP val after: 0x%04x\n",cpu.SP);
}

void opcd_pop_de(){
	// POP DE
	// lenght is 1 byte

	dprintf("POP DE\n");
	dprintf("SP before: 0x%04x\n",cpu.SP);

	lsb = pop(); // C
	msb = pop();  // B

	u16 = (msb << 8) | lsb;

	setDE(u16);

	dprintf("Value of register DE : 0x%04x\n",getDE());
	dprintf("SP after: 0x%04x\n",cpu.SP);
}

void opcd_push_de(){
	// PUSH DE
	// lenght is 1 byte
	// PUSH's the value which is in DE
	// and decrements the SP twice

	dprintf("PUSH DE\n");
	DE = getDE();

	dprintf("SP val before: 0x%04x\n",cpu.SP);
	dprintf("Value of Register DE is 0x%04x\n",DE);

	lsb = DE & 0x00ff; 	  // C
	msb = (DE & 0xff00) >> 8; // B

	push(msb);
	push(lsb);

	dprintf("Pushed 0x%02x to stack\n",lsb);
	dprintf("Pushed 0x%02x to stack\n",msb);

	dprintf("stack: \n0x%02x\n0x%02x\n",msb,lsb);

	dprintf("Pushed 0x%04x to stack\n",DE);
	dprintf("SP val after: 0x%04x\n",cpu.SP);

}

void opcd_pop_hl(){
	// POP HL
	// lenght is 1 byte

	//if(cpu.PC == 0xc16b)
		//exit(1);

	dprintf("POP HL\n");
	dprintf("SP before: 0x%04x\n",cpu.SP);

	lsb = pop(); // C
	msb = pop();  // B

	u16 = (msb << 8) | lsb;

	setHL(u16 );

	dprintf("Value of register HL : 0x%04x\n",getHL());
	dprintf("SP after: 0x%04x\n",cpu.SP);

}

void opcd_push_hl(){
	// PUSH HL
	// lenght is 1 byte
	// PUSH's the value which is in HL
	// and decrements the SP twice

	dprintf("PUSH HL\n");
	HL = getHL();

	dprintf("SP val before: 0x%04x\n",cpu.SP);
	dprintf("Value of Register HL is 0x%04x\n",HL);

	lsb = HL & 0x00ff; 	  // C
	msb = (HL & 0xff00) >> 8; // B

	push(msb);
	push(lsb);

	dprintf("Pushed 0x%02x to stack\n",lsb);
	dprintf("Pushed 0x%02x to stack\n",msb);

	dprintf("stack: \n0x%02x\n0x%02x\n",msb,lsb);

	dprintf("Pushed 0x%04x to stack\n",HL);
	dprintf("SP val after: 0x%04x\n",cpu.SP);

}

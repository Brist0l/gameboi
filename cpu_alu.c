#include "cpu.h"
#include "flags.h"
#include "debug.h"
#include "registers.h"
#include "memory.h"

void opcd_add_hl_hl(){
	// ADD HL,HL
	// lenght is 1 byte
	// Add HL to HL and store in HL

	dprintf("ADD HL, HL");
	dprintf("Value of Register HL before: 0x%04x\n",getHL());

	setADDflags(cpu.A,cpu.B);
	setHL(getHL() + getHL());

	dprintf("Value of Register HL after: 0x%04x\n",getHL());


}

void opcd_add_a_b(){
	// ADD A,B
	// lenght is 1 byte
	// Add B to A and store in A

	dprintf("ADD A,B");
	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("Value of Register B : 0x%02x\n",cpu.B);

	setADDflags(cpu.A,cpu.B);
	cpu.A += cpu.B;


	dprintf("Value of Register A after: 0x%02x\n",cpu.A);
}

void opcd_add_a_hl(){

	// ADD A,(HL)
	// lenght is 1 byte
	// add value at the addr HL to A
	// and store in A

	dprintf("ADD A, (HL)\n");
	dprintf("Value of Register HL : 0x%04x\n",getHL());
	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("0x%02x is at 0x%04x\n",memory[getHL()],getHL());

	setADDflags(cpu.A,memory_read(getHL()));
	cpu.A += memory_read(getHL());


	dprintf("Value of Register A after: 0x%02x\n",cpu.A);

}

void opcd_add_a_a(){
	// ADD A,A
	// lenght is 1 byte
	// Add A to A and store in A

	dprintf("ADD A,A");
	dprintf("Value of Register A before: 0x%02x\n",cpu.A);

	setADDflags(cpu.A,cpu.A);
	cpu.A += cpu.A;


	dprintf("Value of Register A after: 0x%02x\n",cpu.A);

}

void opcd_sub_a_b(){
	// SUB A , B
	// lenght is 1 byte
	// subtract B from A

	dprintf("SUB B\n");
	dprintf("Value of register A before : 0x%02x\n",cpu.A);
	dprintf("Value of register B : 0x%02x\n",cpu.B);

	setSUBflags(cpu.A,cpu.B);
	cpu.A -= cpu.B;

	dprintf("Value of register A after : 0x%02x\n",cpu.A);

}

void opcd_sub_a_c(){
	// SUB A , C
	// lenght is 1 byte
	// subtract C from A

	dprintf("SUB C\n");
	dprintf("Value of register A before : 0x%02x\n",cpu.A);
	dprintf("Value of register C : 0x%02x\n",cpu.C);

	setSUBflags(cpu.A,cpu.C);
	cpu.A -= cpu.C;

	dprintf("Value of register A after : 0x%02x\n",cpu.A);
}

void opcd_or_b(){
	// OR B
	// ALU operation
	// lenght is 1 byte
	// OR's the value which is in B with A and stores in A

	dprintf("OR B\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);
	dprintf("B Register value: 0b%08b\n",cpu.B);
	result = cpu.A | cpu.B;
	setORflags(cpu.A,result);

	cpu.A = result;
	dprintf("A Register value after: 0x%08b\n",cpu.A);

}

void opcd_or_c(){
	// OR C
	// ALU operation
	// lenght is 1 byte
	// OR's the value which is in C with A and stores in A

	dprintf("OR C\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);
	dprintf("C Register value: 0b%08b\n",cpu.C);
	result = cpu.A | cpu.C;
	setORflags(cpu.A,result);

	cpu.A = result;
	dprintf("A Register value after: 0x%08b\n",cpu.A);

}

void opcd_or_hl(){
	// OR (HL)
	// ALU operation
	// lenght is 1 byte
	// OR's the value which is at memory address HL with A and stores in A

	dprintf("OR (HL)\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);
	dprintf("Value at 0x%04x is : 0x%08b\n",getHL(),memory_read(getHL()));

	result = cpu.A | memory_read(getHL());

	setORflags(cpu.A,result);
	cpu.A = result;

	dprintf("A Register value after: 0x%08b\n",cpu.A);

}

void opcd_or_a(){
	// OR A
	// ALU operation
	// lenght is 1 byte
	// OR's the value which is in A with A and stores in A

	dprintf("OR A\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);
	result = cpu.A | cpu.A;
	setORflags(cpu.A,result);

	cpu.A = result;
	dprintf("A Register value after: 0x%08b\n",cpu.A);

}

void opcd_xor_c(){
	// XOR C
	// ALU operation
	// lenght is 1 byte
	// XOR's the value which is in A with A and stores in A

	dprintf("XOR C\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);
	dprintf("C Register value before: 0b%08b\n",cpu.C);

	cpu.A ^= cpu.C;
	setXORflags(cpu.A);


	dprintf("A Register value after: 0b%08b\n",cpu.A);
}

void opcd_xor_l(){
	// XOR L
	// ALU operation
	// lenght is 1 byte
	// XOR's the value which is in L with A and stores in A

	dprintf("XOR L\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);
	dprintf("L Register value before: 0b%08b\n",cpu.L);

	cpu.A ^= cpu.L;
	setXORflags(cpu.A);

	dprintf("A Register value after: 0b%08b\n",cpu.A);
}

void opcd_xor_memhl(){
	// XOR (HL)
	// ALU operation
	// lenght is 1 byte
	// XOR's the value which is in A with value at HL and stores in A

	dprintf("XOR (HL)\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);
	dprintf("Value at HL:             0b%08b\n",memory_read(getHL()));
	dprintf("HL register value : 0x%04x\n",getHL());

	cpu.A ^= memory_read(getHL());
	setXORflags(cpu.A);


	dprintf("A Register value after: 0b%08b\n",cpu.A);

}

void opcd_xor_a(){
	// XOR A
	// ALU operation
	// lenght is 1 byte
	// XOR's the value which is in A with A and stores in A

	dprintf("XOR A\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);

	cpu.A ^= cpu.A;

	setXORflags(cpu.A);

	dprintf("A Register value after: 0b%08b\n",cpu.A);
}

void opcd_add_a_u8(){
	// ADD A,u8
	// lenght is 1 byte
	// Add u8 to A and store in A

	dprintf("ADD A, u8");

	u8 = memory_read(++cpu.PC);

	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("Value of u8 : 0x%02x\n",u8);

	setADDflags(cpu.A,u8);
	cpu.A += u8;

	dprintf("Value of Register A after: 0x%02x\n",cpu.A);
}

void opcd_cp_a_hl(){
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

	if(cpu.A - memory_read(getHL()) == 0){
		dprintf("Setting Zero flag to 1\n");
		setz(1);
	}else{
		dprintf("Setting Zero flag to 0\n");
		setz(0);
	}
}

void opcd_sub_u8(){
	// SUB u8
	// lenght is 2 byte
	// subtract u8 from A

	dprintf("SUB u8\n");

	u8 = memory_read(++cpu.PC);

	dprintf("Value of register A before: 0x%02x\n",cpu.A);
	dprintf("Value of u8: 0x%02x\n",u8);

	cpu.A -= u8;
	setSUBflags(cpu.A,u8);

	dprintf("Value of register A after : 0x%02x\n",cpu.A);
}

void opcd_and_u8(){
	// AND u8
	// lenght is 2 bytes
	// AND u8 with A and store it in A

	dprintf("AND u8\n");

	u8 = memory_read(++cpu.PC);

	dprintf("ANDing with 		    : 0b%08b\n",u8);
	dprintf("Value of register A before : 0x%08b\n",cpu.A);

	cpu.A &= u8;
	setANDflags(cpu.A);

	dprintf("Value of register A after : 0x%08b\n",cpu.A);


}

#include "cpu.h"
#include "flags.h"
#include "debug.h"
#include "registers.h"
#include "memory.h"

void opcd_add_hl_hl(){
	// ADD HL,HL
	// lenght is 1 byte
	// Add HL to HL and store in HL
	// Zero flag ain't changed

	dprintf("ADD HL, HL");
	dprintf("Value of Register HL before: 0x%04x\n",getHL());

	setADD16flags(getHL(),getHL());

	setHL(getHL() + getHL());

	dprintf("Value of Register HL after: 0x%04x\n",getHL());


}

void opcd_add_hl_bc(){
	// ADD HL,BC
	// lenght is 1 byte
	// Add HL to BC and store in HL
	// Zero flag ain't changed

	dprintf("ADD HL, BC");
	dprintf("Value of Register HL before: 0x%04x\n",getHL());
	dprintf("Value of Register BC before: 0x%04x\n",getBC());
	
	setADD16flags(getHL(),getBC());

	setHL(getHL() + getBC());

	dprintf("Value of Register HL after: 0x%04x\n",getHL());
}

void opcd_add_hl_de(){
	// ADD HL,DE
	// lenght is 1 byte
	// Add HL to DE and store in HL
	// Zero flag ain't changed

	dprintf("ADD HL, DE");
	dprintf("Value of Register HL before: 0x%04x\n",getHL());
	dprintf("Value of Register DE before: 0x%04x\n",getDE());
	
	setADD16flags(getHL(),getDE());

	setHL(getHL() + getDE());

	dprintf("Value of Register HL after: 0x%04x\n",getHL());
}

void opcd_add_hl_sp(){
	// ADD HL,SP
	// lenght is 1 byte
	// Add HL to SP and store in HL
	// Zero flag ain't changed

	dprintf("ADD HL, SP");
	dprintf("Value of Register HL before: 0x%04x\n",getHL());
	dprintf("Value of Register SP before: 0x%04x\n",cpu.SP);
	
	setADD16flags(getHL(),cpu.SP);

	setHL(getHL() + cpu.SP);

	dprintf("Value of Register HL after: 0x%04x\n",getHL());
}

void opcd_add_a_b(){
	// ADD A,B
	// lenght is 1 byte
	// Add B to A and store in A

	dprintf("ADD A,B");
	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("Value of Register B : 0x%02x\n",cpu.B);
	
	result = cpu.A + cpu.B;
	setADDflags(cpu.A,cpu.B,result);
	cpu.A = result;

	dprintf("Value of Register A after: 0x%02x\n",cpu.A);
}

void opcd_add_a_c(){
	// ADD A,C
	// lenght is 1 byte
	// Add C to A and store in A

	dprintf("ADD A,C");
	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("Value of Register C : 0x%02x\n",cpu.C);
	
	result = cpu.A + cpu.C;
	setADDflags(cpu.A,cpu.C,result);

	cpu.A = result;

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
	
	result = cpu.A + memory_read(getHL());
	setADDflags(cpu.A,memory_read(getHL()),result);
	cpu.A = result;


	dprintf("Value of Register A after: 0x%02x\n",cpu.A);

}

void opcd_add_a_a(){
	// ADD A,A
	// lenght is 1 byte
	// Add A to A and store in A

	dprintf("ADD A,A");
	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	
	result = cpu.A + cpu.A;
	setADDflags(cpu.A,cpu.A,result);
	cpu.A = result;


	dprintf("Value of Register A after: 0x%02x\n",cpu.A);

}

void opcd_sub_a_b(){
	// SUB A , B
	// lenght is 1 byte
	// subtract B from A

	dprintf("SUB B\n");
	dprintf("Value of register A before : 0x%02x\n",cpu.A);
	dprintf("Value of register B : 0x%02x\n",cpu.B);
	
	result = cpu.A - cpu.B;
	setSUBflags(cpu.A,cpu.B,result);
	cpu.A = result;

	dprintf("Value of register A after : 0x%02x\n",cpu.A);
}

void opcd_sub_a_c(){
	// SUB A , C
	// lenght is 1 byte
	// subtract C from A

	dprintf("SUB C\n");
	dprintf("Value of register A before : 0x%02x\n",cpu.A);
	dprintf("Value of register C : 0x%02x\n",cpu.C);
	
	result = cpu.A - cpu.C;
	setSUBflags(cpu.A,cpu.C,result);
	cpu.A = result;

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
	setORflags(result);

	cpu.A = result;
	dprintf("A Register value after: 0x%08b\n",cpu.A);

}

void opcd_or_u8(){
	// OR u8
	// ALU operation
	// lenght is 1 byte
	// OR's the value u8 with A and stores in A

	dprintf("OR u8\n");

	dprintf("A Register value before: 0b%08b\n",cpu.A);
	u8 = memory_read(++cpu.PC);
	dprintf("Value of u8 : 0x%02x\n",u8);

	result = cpu.A | u8;
	setORflags(result);

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
	setORflags(result);

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

	setORflags(result);
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
	setORflags(result);

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

	result = cpu.A + u8;
	setADDflags(cpu.A,u8,result);
	cpu.A = result;

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

void opcd_cp_c(){
	// COMPARE C
	// Same as CP u8 but this time compare with the content
	// in C
	// Basically sets flag after A-C and throws away the result
	// So if A == C then A - C is 0
	// hence ,
	// Z = 1

	dprintf("CP C\n");
	dprintf("Value of Register C is: 0x%02x\n",cpu.C);
	dprintf("Value of Register A is: 0x%02x\n",cpu.A);

	if(cpu.A - cpu.C == 0){
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
	
	result = cpu.A - u8;
	setSUBflags(cpu.A,u8,result);
	cpu.A = result;

	dprintf("Value of register A after : 0x%02x\n",cpu.A);
}

void opcd_sbc_a_u8(){
	// SBC A, u8
	// Subtract register A , u8 and carry
	// flag and store in A
	// Z = set
	// N = 1
	// H , C = set

	dprintf("SBC A, u8\n");

	u8 = memory_read(++cpu.PC);

	dprintf("Value of register A before: 0x%02x\n",cpu.A);
	dprintf("Value of u8: 0x%02x\n",u8);
	
	result = cpu.A - u8 - getC();
	setSBCflags(cpu.A,u8,getC(),result);
	cpu.A = result;

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

void opcd_adc_a_u8(){
	// ADC A,u8
	// Add u8 and C flag to A
	// Set Z flags, N = 0, H and C

	dprintf("ADC A,u8\n");

	u8 = memory_read(++cpu.PC);
	dprintf("u8 : 0x%02x\n",u8);

	dprintf("ADC A, 0x%02x\n",u8);

	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	result = cpu.A + getC() + u8;
	setADCflags(cpu.A,u8,getC(),result);

	cpu.A = result;

	dprintf("Value of Register A after: 0x%02x\n",cpu.A);
}

void opcd_add_sp_u8(){
	// ADD SP, s8
	// lenght is 1 byte
	// Add u8 to SP and store in SP

	dprintf("ADD SP, s8");

	s8 = memory_read(++cpu.PC);

	dprintf("Value of Register SP before: 0x%04x\n",cpu.SP);
	dprintf("Value of s8 : 0x%02x\n",s8);
	
	result = cpu.SP + s8;

	setADDflags(cpu.SP,s8,result);
	setz(0);

	cpu.SP = result;

	dprintf("Value of Register SP after: 0x%02x\n",cpu.SP);
}

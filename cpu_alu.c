#include "cpu.h"
#include "flags.h"
#include "debug.h"
#include "registers_cpu.h"
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

void opcd_add_a_l(){
	// ADD A,L
	// lenght is 1 byte
	// Add L to A and store in A

	dprintf("ADD A,L");
	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("Value of Register L : 0x%02x\n",cpu.L);
	
	result = cpu.A + cpu.L;
	setADDflags(cpu.A,cpu.L,result);
	cpu.A = result;

	dprintf("Value of Register A after: 0x%02x\n",cpu.A);
}

void opcd_add_a_h(){
	// ADD A,H
	// lenght is 1 byte
	// Add H to A and store in A

	dprintf("ADD A,H");
	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("Value of Register H : 0x%02x\n",cpu.H);
	
	result = cpu.A + cpu.H;
	setADDflags(cpu.A,cpu.H,result);
	cpu.A = result;

	dprintf("Value of Register A after: 0x%02x\n",cpu.A);
}

void opcd_add_a_e(){
	// ADD A,E
	// lenght is 1 byte
	// Add E to A and store in A

	dprintf("ADD A,E");
	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("Value of Register E : 0x%02x\n",cpu.E);
	
	result = cpu.A + cpu.E;
	setADDflags(cpu.A,cpu.E,result);
	cpu.A = result;

	dprintf("Value of Register A after: 0x%02x\n",cpu.A);
}

void opcd_add_a_d(){
	// ADD A,D
	// lenght is 1 byte
	// Add D to A and store in A

	dprintf("ADD A,D");
	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("Value of Register D : 0x%02x\n",cpu.D);
	
	result = cpu.A + cpu.D;
	setADDflags(cpu.A,cpu.D,result);
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

void opcd_sub_a_hl(){
	// SUB A , (HL)
	// lenght is 1 byte
	// subtract (HL) from A

	dprintf("SUB (HL)\n");
	dprintf("Value of register A before : 0x%02x\n",cpu.A);

	HL = getHL();
	dprintf("Value of register HL : 0x%04x\n",HL);
	dprintf("Value at register HL : 0x%02x\n",memory_read(HL));
	
	result = cpu.A - memory_read(HL);
	setSUBflags(cpu.A,memory_read(HL),result);
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

void opcd_sub_a_l(){
	// SUB A , L
	// lenght is 1 byte
	// subtract L from A

	dprintf("SUB L\n");
	dprintf("Value of register A before : 0x%02x\n",cpu.A);
	dprintf("Value of register L : 0x%02x\n",cpu.L);
	
	result = cpu.A - cpu.L;
	setSUBflags(cpu.A,cpu.L,result);
	cpu.A = result;

	dprintf("Value of register A after : 0x%02x\n",cpu.A);
}

void opcd_sub_a_h(){
	// SUB A , H
	// lenght is 1 byte
	// subtract H from A

	dprintf("SUB H\n");
	dprintf("Value of register A before : 0x%02x\n",cpu.A);
	dprintf("Value of register H : 0x%02x\n",cpu.H);
	
	result = cpu.A - cpu.H;
	setSUBflags(cpu.A,cpu.H,result);
	cpu.A = result;

	dprintf("Value of register A after : 0x%02x\n",cpu.A);
}

void opcd_sub_a_e(){
	// SUB A , E
	// lenght is 1 byte
	// subtract E from A

	dprintf("SUB E\n");
	dprintf("Value of register A before : 0x%02x\n",cpu.A);
	dprintf("Value of register E : 0x%02x\n",cpu.E);
	
	result = cpu.A - cpu.E;
	setSUBflags(cpu.A,cpu.E,result);
	cpu.A = result;

	dprintf("Value of register A after : 0x%02x\n",cpu.A);
}

void opcd_sub_a_d(){
	// SUB A , D
	// lenght is 1 byte
	// subtract D from A

	dprintf("SUB D\n");
	dprintf("Value of register A before : 0x%02x\n",cpu.A);
	dprintf("Value of register D : 0x%02x\n",cpu.D);
	
	result = cpu.A - cpu.D;
	setSUBflags(cpu.A,cpu.D,result);
	cpu.A = result;

	dprintf("Value of register A after : 0x%02x\n",cpu.A);
}

void opcd_sub_a_a(){
	// SUB A , A
	// lenght is 1 byte
	// subtract A from A

	dprintf("SUB A\n");
	dprintf("Value of register A before : 0x%02x\n",cpu.A);
	
	result = cpu.A - cpu.A;
	setSUBflags(cpu.A,cpu.A,result);
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

void opcd_or_d(){
	// OR D
	// ALU operation
	// lenght is 1 byte
	// OR's the value which is in D with A and stores in A

	dprintf("OR D\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);
	dprintf("D Register value: 0b%08b\n",cpu.D);

	result = cpu.A | cpu.D;
	setORflags(result);

	cpu.A = result;
	dprintf("A Register value after: 0x%08b\n",cpu.A);

}

void opcd_or_e(){
	// OR E
	// ALU operation
	// lenght is 1 byte
	// OR's the value which is in E with A and stores in A

	dprintf("OR E\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);
	dprintf("E Register value: 0b%08b\n",cpu.E);

	result = cpu.A | cpu.E;
	setORflags(result);

	cpu.A = result;
	dprintf("A Register value after: 0x%08b\n",cpu.A);

}

void opcd_or_h(){
	// OR H
	// ALU operation
	// lenght is 1 byte
	// OR's the value which is in H with A and stores in A

	dprintf("OR H\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);
	dprintf("H Register value: 0b%08b\n",cpu.H);

	result = cpu.A | cpu.H;
	setORflags(result);

	cpu.A = result;
	dprintf("A Register value after: 0x%08b\n",cpu.A);

}

void opcd_or_l(){
	// OR L
	// ALU operation
	// lenght is 1 byte
	// OR's the value which is in L with A and stores in A

	dprintf("OR L\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);
	dprintf("L Register value: 0b%08b\n",cpu.L);

	result = cpu.A | cpu.L;
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
	// XOR's the value which is in A with A and stores in A

	dprintf("XOR L\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);
	dprintf("L Register value before: 0b%08b\n",cpu.L);

	cpu.A ^= cpu.L;
	setXORflags(cpu.A);


	dprintf("A Register value after: 0b%08b\n",cpu.A);
}

void opcd_xor_h(){
	// XOR H
	// ALU operation
	// lenght is 1 byte
	// XOR's the value which is in A with A and stores in A

	dprintf("XOR H\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);
	dprintf("H Register value before: 0b%08b\n",cpu.H);

	cpu.A ^= cpu.H;
	setXORflags(cpu.A);


	dprintf("A Register value after: 0b%08b\n",cpu.A);
}

void opcd_xor_e(){
	// XOR E
	// ALU operation
	// lenght is 1 byte
	// XOR's the value which is in A with A and stores in A

	dprintf("XOR E\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);
	dprintf("E Register value before: 0b%08b\n",cpu.E);

	cpu.A ^= cpu.E;
	setXORflags(cpu.A);


	dprintf("A Register value after: 0b%08b\n",cpu.A);
}

void opcd_xor_d(){
	// XOR D
	// ALU operation
	// lenght is 1 byte
	// XOR's the value which is in A with A and stores in A

	dprintf("XOR D\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);
	dprintf("D Register value before: 0b%08b\n",cpu.D);

	cpu.A ^= cpu.D;
	setXORflags(cpu.A);


	dprintf("A Register value after: 0b%08b\n",cpu.A);
}

void opcd_xor_b(){
	// XOR B
	// ALU operation
	// lenght is 1 byte
	// XOR's the value which is in A with A and stores in A

	dprintf("XOR B\n");
	dprintf("A Register value before: 0b%08b\n",cpu.A);
	dprintf("B Register value before: 0b%08b\n",cpu.B);

	cpu.A ^= cpu.B;
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
	dprintf("A Register value before: 0b%08b\n",cpu.A);

	cpu.A ^= cpu.A;
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

	setCPflags(cpu.A , memory_read(getHL()));
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

	setCPflags(cpu.A , cpu.C);
}

void opcd_cp_b(){
	// COMPARE B
	// Same as CP u8 but this time compare with the content
	// in B
	// Basically sets flag after A-B and throws away the result
	// So if A == B then A - B is 0
	// hence ,
	// Z = 1

	dprintf("CP B\n");
	dprintf("Value of Register B is: 0x%02x\n",cpu.B);
	dprintf("Value of Register A is: 0x%02x\n",cpu.A);

	setCPflags(cpu.A , cpu.B);
}

void opcd_cp_d(){
	// COMPARE D
	// Same as CP u8 but this time compare with the content
	// in D
	// Dasically sets flag after A-D and throws away the result
	// So if A == D then A - D is 0
	// hence ,
	// Z = 1

	dprintf("CP D\n");
	dprintf("Value of Register D is: 0x%02x\n",cpu.D);
	dprintf("Value of Register A is: 0x%02x\n",cpu.A);

	setCPflags(cpu.A , cpu.D);
}

void opcd_cp_e(){
	// COMPARE E
	// Same as CP u8 but this time compare with the content
	// in E
	// Easically sets flag after A-E and throws away the result
	// So if A == E then A - E is 0
	// hence ,
	// Z = 1

	dprintf("CP E\n");
	dprintf("Value of Register E is: 0x%02x\n",cpu.E);
	dprintf("Value of Register A is: 0x%02x\n",cpu.A);

	setCPflags(cpu.A , cpu.E);
}

void opcd_cp_h(){
	// COMPARE H
	// Same as CP u8 but this time compare with the content
	// in H
	// Hasically sets flag after A-H and throws away the result
	// So if A == H then A - H is 0
	// hence ,
	// Z = 1

	dprintf("CP H\n");
	dprintf("Value of Register H is: 0x%02x\n",cpu.H);
	dprintf("Value of Register A is: 0x%02x\n",cpu.A);

	setCPflags(cpu.A , cpu.H);
}

void opcd_cp_l(){
	// COMPARE L
	// Same as CP u8 but this time compare with the content
	// in L
	// Lasically sets flag after A-L and throws away the result
	// So if A == L then A - L is 0
	// hence ,
	// Z = 1

	dprintf("CP L\n");
	dprintf("Value of Register L is: 0x%02x\n",cpu.L);
	dprintf("Value of Register A is: 0x%02x\n",cpu.A);

	setCPflags(cpu.A , cpu.L);
}

void opcd_cp_a(){
	// COMPARE A
	// Same as CP u8 but this time compare with the content
	// in A
	// Aasically sets flag after A-A and throws away the result
	// So if A == A then A - A is 0
	// hence ,
	// Z = 1

	dprintf("CP A\n");
	dprintf("Value of Register A is: 0x%02x\n",cpu.A);

	setCPflags(cpu.A , cpu.A);
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

void opcd_sbc_a_a(){
	// SBC A, A
	// Subtract register A , A and carry
	// flag and store in A
	// Z = set
	// N = 1
	// H , C = set

	dprintf("SBC A, A\n");


	dprintf("Value of register A before: 0x%02x\n",cpu.A);
	
	result = cpu.A - cpu.A - getC();
	setSBCflags(cpu.A,cpu.A,getC(),result);
	cpu.A = result;

	dprintf("Value of register A after : 0x%02x\n",cpu.A);
}

void opcd_sbc_a_b(){
	// SBC A, B
	// Subtract register A , B and carry
	// flag and store in A
	// Z = set
	// N = 1
	// H , C = set

	dprintf("SBC A, u8\n");


	dprintf("Value of register A before: 0x%02x\n",cpu.A);
	
	result = cpu.A - cpu.B - getC();
	setSBCflags(cpu.A,cpu.B,getC(),result);
	cpu.A = result;

	dprintf("Value of register A after : 0x%02x\n",cpu.A);
}

void opcd_sbc_a_c(){
	// SBC A, C
	// Subtract register A , C and carry
	// flag and store in A
	// Z = set
	// N = 1
	// H , C = set

	dprintf("SBC A, C\n");


	dprintf("Value of register A before: 0x%02x\n",cpu.A);
	
	result = cpu.A - cpu.C - getC();
	setSBCflags(cpu.A,cpu.C,getC(),result);
	cpu.A = result;

	dprintf("Value of register A after : 0x%02x\n",cpu.A);
}

void opcd_sbc_a_d(){
	// SBC A, D
	// Subtract register A , D and carry
	// flag and store in A
	// Z = set
	// N = 1
	// H , C = set

	dprintf("SBC A, D\n");


	dprintf("Value of register A before: 0x%02x\n",cpu.A);
	
	result = cpu.A - cpu.D - getC();
	setSBCflags(cpu.A,cpu.D,getC(),result);
	cpu.A = result;

	dprintf("Value of register A after : 0x%02x\n",cpu.A);
}

void opcd_sbc_a_e(){
	// SBC A, E
	// Subtract register A , E and carry
	// flag and store in A
	// Z = set
	// N = 1
	// H , C = set

	dprintf("SBC A, E\n");


	dprintf("Value of register A before: 0x%02x\n",cpu.A);
	
	result = cpu.A - cpu.E - getC();
	setSBCflags(cpu.A,cpu.E,getC(),result);
	cpu.A = result;

	dprintf("Value of register A after : 0x%02x\n",cpu.A);
}

void opcd_sbc_a_h(){
	// SBC A, H
	// Subtract register A , H and carry
	// flag and store in A
	// Z = set
	// N = 1
	// H , C = set

	dprintf("SBC A, H\n");


	dprintf("Value of register A before: 0x%02x\n",cpu.A);
	
	result = cpu.A - cpu.H - getC();
	setSBCflags(cpu.A,cpu.H,getC(),result);
	cpu.A = result;

	dprintf("Value of register A after : 0x%02x\n",cpu.A);
}

void opcd_sbc_a_l(){
	// SBC A, L
	// Subtract register A , L and carry
	// flag and store in A
	// Z = set
	// N = 1
	// L , C = set

	dprintf("SBC A, L\n");


	dprintf("Value of register A before: 0x%02x\n",cpu.A);
	
	result = cpu.A - cpu.L - getC();
	setSBCflags(cpu.A,cpu.L,getC(),result);
	cpu.A = result;

	dprintf("Value of register A after : 0x%02x\n",cpu.A);
}

void opcd_sbc_a_hl(){
	// SBC A, (HL)
	// Subtract register A , (HL) and carry
	// flag and store in A
	// Z = set
	// N = 1
	// (HL) , C = set

	dprintf("SBC A, (HL)\n");


	dprintf("Value of register A before: 0x%02x\n",cpu.A);
	
	result = cpu.A - memory_read(getHL()) - getC();
	setSBCflags(cpu.A,memory_read(getHL()),getC(),result);
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

void opcd_and_b(){
	// AND B
	// lenght is 2 bytes
	// AND B with A and store it in A

	dprintf("AND B\n");


	dprintf("ANDing with 		    : 0b%08b\n",cpu.B);
	dprintf("Value of register A before : 0x%08b\n",cpu.A);

	cpu.A &= cpu.B;
	setANDflags(cpu.A);

	dprintf("Value of register A after : 0x%08b\n",cpu.A);
}

void opcd_and_l(){
	// AND L
	// lenght is 2 bytes
	// AND L with A and store it in A

	dprintf("AND L\n");


	dprintf("ANDing with 		    : 0b%08b\n",cpu.L);
	dprintf("Value of register A before : 0x%08b\n",cpu.A);

	cpu.A &= cpu.L;
	setANDflags(cpu.A);

	dprintf("Value of register A after : 0x%08b\n",cpu.A);
}

void opcd_and_a(){
	// AND A
	// lenght is 2 bytes
	// AND A with A and store it in A

	dprintf("AND A\n");


	dprintf("ANDing with 		    : 0b%08b\n",cpu.A);
	dprintf("Value of register A before : 0x%08b\n",cpu.A);

	cpu.A &= cpu.A;
	setANDflags(cpu.A);

	dprintf("Value of register A after : 0x%08b\n",cpu.A);
}

void opcd_and_hl(){
	// AND (HL)
	// lenght is 2 bytes
	// AND (HL) with A and store it in A

	dprintf("AND (HL)\n");


	dprintf("ANDing with 		    : 0b%08b\n",memory_read(getHL()));
	dprintf("Value of register A before : 0x%08b\n",cpu.A);

	cpu.A &= memory_read(getHL());
	setANDflags(cpu.A);

	dprintf("Value of register A after : 0x%08b\n",cpu.A);
}

void opcd_and_h(){
	// AND H
	// lenght is 2 bytes
	// AND H with A and store it in A

	dprintf("AND H\n");


	dprintf("ANDing with 		    : 0b%08b\n",cpu.H);
	dprintf("Value of register A before : 0x%08b\n",cpu.A);

	cpu.A &= cpu.H;
	setANDflags(cpu.A);

	dprintf("Value of register A after : 0x%08b\n",cpu.A);
}

void opcd_and_e(){
	// AND E
	// lenght is 2 bytes
	// AND E with A and store it in A

	dprintf("AND E\n");


	dprintf("ANDing with 		    : 0b%08b\n",cpu.E);
	dprintf("Value of register A before : 0x%08b\n",cpu.A);

	cpu.A &= cpu.E;
	setANDflags(cpu.A);

	dprintf("Value of register A after : 0x%08b\n",cpu.A);
}

void opcd_and_d(){
	// AND D
	// lenght is 2 bytes
	// AND D with A and store it in A

	dprintf("AND D\n");


	dprintf("ANDing with 		    : 0b%08b\n",cpu.D);
	dprintf("Value of register A before : 0x%08b\n",cpu.A);

	cpu.A &= cpu.D;
	setANDflags(cpu.A);

	dprintf("Value of register A after : 0x%08b\n",cpu.A);
}

void opcd_and_c(){
	// AND C
	// lenght is 2 bytes
	// AND C with A and store it in A

	dprintf("AND C\n");


	dprintf("ANDing with 		    : 0b%08b\n",cpu.C);
	dprintf("Value of register A before : 0x%08b\n",cpu.A);

	cpu.A &= cpu.C;
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

void opcd_adc_a_b(){
	// ADC A,B
	// Add B and C flag to A
	// Set Z flags, N = 0, H and C

	dprintf("ADC A,B\n");

	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("Value of Register B: 0x%02x\n",cpu.B);

	result = cpu.A + getC() + cpu.B;
	setADCflags(cpu.A,cpu.B,getC(),result);

	cpu.A = result;

	dprintf("Value of Register A after: 0x%02x\n",cpu.A);
}

void opcd_adc_a_hl(){
	// ADC A,(HL)
	// Add (HL) and C flag to A
	// Set Z flags, N = 0, H and C

	dprintf("ADC A, (HL)\n");

	dprintf("Value of Register A before: 0x%02x\n",cpu.A);

	HL = getHL();
	dprintf("Value of Register HL: 0x%04x\n",HL);
	dprintf("Value at Register HL: 0x%02x\n",memory_read(HL));

	result = cpu.A + getC() + memory_read(HL);
	setADCflags(cpu.A,memory_read(HL),getC(),result);

	cpu.A = result;

	dprintf("Value of Register A after: 0x%02x\n",cpu.A);
}

void opcd_adc_a_a(){
	// ADC A,A
	// Add A and C flag to A
	// Set Z flags, N = 0, H and C

	dprintf("ADC A,A\n");

	dprintf("Value of Register A before: 0x%02x\n",cpu.A);

	result = cpu.A + getC() + cpu.A;
	setADCflags(cpu.A,cpu.A,getC(),result);

	cpu.A = result;

	dprintf("Value of Register A after: 0x%02x\n",cpu.A);
}

void opcd_adc_a_l(){
	// ADC A,L
	// Add L and C flag to A
	// Set Z flags, N = 0, H and C

	dprintf("ADC A,L\n");

	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("Value of Register L: 0x%02x\n",cpu.L);

	result = cpu.A + getC() + cpu.L;
	setADCflags(cpu.A,cpu.L,getC(),result);

	cpu.A = result;

	dprintf("Value of Register A after: 0x%02x\n",cpu.A);
}

void opcd_adc_a_h(){
	// ADC A,H
	// Add H and C flag to A
	// Set Z flags, N = 0, H and C

	dprintf("ADC A,H\n");

	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("Value of Register H: 0x%02x\n",cpu.B);

	result = cpu.A + getC() + cpu.H;
	setADCflags(cpu.A,cpu.H,getC(),result);

	cpu.A = result;

	dprintf("Value of Register A after: 0x%02x\n",cpu.A);
}

void opcd_adc_a_e(){
	// ADC A,E
	// Add E and C flag to A
	// Set Z flags, N = 0, H and C

	dprintf("ADC A,E\n");

	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("Value of Register E: 0x%02x\n",cpu.E);

	result = cpu.A + getC() + cpu.E;
	setADCflags(cpu.A,cpu.E,getC(),result);

	cpu.A = result;

	dprintf("Value of Register A after: 0x%02x\n",cpu.A);
}

void opcd_adc_a_d(){
	// ADC A,D
	// Add D and C flag to A
	// Set Z flags, N = 0, H and C

	dprintf("ADC A,D\n");

	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("Value of Register D: 0x%02x\n",cpu.D);

	result = cpu.A + getC() + cpu.D;
	setADCflags(cpu.A,cpu.D,getC(),result);

	cpu.A = result;

	dprintf("Value of Register A after: 0x%02x\n",cpu.A);
}

void opcd_adc_a_c(){
	// ADC A,C
	// Add C and C flag to A
	// Set Z flags, N = 0, H and C

	dprintf("ADC A,C\n");

	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("Value of Register C: 0x%02x\n",cpu.C);

	result = cpu.A + getC() + cpu.C;
	setADCflags(cpu.A,cpu.C,getC(),result);

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

#include "debug.h"
#include "cpu.h"
#include "flags.h"
#include "registers.h"
#include "memory.h"

// 	├── cpu_ld.c           // LD instructions

void opcd_ld_bc_u16(){
	// LD BC, u16
	// lenght is 3 bytes
	// store u16 in BC

	dprintf("LD BC, u16\n");

	u16 = get_u16();

	dprintf("LD BC, 0x%04x\n",u16);

	dprintf("Value of Register BC before: 0x%04x\n",getBC());

	setBC(u16);

	dprintf("Value of Register BC after: 0x%04x\n",getBC());

}

void opcd_ld_bc_a(){
	// LD (BC), A
	// lenght is 3 bytes
	// store u16 in BC

	dprintf("LD (BC), A\n");

	dprintf("Value of Register BC: 0x%04x\n",getBC());
	dprintf("Value of Register A : 0x%02x\n",cpu.A);
	
	memory_write(getBC(),cpu.A);

}

void opcd_ld_b_u8(){
	// LOAD B,u8
	// lenght is 2 bytes
	// Put u8 into B

	u8 = memory_read(++cpu.PC);
	dprintf("u8: 0x%02x\n",u8);

	dprintf("LD B, 0x%02x\n",u8);
	dprintf("Value of Register B before: 0x%02x\n",cpu.B);

	cpu.B = u8;

	dprintf("Value of Register B after: 0x%02x\n",cpu.B);

}

void opcd_ld_b_b(){
	// LOAD B, B
	// lenght is 1 bytes
	// Put B into B

	dprintf("LD B, B\n");
	dprintf("Value of Register B before: 0x%02x\n",cpu.B);

	cpu.B = cpu.B;

	dprintf("Value of Register B after: 0x%02x\n",cpu.B);
}

void opcd_ld_c_u8(){
	// LOAD C , u8
	// lenght is 2 bytes
	// Put the values of u8 into C

	dprintf("LD C, u8\n");

	dprintf("Register C value before : 0x%02x\n",cpu.C);
	u8 = memory_read(++cpu.PC);
	dprintf("u8: 0x%02x\n",u8);

	dprintf("LD C, 0x%02x\n",u8);

	cpu.C = u8;
	dprintf("Register C value after : 0x%02x\n",cpu.C);

}

void opcd_ld_de_u16(){
	// LOAD DE, u16
	// lenght is 3 bytes
	// store u16 in DE

	u16 = get_u16();

	dprintf("LD DE, 0x%04x\n",u16);

	dprintf("Value of Register DE before: 0x%04x\n",getDE());

	setDE(u16);

	dprintf("Value of Register DE after: 0x%04x\n",getDE());

}

void opcd_ld_de_a(){
	// LOAD (DE), A
	// lenght is 1 byte
	// store A in the memory location DE

	dprintf("LD (DE), A\n");

	DE = getDE();

	dprintf("Value of Register DE: 0x%04x\n",DE);
	dprintf("Value before at 0x%04x is 0x%02x\n",DE,memory_read(DE));

	memory_write(DE,cpu.A);

	dprintf("Value after at 0x%04x is 0x%02x\n",DE,memory_read(DE));

}

void opcd_ld_d_u8(){
	// LOAD D , u8
	// lenght is 2 bytes

	dprintf("LD D, u8\n");

	u8 = memory_read(++cpu.PC);
	dprintf("u8: 0x%02x\n",u8);

	dprintf("LD D, 0x%02x\n",u8);
	dprintf("Register D before: 0x%02x\n",cpu.D);

	cpu.D = u8;

	dprintf("Register D after: 0x%02x\n",cpu.D);

}

void opcd_ld_a_de(){
	// LOAD A,(DE)
	// lenght is 1 byte
	// put contents at addr specified by DE into A

	dprintf("LD A, (DE)\n");
	dprintf("Value of Register DE is: 0x%04x\n",getDE());
	dprintf("Value of Register A before is: 0x%02x\n",cpu.A);
	dprintf("Value at 0x%04x is: 0x%02x\n",getDE(),memory_read(getDE()));

	cpu.A = memory_read(getDE());

	dprintf("Value of Register A after is: 0x%02x\n",cpu.A);
}

void opcd_ld_a_bc(){
	// LOAD A,(BC)
	// lenght is 1 byte
	// put contents at addr specified by BC into A

	dprintf("LD A, (BC)\n");
	dprintf("Value of Register BC is: 0x%04x\n",getBC());
	dprintf("Value of Register A before is: 0x%02x\n",cpu.A);
	dprintf("Value at 0x%04x is: 0x%02x\n",getBC(),memory_read(getBC()));

	cpu.A = memory_read(getBC());

	dprintf("Value of Register A after is: 0x%02x\n",cpu.A);
}

void opcd_ld_a_hl(){
	// LOAD A, (HL)
	// lenght is 1 byte
	// put contents at addr specified by HL into A

	dprintf("LD A, (HL)\n");
	dprintf("Value of Register HL is: 0x%04x\n",getHL());
	dprintf("Value of Register A before is: 0x%02x\n",cpu.A);
	dprintf("Value at 0x%04x is: 0x%02x\n",getHL(),memory_read(getHL()));

	cpu.A = memory_read(getHL());

	dprintf("Value of Register A after is: 0x%02x\n",cpu.A);
}

void opcd_ld_e_u8(){
	// LOAD E,u8
	// lenght is 2 bytes

	dprintf("LD E, u8\n");
	u8 = memory_read(++cpu.PC);
	dprintf("u8: 0x%02x\n",u8);

	dprintf("LD E, 0x%02x\n",u8);

	dprintf("Register E value before : 0x%02x\n",cpu.E);

	cpu.E = u8;

	dprintf("Register E value after : 0x%02x\n",cpu.E);

}

void opcd_ld_hl_u16(){
	// LOAD HL,u16
	// 16-bit load instruction
	// length is 3 bytes
	// Put u16's msb in H and lsb in L

	dprintf("LD HL, u16\n");

	u16 = get_u16();

	dprintf("LD HL, 0x%04x\n",u16);

	dprintf("HL register before: 0x%04x\n",getHL());

	setHL(u16);

	dprintf("HL register after: 0x%04x\n",getHL());
}

void opcd_ld_hlplus_a(){
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

	memory_write(HL,cpu.A);
	HL++;
	setHL(HL);

	dprintf("HL Register after: 0x%04x\n",getHL());
	dprintf("H Register after: 0x%02x\n",cpu.H);
	dprintf("L Register after: 0x%02x\n",cpu.L);
	dprintf("memory at HL after: 0x%02x\n",memory[getHL() - 1]);

}

void opcd_ld_hl_e(){
	// LOAD (HL),E
	// lenght is 1 byte
	// put data of E at the memory location of HL

	dprintf("LD (HL), E\n");

	dprintf("HL Register : 0x%04x\n",getHL());
	dprintf("Value of Register E : 0x%02x\n",cpu.E);
	dprintf("memory at HL before: 0x%02x\n",memory_read(getHL()));

	HL = getHL();

	memory_write(HL,cpu.E);

	dprintf("memory at HL after: 0x%02x\n",memory_read(getHL()));
}

void opcd_ld_hl_u8(){
	// LOAD (HL), u8
	// lenght is 1 byte
	// put data u8 at the memory location of HL

	dprintf("LD (HL), u8\n");

	dprintf("HL Register : 0x%04x\n",getHL());
	u8 = memory_read(++cpu.PC);
	dprintf("u8: 0x%02x\n",u8);
	dprintf("LD (HL), 0x%02x\n",u8);
	dprintf("memory at HL before: 0x%02x\n",memory_read(getHL()));

	HL = getHL();

	memory_write(HL,u8);

	dprintf("memory at HL after: 0x%02x\n",memory_read(getHL()));
}

void opcd_ld_h_u8(){
	// LOAD H,u8
	// lenght is 2 bytes
	// Put u8 into H

	u8 = memory_read(++cpu.PC);
	dprintf("u8: 0x%02x\n",u8);

	dprintf("LD H, 0x%02x\n",u8);
	dprintf("Value of Register H before: 0x%02x\n",cpu.H);

	cpu.H = u8;

	dprintf("Value of Register H before: 0x%02x\n",cpu.H);
}

void opcd_ld_a_hlplus(){
	// LOAD A,(HL+)
	// lenght is 1 byte
	// put data at HL into  A and increment HL

	dprintf("LD A, (HL+)\n");

	dprintf("HL Register before: 0x%04x\n",getHL());
	dprintf("H Register before: 0x%02x\n",cpu.H);
	dprintf("L Register before: 0x%02x\n",cpu.L);
	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("memory at HL before: 0x%02x\n",memory[getHL()]);

	HL = getHL();

	cpu.A = memory_read(HL);
	HL++;
	setHL(HL);

	dprintf("HL Register after: 0x%04x\n",getHL());
	dprintf("H Register after: 0x%02x\n",cpu.H);
	dprintf("L Register after: 0x%02x\n",cpu.L);
	dprintf("Value of Register A after: 0x%02x\n",cpu.A);

}

void opcd_ld_a_hlmin(){
	// LOAD A,(HL-)
	// lenght is 1 byte

	dprintf("LD A, (HL-)\n");

	dprintf("HL Register before: 0x%04x\n",getHL());
	dprintf("H Register before: 0x%02x\n",cpu.H);
	dprintf("L Register before: 0x%02x\n",cpu.L);
	dprintf("Value of Register A before: 0x%02x\n",cpu.A);
	dprintf("memory at HL before: 0x%02x\n",memory[getHL()]);

	HL = getHL();

	cpu.A = memory_read(HL);
	HL--;
	setHL(HL);

	dprintf("HL Register after: 0x%04x\n",getHL());
	dprintf("H Register after: 0x%02x\n",cpu.H);
	dprintf("L Register after: 0x%02x\n",cpu.L);
	dprintf("Value of Register A after: 0x%02x\n",cpu.A);

}

void opcd_ld_l_u8(){
	// LOAD L , u8
	// lenght is 2 bytes
	// Put the value of u8 in the L register

	u8 = memory_read(++cpu.PC);
	dprintf("u8: 0x%02x\n",u8);

	dprintf("LD L, 0x%02x\n",u8);
	dprintf("Value of register L before : 0x%02x\n",cpu.L);

	cpu.L = u8;

	dprintf("Value of register L after : 0x%02x\n",cpu.L);
}

void opcd_ld_sp_u16(){
	// LOAD SP,u16
	// 16-bit load instruction
	// length is 3 bytes
	// put the u16 in the SP register

	dprintf("LD SP, u16\n");

	u16 = get_u16();

	dprintf("LD SP, 0x%04x\n",u16);

	dprintf("SP Register value before: 0x%04x\n",cpu.SP);

	cpu.SP = u16;

	dprintf("SP Register value after: 0x%04x\n",cpu.SP);

}

void opcd_ld_sp_hl(){
	// LOAD SP, HL
	// 16-bit load instruction
	// length is 3 bytes
	// put the HL in the SP register

	dprintf("LD SP, HL\n");

	dprintf("SP Register value before: 0x%04x\n",cpu.SP);
	dprintf("HL Register before: 0x%04x\n",getHL());

	cpu.SP = getHL();

	dprintf("SP Register value after: 0x%04x\n",cpu.SP);

}

void opcd_ld_hlminus_a(){
	// LOAD (HL-),A
	// 16-bit load instruction
	// length is 1 bytes
	// Put A into memory address HL and then decrement HL

	dprintf("LD (HL-), A\n");
	dprintf("HL Register before: 0x%04x\n",getHL());
	dprintf("H Register before: 0x%04x\n",cpu.H);
	dprintf("L Register before: 0x%04x\n",cpu.L);
	dprintf("Value of Register A : 0x%02x\n",cpu.A);
	dprintf("memory at HL before: 0x%02x\n",memory_read(getHL()));

	HL = getHL();

	memory_write(HL,cpu.A);
	HL--;
	setHL(HL);

	dprintf("HL Register after: 0x%04x\n",getHL());
	dprintf("H Register after: 0x%02x\n",cpu.H);
	dprintf("L Register after: 0x%02x\n",cpu.L);
	dprintf("memory at HL after: 0x%02x\n",memory_read(getHL() + 1));
}

void opcd_ld_a_u8(){
	// LOAD A , u8
	// lenght is 2 bytes

	dprintf("LD A, u8\n");
	dprintf("Register A value before : 0x%02x\n",cpu.A);

	u8 = memory_read(++cpu.PC);
	dprintf("u8: 0x%02x\n",u8);

	dprintf("LD A, 0x%02x\n",u8);

	cpu.A = u8;

	dprintf("Register A value after : 0x%02x\n",cpu.A);

}

void opcd_ld_b_hl(){
	// LOAD B,(HL)
	// lenght is 1 byte
	// put data at HL into  B

	dprintf("LD B, (HL)\n");

	dprintf("HL Register: 0x%04x\n",getHL());
	dprintf("Value of Register B before: 0x%02x\n",cpu.B);
	dprintf("value at HL: 0x%02x\n",memory_read(getHL()));

	HL = getHL();

	cpu.B = memory_read(HL);

	dprintf("Value of Register B after: 0x%02x\n",cpu.B);

}

void opcd_ld_b_a(){
	// LOAD B,A
	// lenght is 1 byte

	dprintf("LD B, A\n");
	dprintf("Register B value before : 0x%02x\n",cpu.B);
	dprintf("Register A value : 0x%02x\n",cpu.A);

	cpu.B = cpu.A;

	dprintf("Register B value after : 0x%02x\n",cpu.B);

}

void opcd_ld_b_c(){
	// LOAD B,C
	// lenght is 1 byte

	dprintf("LD B, C\n");
	dprintf("Register B value before : 0x%02x\n",cpu.B);
	dprintf("Register C value : 0x%02x\n",cpu.C);

	cpu.B = cpu.C;

	dprintf("Register B value after : 0x%02x\n",cpu.B);

}

void opcd_ld_b_d(){
	// LOAD B,D
	// lenght is 1 byte

	dprintf("LD B, D\n");
	dprintf("Register B value before : 0x%02x\n",cpu.B);
	dprintf("Register D value : 0x%02x\n",cpu.D);

	cpu.B = cpu.D;

	dprintf("Register B value after : 0x%02x\n",cpu.B);

}

void opcd_ld_b_e(){
	// LOAD B,E
	// lenght is 1 byte

	dprintf("LD B, E\n");
	dprintf("Register B value before : 0x%02x\n",cpu.B);
	dprintf("Register E value : 0x%02x\n",cpu.E);

	cpu.B = cpu.E;

	dprintf("Register B value after : 0x%02x\n",cpu.B);

}

void opcd_ld_b_h(){
	// LOAD B,H
	// lenght is 1 byte

	dprintf("LD B, H\n");
	dprintf("Register B value before : 0x%02x\n",cpu.B);
	dprintf("Register H value : 0x%02x\n",cpu.H);

	cpu.B = cpu.H;

	dprintf("Register B value after : 0x%02x\n",cpu.B);

}

void opcd_ld_b_l(){
	// LOAD B,L
	// lenght is 1 byte

	dprintf("LD B, L\n");
	dprintf("Register B value before : 0x%02x\n",cpu.B);
	dprintf("Register L value : 0x%02x\n",cpu.L);

	cpu.B = cpu.L;

	dprintf("Register B value after : 0x%02x\n",cpu.B);

}

void opcd_ld_c_b(){
	// LOAD C,B
	// lenght is 1 byte
	// Put value of B into C

	dprintf("LD C, B\n");
	dprintf("Register C value before : 0x%02x\n",cpu.C);
	dprintf("Register B value : 0x%02x\n",cpu.B);

	cpu.C = cpu.B;

	dprintf("Register C value after : 0x%02x\n",cpu.C);
}

void opcd_ld_c_c(){
	// LOAD C,C
	// lenght is 1 byte
	// Put value of C into C

	dprintf("LD C, C\n");
	dprintf("Register C value before : 0x%02x\n",cpu.C);
	dprintf("Register C value : 0x%02x\n",cpu.C);

	cpu.C = cpu.C;

	dprintf("Register C value after : 0x%02x\n",cpu.C);
}

void opcd_ld_c_d(){
	// LOAD C,D
	// lenght is 1 byte
	// Put value of D into D

	dprintf("LD D, D\n");
	dprintf("Register D value before : 0x%02x\n",cpu.D);
	dprintf("Register D value : 0x%02x\n",cpu.D);

	cpu.C = cpu.D;

	dprintf("Register D value after : 0x%02x\n",cpu.D);
}

void opcd_ld_c_e(){
	// LOAD C,E
	// lenght is 1 byte
	// Put value of E into C

	dprintf("LD C, E\n");
	dprintf("Register C value before : 0x%02x\n",cpu.C);
	dprintf("Register E value : 0x%02x\n",cpu.E);

	cpu.C = cpu.E;

	dprintf("Register C value after : 0x%02x\n",cpu.C);
}

void opcd_ld_c_h(){
	// LOAD C,H
	// lenght is 1 byte
	// Put value of H into C

	dprintf("LD C, H\n");
	dprintf("Register C value before : 0x%02x\n",cpu.C);
	dprintf("Register H value : 0x%02x\n",cpu.H);

	cpu.C = cpu.H;

	dprintf("Register C value after : 0x%02x\n",cpu.C);
}

void opcd_ld_c_l(){
	// LOAD C,L
	// lenght is 1 byte
	// Put value of L into C

	dprintf("LD C, L\n");
	dprintf("Register C value before : 0x%02x\n",cpu.C);
	dprintf("Register L value : 0x%02x\n",cpu.L);

	cpu.C = cpu.L;

	dprintf("Register C value after : 0x%02x\n",cpu.C);
}

void opcd_ld_c_hl(){
	// LOAD C,(HL)
	// lenght is 1 byte
	// put data at HL into  C

	dprintf("LD C, (HL)\n");

	dprintf("HL Register: 0x%04x\n",getHL());
	dprintf("Value of Register C before: 0x%02x\n",cpu.C);
	dprintf("value at HL: 0x%02x\n",memory_read(getHL()));

	HL = getHL();

	cpu.C = memory_read(HL);

	dprintf("Value of Register C after: 0x%02x\n",cpu.C);

}

void opcd_ld_c_a(){
	// LOAD C,A
	// lenght is 1 byte
	// Put value of A into C

	dprintf("LD C, A\n");
	dprintf("Register C value before : 0x%02x\n",cpu.C);
	dprintf("Register A value : 0x%02x\n",cpu.A);

	cpu.C = cpu.A;

	dprintf("Register C value after : 0x%02x\n",cpu.C);
}

void opcd_ld_d_b(){
	// LOAD D,B
	// lenght is 1 byte

	dprintf("LD D, B\n");

	dprintf("Register D value before : 0x%02x\n",cpu.D);
	dprintf("Register B value : 0x%02x\n",cpu.B);

	cpu.D = cpu.B;

	dprintf("Register D value after : 0x%02x\n",cpu.D);
}

void opcd_ld_d_c(){
	// LOAD D,C
	// lenght is 1 byte

	dprintf("LD D, C\n");

	dprintf("Register D value before : 0x%02x\n",cpu.D);
	dprintf("Register C value : 0x%02x\n",cpu.C);

	cpu.D = cpu.C;

	dprintf("Register D value after : 0x%02x\n",cpu.D);
}

void opcd_ld_d_d(){
	// LOAD D,D
	// lenght is 1 byte

	dprintf("LD D, D\n");

	dprintf("Register D value before : 0x%02x\n",cpu.D);
	dprintf("Register D value : 0x%02x\n",cpu.D);

	cpu.D = cpu.D;

	dprintf("Register D value after : 0x%02x\n",cpu.D);
}

void opcd_ld_d_e(){
	// LOAD D,E
	// lenght is 1 byte

	dprintf("LD D, E\n");

	dprintf("Register D value before : 0x%02x\n",cpu.D);
	dprintf("Register E value : 0x%02x\n",cpu.E);

	cpu.D = cpu.E;

	dprintf("Register D value after : 0x%02x\n",cpu.D);
}

void opcd_ld_d_h(){
	// LOAD D,H
	// lenght is 1 byte

	dprintf("LD D, H\n");

	dprintf("Register D value before : 0x%02x\n",cpu.D);
	dprintf("Register H value : 0x%02x\n",cpu.H);

	cpu.D = cpu.H;

	dprintf("Register D value after : 0x%02x\n",cpu.D);
}

void opcd_ld_d_l(){
	// LOAD D,L
	// lenght is 1 byte

	dprintf("LD D, L\n");

	dprintf("Register D value before : 0x%02x\n",cpu.D);
	dprintf("Register L value : 0x%02x\n",cpu.L);

	cpu.D = cpu.L;

	dprintf("Register D value after : 0x%02x\n",cpu.D);
}

void opcd_ld_d_hl(){
	// LOAD D,(HL)
	// lenght is 1 byte
	// put data at HL into  D

	dprintf("LD D, (HL)\n");

	dprintf("HL Register: 0x%04x\n",getHL());
	dprintf("Value of Register D before: 0x%02x\n",cpu.D);
	dprintf("value at HL: 0x%02x\n",memory_read(getHL()));

	HL = getHL();

	cpu.D = memory_read(HL);

	dprintf("Value of Register D after: 0x%02x\n",cpu.D);
}

void opcd_ld_d_a(){
	// LOAD D,A
	// lenght is 1 byte

	dprintf("LD D, A\n");

	dprintf("Register D value before : 0x%02x\n",cpu.D);
	dprintf("Register A value : 0x%02x\n",cpu.A);

	cpu.D = cpu.A;

	dprintf("Register H value after : 0x%02x\n",cpu.D);
}

void opcd_ld_e_a(){
	// LOAD E,A
	// lenght is 1 byte

	dprintf("LD E, A\n");
	dprintf("Register E value before : 0x%02x\n",cpu.E);
	dprintf("Register A value : 0x%02x\n",cpu.A);

	cpu.E = cpu.A;

	dprintf("Register E value after : 0x%02x\n",cpu.E);

}

void opcd_ld_e_l(){
	// LOAD E,L
	// lenght is 1 byte

	dprintf("LD E, L\n");
	dprintf("Register E value before : 0x%02x\n",cpu.E);
	dprintf("Register L value : 0x%02x\n",cpu.L);

	cpu.E = cpu.L;

	dprintf("Register E value after : 0x%02x\n",cpu.E);

}

void opcd_ld_e_b(){
	// LOAD E,B
	// lenght is 1 byte

	dprintf("LD E, B\n");
	dprintf("Register E value before : 0x%02x\n",cpu.E);
	dprintf("Register B value : 0x%02x\n",cpu.B);

	cpu.E = cpu.B;

	dprintf("Register E value after : 0x%02x\n",cpu.E);

}

void opcd_ld_e_c(){
	// LOAD E,C
	// lenght is 1 byte

	dprintf("LD E, C\n");
	dprintf("Register E value before : 0x%02x\n",cpu.E);
	dprintf("Register C value : 0x%02x\n",cpu.C);

	cpu.E = cpu.C;

	dprintf("Register E value after : 0x%02x\n",cpu.E);

}

void opcd_ld_e_d(){
	// LOAD E,D
	// lenght is 1 byte

	dprintf("LD E, D\n");
	dprintf("Register E value before : 0x%02x\n",cpu.E);
	dprintf("Register D value : 0x%02x\n",cpu.D);

	cpu.E = cpu.D;

	dprintf("Register E value after : 0x%02x\n",cpu.E);

}
void opcd_ld_e_e(){
	// LOAD E,E
	// lenght is 1 byte

	dprintf("LD E, E\n");
	dprintf("Register E value before : 0x%02x\n",cpu.E);
	dprintf("Register E value : 0x%02x\n",cpu.E);

	cpu.E = cpu.E;

	dprintf("Register E value after : 0x%02x\n",cpu.E);

}
void opcd_ld_e_h(){
	// LOAD E,H
	// lenght is 1 byte

	dprintf("LD E, H\n");
	dprintf("Register E value before : 0x%02x\n",cpu.E);
	dprintf("Register H value : 0x%02x\n",cpu.H);

	cpu.E = cpu.H;

	dprintf("Register E value after : 0x%02x\n",cpu.E);

}

void opcd_ld_e_hl(){
	// LOAD E,(HL)
	// lenght is 1 byte
	// put data at HL into  L

	dprintf("LD E, (HL)\n");

	dprintf("HL Register: 0x%04x\n",getHL());
	dprintf("Value of Register D before: 0x%02x\n",cpu.E);
	dprintf("value at HL: 0x%02x\n",memory_read(getHL()));

	HL = getHL();

	cpu.E = memory_read(HL);

	dprintf("Value of Register E after: 0x%02x\n",cpu.E);
}

void opcd_ld_h_a(){
	// LOAD H,A
	// lenght is 1 byte
	// Put the contents of A into the H register

	dprintf("LD H, A\n");
	dprintf("Register H value before : 0x%02x\n",cpu.H);
	dprintf("Register A value : 0x%02x\n",cpu.A);

	cpu.H = cpu.A;

	dprintf("Register H value after : 0x%02x\n",cpu.H);

}

void opcd_ld_h_b(){
	// LOAD H,B
	// lenght is 1 byte

	dprintf("LD H, B\n");
	dprintf("Register H value before : 0x%02x\n",cpu.H);
	dprintf("Register B value : 0x%02x\n",cpu.B);

	cpu.H = cpu.B;

	dprintf("Register H value after : 0x%02x\n",cpu.H);
}

void opcd_ld_h_c(){
	// LOAD H,C
	// lenght is 1 byte

	dprintf("LD H, C\n");
	dprintf("Register H value before : 0x%02x\n",cpu.H);
	dprintf("Register C value : 0x%02x\n",cpu.C);

	cpu.H = cpu.C;

	dprintf("Register H value after : 0x%02x\n",cpu.H);
}

void opcd_ld_h_d(){
	// LOAD H,D
	// lenght is 1 byte

	dprintf("LD H, D\n");
	dprintf("Register H value before : 0x%02x\n",cpu.H);
	dprintf("Register D value : 0x%02x\n",cpu.D);

	cpu.H = cpu.D;

	dprintf("Register H value after : 0x%02x\n",cpu.H);
}

void opcd_ld_h_e(){
	// LOAD H,E
	// lenght is 1 byte

	dprintf("LD H, E\n");
	dprintf("Register H value before : 0x%02x\n",cpu.H);
	dprintf("Register E value : 0x%02x\n",cpu.E);

	cpu.H = cpu.E;

	dprintf("Register H value after : 0x%02x\n",cpu.H);
}

void opcd_ld_h_h(){
	// LOAD H,H
	// lenght is 1 byte

	dprintf("LD H, H\n");
	dprintf("Register H value before : 0x%02x\n",cpu.H);
	dprintf("Register H value : 0x%02x\n",cpu.H);

	cpu.H = cpu.H;

	dprintf("Register H value after : 0x%02x\n",cpu.H);
}

void opcd_ld_h_l(){
	// LOAD H,L
	// lenght is 1 byte

	dprintf("LD H, L\n");
	dprintf("Register H value before : 0x%02x\n",cpu.H);
	dprintf("Register L value : 0x%02x\n",cpu.L);

	cpu.H = cpu.L;

	dprintf("Register H value after : 0x%02x\n",cpu.H);
}

void opcd_ld_h_hl(){
	// LOAD H,(HL)
	// lenght is 1 byte
	// put data at HL into  H

	dprintf("LD H, (HL)\n");

	dprintf("HL Register: 0x%04x\n",getHL());
	dprintf("Value of Register D before: 0x%02x\n",cpu.H);
	dprintf("value at HL: 0x%02x\n",memory_read(getHL()));

	HL = getHL();

	cpu.H = memory_read(HL);

	dprintf("Value of Register H after: 0x%02x\n",cpu.H);
}

void opcd_ld_l_hl(){
	// LOAD L,(HL)
	// lenght is 1 byte
	// put data at HL into  L

	dprintf("LD L, (HL)\n");

	dprintf("HL Register: 0x%04x\n",getHL());
	dprintf("Value of Register D before: 0x%02x\n",cpu.L);
	dprintf("value at HL: 0x%02x\n",memory_read(getHL()));

	HL = getHL();

	cpu.L = memory_read(HL);

	dprintf("Value of Register D after: 0x%02x\n",cpu.L);
}

void opcd_ld_l_a(){
	// LOAD L,A
	// lenght is 1 byte
	// put data of A into  L

	dprintf("LD L, A\n");

	dprintf("Register L value before : 0x%02x\n",cpu.L);
	dprintf("Register A value : 0x%02x\n",cpu.A);

	cpu.L = cpu.A;

	dprintf("Register L value after : 0x%02x\n",cpu.L);
}

void opcd_ld_l_b(){
	// LOAD L,B
	// lenght is 1 byte

	dprintf("LD L, B\n");

	dprintf("Register L value before : 0x%02x\n",cpu.L);
	dprintf("Register B value : 0x%02x\n",cpu.B);

	cpu.L = cpu.B;

	dprintf("Register L value after : 0x%02x\n",cpu.L);
}

void opcd_ld_l_c(){
	// LOAD L,C
	// lenght is 1 byte

	dprintf("LD L, C\n");

	dprintf("Register L value before : 0x%02x\n",cpu.L);
	dprintf("Register C value : 0x%02x\n",cpu.C);

	cpu.L = cpu.C;

	dprintf("Register L value after : 0x%02x\n",cpu.L);
}

void opcd_ld_l_d(){
	// LOAD L,D
	// lenght is 1 byte

	dprintf("LD L, D\n");

	dprintf("Register L value before : 0x%02x\n",cpu.L);
	dprintf("Register D value : 0x%02x\n",cpu.D);

	cpu.L = cpu.D;

	dprintf("Register L value after : 0x%02x\n",cpu.L);
}

void opcd_ld_l_e(){
	// LOAD L,E
	// lenght is 1 byte

	dprintf("LD L, E\n");

	dprintf("Register L value before : 0x%02x\n",cpu.L);
	dprintf("Register E value : 0x%02x\n",cpu.E);

	cpu.L = cpu.E;

	dprintf("Register L value after : 0x%02x\n",cpu.L);
}

void opcd_ld_l_h(){
	// LOAD L,H
	// lenght is 1 byte

	dprintf("LD L, H\n");

	dprintf("Register L value before : 0x%02x\n",cpu.L);
	dprintf("Register H value : 0x%02x\n",cpu.H);

	cpu.L = cpu.H;

	dprintf("Register L value after : 0x%02x\n",cpu.L);
}

void opcd_ld_l_l(){
	// LOAD L,L
	// lenght is 1 byte

	dprintf("LD L, L\n");

	dprintf("Register L value before : 0x%02x\n",cpu.L);
	dprintf("Register L value : 0x%02x\n",cpu.L);

	cpu.L = cpu.L;

	dprintf("Register L value after : 0x%02x\n",cpu.L);
}

void opcd_ld_hl_b(){
	// LOAD (HL),B
	// lenght is 1 byte
	// put data of B into memory of HL

	dprintf("LD HL, B\n");
	dprintf("Value of Register HL : 0x%04x\n",getHL());
	dprintf("Value of Register B : 0x%02x\n",cpu.B);
	dprintf("before : 0x%02x is at 0x%04x\n",memory_read(getHL()),getHL());

	memory_write(getHL(),cpu.B);

	dprintf("after : 0x%02x is at 0x%04x\n",memory_read(getHL()),getHL());

}

void opcd_ld_hl_c(){
	// LOAD (HL),C
	// lenght is 1 byte
	// put data of C into memory of HL

	dprintf("LD HL, C\n");
	dprintf("Value of Register HL : 0x%04x\n",getHL());
	dprintf("Value of Register C : 0x%02x\n",cpu.C);
	dprintf("before : 0x%02x is at 0x%04x\n",memory_read(getHL()),getHL());

	memory_write(getHL(),cpu.C);

	dprintf("after : 0x%02x is at 0x%04x\n",memory_read(getHL()),getHL());

}

void opcd_ld_hl_d(){
	// LOAD (HL),D
	// lenght is 1 byte
	// put data of A into memory of HL

	dprintf("LD HL, D\n");
	dprintf("Value of Register HL : 0x%04x\n",getHL());
	dprintf("Value of Register D : 0x%02x\n",cpu.D);
	dprintf("before : 0x%02x is at 0x%04x\n",memory_read(getHL()),getHL());

	memory_write(getHL(),cpu.D);

	dprintf("after : 0x%02x is at 0x%04x\n",memory_read(getHL()),getHL());

}

void opcd_ld_hl_h(){
	// LOAD (HL),H
	// lenght is 1 byte
	// put data of H into memory of HL

	dprintf("LD HL, H\n");
	dprintf("Value of Register HL : 0x%04x\n",getHL());
	dprintf("Value of Register H : 0x%02x\n",cpu.H);
	dprintf("before : 0x%02x is at 0x%04x\n",memory_read(getHL()),getHL());

	memory_write(getHL(),cpu.H);

	dprintf("after : 0x%02x is at 0x%04x\n",memory_read(getHL()),getHL());

}

void opcd_ld_hl_l(){
	// LOAD (HL),L
	// lenght is 1 byte
	// put data of L into memory of HL

	dprintf("LD HL, L\n");
	dprintf("Value of Register HL : 0x%04x\n",getHL());
	dprintf("Value of Register L : 0x%02x\n",cpu.L);
	dprintf("before : 0x%02x is at 0x%04x\n",memory_read(getHL()),getHL());

	memory_write(getHL(),cpu.L);

	dprintf("after : 0x%02x is at 0x%04x\n",memory_read(getHL()),getHL());

}

void opcd_ld_hl_a(){
	// LOAD (HL),A
	// lenght is 1 byte
	// put data of A into memory of HL

	dprintf("LD HL, A\n");
	dprintf("Value of Register HL : 0x%04x\n",getHL());
	dprintf("Value of Register A : 0x%02x\n",cpu.A);
	dprintf("before : 0x%02x is at 0x%04x\n",memory[getHL()],getHL());

	memory_write(getHL(),cpu.A);

	dprintf("after : 0x%02x is at 0x%04x\n",memory[getHL()],getHL());

}

void opcd_ld_hl_sp_u8(){
	// LOAD HL,SP + s8
	// lenght is 1 byte
	// put SP + u8 into HL

	dprintf("LD HL, SP  + u8\n");
	dprintf("Value of Register HL before : 0x%04x\n",getHL());
	dprintf("Value of Register SP : 0x%04x\n",cpu.SP);
	
	s8 = memory_read(++cpu.PC);
	dprintf("s8: 0x%02x\n",s8);

	HL = getHL();
	HL = cpu.SP + s8;

	seth(((cpu.SP & 0x0F) + (s8 & 0x0F)) > 0x0F);
	setc(((cpu.SP & 0xFF) + (s8 & 0xFF)) > 0xFF);
	setz(0);
	setn(0);

	setHL(HL);

	dprintf("Value of Register HL after : 0x%04x\n",getHL());

}

void opcd_ld_a_b(){
	// LOAD A,B
	// lenght is 1 byte
	// Put contents of B into A

	dprintf("LD A, B\n");
	dprintf("Register A value before : 0x%02x\n",cpu.A);
	dprintf("Register B value : 0x%02x\n",cpu.B);

	cpu.A = cpu.B;

	dprintf("Register A value after : 0x%02x\n",cpu.A);

}

void opcd_ld_a_c(){
	// LOAD A,C
	// lenght is 1 byte
	// Put contents of C into A

	dprintf("LD A, C\n");
	dprintf("Register A value before : 0x%02x\n",cpu.A);
	dprintf("Register C value : 0x%02x\n",cpu.C);

	cpu.A = cpu.C;

	dprintf("Register A value after : 0x%02x\n",cpu.A);

}

void opcd_ld_a_d(){
	// LOAD A,D
	// lenght is 1 byte
	// Put contents of D into A

	dprintf("LD A, D\n");
	dprintf("Register A value before : 0x%02x\n",cpu.A);
	dprintf("Register D value : 0x%02x\n",cpu.D);

	cpu.A = cpu.D;

	dprintf("Register A value after : 0x%02x\n",cpu.A);

}

void opcd_ld_a_e(){
	// LOAD A,E
	// lenght is 1 byte
	// Put contents of E into A

	dprintf("LD A, E\n");

	dprintf("Register A value before : 0x%02x\n",cpu.A);
	dprintf("Register E value : 0x%02x\n",cpu.E);

	cpu.A = cpu.E;

	dprintf("Register A value after : 0x%02x\n",cpu.A);

}

void opcd_ld_a_h(){
	// LOAD A,H
	// lenght is 1 byte
	// Put contents of H into A

	dprintf("LD A, H\n");
	dprintf("Register A value before : 0x%02x\n",cpu.A);
	dprintf("Register H value : 0x%02x\n",cpu.H);

	cpu.A = cpu.H;

	dprintf("Register A value after : 0x%02x\n",cpu.A);

}

void opcd_ld_a_l(){
	// LOAD A ,L
	// lenght is 1 byte
	// Put contents of L into A

	dprintf("LD A, L\n");
	dprintf("Register A value before : 0x%02x\n",cpu.A);
	dprintf("Register L value : 0x%02x\n",cpu.L);

	cpu.A = cpu.L;

	dprintf("Register A value after : 0x%02x\n",cpu.A);

}

void opcd_ld_a_a(){
	// LOAD A,A
	// lenght is 1 byte
	// Put contents of A into A

	dprintf("LD A, A\n");
	dprintf("Register A value before : 0x%02x\n",cpu.A);
	dprintf("Register A value : 0x%02x\n",cpu.A);

	cpu.A = cpu.A;

	dprintf("Register A value after : 0x%02x\n",cpu.A);

}

void opcd_ld_ff00_u8_a(){
	// LOAD (FF00 + u8),A
	// lenght is 2 bytes
	// Put A into addr of val u8+ 0xff00

	dprintf("LD (FF00 + u8),A\n");

	u8 = memory_read(++cpu.PC);
	dprintf("u8: 0x%02x\n",u8);

	u16 = 0xff00 + u8;
	dprintf("LD (0xff00 + 0x%02x),A\n",u8);
	dprintf("before : 0x%02x is at 0x%04x\n",memory[u16],u16);

	memory_write(u16 , cpu.A);

	dprintf("after : 0x%02x is at 0x%04x\n",memory[u16],u16);

}

void opcd_ld_ff00_c_a(){
	// LOAD (FF00 + C), A
	// lenght is 1 byte
	// Put A into addr of val at C + 0xff00

	dprintf("LD (0xff00 + C),A\n");
	dprintf("Putting 0x%02x at 0x%04x\n",cpu.A,cpu.C + 0xff00);
	memory_write((cpu.C + 0xff00),cpu.A);
}

void opcd_ld_u16_a(){
	// LD u16, A
	// lenght is 3 bytes
	// store the value of A at memory address u16

	dprintf("LD u16, A\n");

	u16 = get_u16();

	dprintf("LD 0x%04x, A\n",u16);

	dprintf("Storing 0x%02x at 0x%04x\n",cpu.A,u16);
	dprintf("Value at 0x%04x before: 0x%02x\n",u16,memory_read(u16));

	memory_write(u16, cpu.A);

	dprintf("Value at 0x%04x after: 0x%02x\n",u16,memory_read(u16));
}

void opcd_ld_u16_sp(){
	// LD u16, SP
	// lenght is 3 bytes
	// store the value of SP at memory address u16
	// lsb -> u16
	// msb -> u16 + 1

	dprintf("LD u16, SP\n");

	u16 = get_u16();

	dprintf("LD 0x%04x, SP\n",u16);
	dprintf("Value of register SP: 0x%04x\n",cpu.SP);

	lsb = cpu.SP  & 0x00ff; 	  // P
	msb = (cpu.SP & 0xff00) >> 8; // S

	dprintf("Storing 0x%02x at 0x%04x\n",lsb,u16);
	dprintf("Storing 0x%02x at 0x%04x\n",msb,u16 + 1);
	dprintf("Value at 0x%04x before: 0x%02x\n",u16,memory_read(u16));
	dprintf("Value at 0x%04x before: 0x%02x\n",u16 + 1,memory_read(u16 +1));

	memory_write(u16, lsb);
	memory_write(u16 + 1, msb);

	dprintf("Value at 0x%04x after: 0x%02x\n",u16,memory_read(u16));
	dprintf("Value at 0x%04x after: 0x%02x\n",u16 + 1,memory_read(u16 +1));
}


void opcd_ld_a_ff00_u8(){
	// LOAD A , (0xFF00 + u8)
	// lenght is 2 bytes
	// put the values from the memory addr (0xff00 + u8) into A

	u8 = memory_read(++cpu.PC);
	dprintf("u8: 0x%02x\n",u8);

	dprintf("LD A, (0xff00 + 0x%02x)\n",u8);

	u16 = 0xff00 + u8;

	dprintf("Memory 0x%04x has 0x%02x\n",u16,memory[u16]);
	dprintf("Value of Register A before: 0x%02x\n",cpu.A);

	cpu.A = memory_read(u16);

	dprintf("Value of Register A before: 0x%02x\n",cpu.A);

}

void opcd_ld_a_c_ff00(){
	// LOAD A , (C + 0xff00)
	// lenght is 1 bytes
	// put the values from the memory addr
	// specified by register C into A.
	// Add the contents of C with 0xff00 as
	//  contents of the internal RAM, port register
	// or mode register at the address in the range

	dprintf("LD A, (C + 0xff00)\n");

	u16 = 0xff00 + cpu.C;

	dprintf("Memory 0x%04x has 0x%02x\n",u16,memory[u16]);
	dprintf("Value of Register A before: 0x%02x\n",cpu.A);

	cpu.A = memory_read(u16);

	dprintf("Value of Register A before: 0x%02x\n",cpu.A);

	//sleep(5);

}

void opcd_ld_a_u16(){
	// LD A, (u16)
	// Lenght is 3 bytes
	// put the contents at memory location u16
	// into register A

	dprintf("LD A, (u16)\n");

	u16 = get_u16();

	dprintf("Register Value A before : 0x%02x\n",
			cpu.A);
	dprintf("Value at Address 0x%04x is : 0x%02x\n",
			u16,memory_read(u16));

	dprintf("LD A, (0x%04x)\n",u16);

	cpu.A = memory_read(u16);

	dprintf("Register Value A after : 0x%02x\n",
			cpu.A);

}

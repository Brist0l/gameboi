#include "debug.h"
#include "flags.h"
#include "cpu.h"
#include "memory.h"
#include "registers_cpu.h"

void opcd_swap_a(){
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
		
	dprintf("SWAP A\n");
	dprintf("value of register A before is : 0b%08b\n", cpu.A);

	cpu.A = (cpu.A >> 4) | (cpu.A << 4);

	setSWAPflags(cpu.A);

	dprintf("value of register A after is  : 0b%08b\n", cpu.A);
}

void opcd_swap_b(){
	// SWAP B
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
		
	dprintf("SWAP B\n");
	dprintf("value of register B before is : 0b%08b\n", cpu.B);

	cpu.B = (cpu.B >> 4) | (cpu.B << 4);

	setSWAPflags(cpu.B);

	dprintf("value of register B after is  : 0b%08b\n", cpu.B);
}

void opcd_swap_c(){
	// SWAP C
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
		
	dprintf("SWAP C\n");
	dprintf("value of register C before is : 0b%08b\n", cpu.C);

	cpu.C = (cpu.C >> 4) | (cpu.C << 4);

	setSWAPflags(cpu.C);

	dprintf("value of register C after is  : 0b%08b\n", cpu.C);
} 

void opcd_swap_d(){
	// SWAP D
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
		
	dprintf("SWAP D\n");
	dprintf("value of register D before is : 0b%08b\n", cpu.D);

	cpu.D = (cpu.D >> 4) | (cpu.D << 4);

	setSWAPflags(cpu.D);

	dprintf("value of register D after is  : 0b%08b\n", cpu.D);
}

void opcd_swap_e(){
	// SWAP E
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
		
	dprintf("SWAP E\n");
	dprintf("value of register E before is : 0b%08b\n", cpu.E);

	cpu.E = (cpu.E >> 4) | (cpu.E << 4);

	setSWAPflags(cpu.E);

	dprintf("value of register E after is  : 0b%08b\n", cpu.E);
}

void opcd_swap_h(){
	// SWAP H
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
		
	dprintf("SWAP H\n");
	dprintf("value of register H before is : 0b%08b\n", cpu.H);

	cpu.H = (cpu.H >> 4) | (cpu.H << 4);

	setSWAPflags(cpu.H);

	dprintf("value of register H after is  : 0b%08b\n", cpu.H);
}

void opcd_swap_l(){
	// SWAP L
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
		
	dprintf("SWAP L\n");
	dprintf("value of register L before is : 0b%08b\n", cpu.L);

	cpu.L = (cpu.L >> 4) | (cpu.L << 4);

	setSWAPflags(cpu.L);

	dprintf("value of register L after is  : 0b%08b\n", cpu.L);
}

void opcd_swap_hl(){
	// SWAP B
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
		
	dprintf("SWAP HL\n");

	u8 = memory_read(getHL());
	dprintf("value of register B before is : 0b%08b\n", u8);
	
	u8 = (u8 >> 4) | (u8 << 4);
	
	memory_write(getHL(),u8);
	setSWAPflags(u8);

	dprintf("value of register B after is  : 0b%08b\n", u8);
}

void opcd_srl_b(){
	// SRL B
	// lenght is 2 bytes
	// B's value is shifted to the right
	// by 1 bit.
	// The MSB is set to 0.
	// The carry flag is set to LSB
	// N and H are set to 0

	dprintf("SRL B\n");
	dprintf("value of register B before is : 0b%08b\n",cpu.B);

	setc(cpu.B & 0x01); //set the carry flag to the lsb

	cpu.B >>= 1; // Shift by 1 bit
	cpu.B = cpu.B & 0b01111111; // set the MSB to 0

	setz(cpu.B == 0);
	setn(0);
	seth(0);

	dprintf("value of register B after is : 0b%08b\n",cpu.B);

}

void opcd_srl_c(){
	// SRL C
	// lenght is 2 bytes
	// C's value is shifted to the right
	// by 1 bit.
	// The MSC is set to 0.
	// The carry flag is set to LSC
	// N and H are set to 0

	dprintf("SRL C\n");
	dprintf("value of register C before is : 0b%08b\n",cpu.C);

	setc(cpu.C & 0x01); //set the carry flag to the lsb

	cpu.C >>= 1; // Shift by 1 bit
	cpu.C = cpu.C & 0b01111111; // set the MSC to 0

	setz(cpu.C == 0);
	setn(0);
	seth(0);

	dprintf("value of register C after is : 0b%08b\n",cpu.C);

}

void opcd_srl_d(){
	// SRL D
	// lenght is 2 bytes
	// D's value is shifted to the right
	// by 1 bit.
	// The MSD is set to 0.
	// The carry flag is set to LSD
	// N and H are set to 0

	dprintf("SRL D\n");
	dprintf("value of register D before is : 0b%08b\n",cpu.D);

	setc(cpu.D & 0x01); //set the carry flag to the lsb

	cpu.D >>= 1; // Shift by 1 bit
	cpu.D = cpu.D & 0b01111111; // set the MSD to 0

	setz(cpu.D == 0);
	setn(0);
	seth(0);

	dprintf("value of register D after is : 0b%08b\n",cpu.D);

}

void opcd_srl_hl(){
	// SRL (HL)
	// lenght is 2 bytes

	dprintf("SRL (HL)\n");

	u8 = memory_read(getHL());

	dprintf("value of u8 before is : 0b%08b\n",u8);

	setc(u8 & 0x01); //set the carry flag to the lsb

	u8 >>= 1; // Shift by 1 bit
	u8 = u8 & 0b01111111; // set the MSD to 0
	
	memory_write(getHL(),u8);

	setz(u8 == 0);
	setn(0);
	seth(0);
	
	dprintf("value of u8 after is : 0b%08b\n",u8);
}

void opcd_srl_e(){
	// SRL E
	// lenght is 2 bytes
	// E's value is shifted to the right
	// by 1 bit.
	// The MSE is set to 0.
	// The carry flag is set to LSE
	// N and H are set to 0

	dprintf("SRL E\n");
	dprintf("value of register E before is : 0b%08b\n",cpu.E);

	setc(cpu.E & 0x01); //set the carry flag to the lsb

	cpu.E >>= 1; // Shift by 1 bit
	cpu.E = cpu.E & 0b01111111; // set the MSE to 0

	setz(cpu.E == 0);
	setn(0);
	seth(0);

	dprintf("value of register E after is : 0b%08b\n",cpu.E);

}

void opcd_srl_h(){
	// SRL H
	// lenght is 2 bytes
	// H's value is shifted to the right
	// by 1 bit.
	// The MSH is set to 0.
	// The carry flag is set to LSH
	// N and H are set to 0

	dprintf("SRL H\n");
	dprintf("value of register H before is : 0b%08b\n",cpu.H);

	setc(cpu.H & 0x01); //set the carry flag to the lsb

	cpu.H >>= 1; // Shift by 1 bit
	cpu.H = cpu.H & 0b01111111; // set the MSH to 0

	setz(cpu.H == 0);
	setn(0);
	seth(0);

	dprintf("value of register H after is : 0b%08b\n",cpu.H);

}

void opcd_srl_l(){
	// SRL L
	// lenght is 2 bytes
	// L's value is shifted to the right
	// by 1 bit.
	// The MSL is set to 0.
	// The carry flag is set to LSL
	// N and H are set to 0

	dprintf("SRL L\n");
	dprintf("value of register L before is : 0b%08b\n",cpu.L);

	setc(cpu.L & 0x01); //set the carry flag to the lsb

	cpu.L >>= 1; // Shift by 1 bit
	cpu.L = cpu.L & 0b01111111; // set the MSL to 0

	setz(cpu.L == 0);
	setn(0);
	seth(0);

	dprintf("value of register L after is : 0b%08b\n",cpu.L);

}

void opcd_srl_a(){
	// SRL A
	// lenght is 2 bytes
	// A's value is shifted to the right
	// by 1 bit.
	// The MSA is set to 0.
	// The carry flag is set to LSA
	// N and H are set to 0

	dprintf("SRL A\n");
	dprintf("value of register A before is : 0b%08b\n",cpu.A);

	setc(cpu.A & 0x01); //set the carry flag to the lsb

	cpu.A >>= 1; // Shift by 1 bit
	cpu.A = cpu.A & 0b01111111; // set the MSA to 0

	setz(cpu.A == 0);
	setn(0);
	seth(0);

	dprintf("value of register A after is : 0b%08b\n",cpu.A);

}

void opcd_sla_a(){
	// SLA A
	// Shifts A 1 bit 
	// Ait 7 goes in carry flag
	// b0 is 0
	//
	// C  b7 b6 b5 b4 b3 b2 b1 b0
	// b7 b6 b5 b4 b3 b2 b1 b0 0

	dprintf("SLA A\n");
	dprintf("value of register A before is: 0b%08b\n",cpu.A);

	setc((cpu.A & GET7BIT) >> 7); // set C to b7
	
	cpu.A <<= 1; //shift left by 1
	cpu.A = cpu.A & 0b11111110; // set b0 to 0
	
	setz(cpu.A == 0);
	setn(0);
	seth(0);

	dprintf("value of register A after is : 0b%08b\n",cpu.A);
}

void opcd_sla_c(){
	// SLA C
	// Shifts C 1 bit 
	// Cit 7 goes in carry flag
	// b0 is 0
	//
	// C  b7 b6 b5 b4 b3 b2 b1 b0
	// b7 b6 b5 b4 b3 b2 b1 b0 0

	dprintf("SLA C\n");
	dprintf("value of register C before is: 0b%08b\n",cpu.C);

	setc((cpu.C & GET7BIT) >> 7); // set C to b7
	
	cpu.C <<= 1; //shift left by 1
	cpu.C = cpu.C & 0b11111110; // set b0 to 0
	
	setz(cpu.C == 0);
	setn(0);
	seth(0);

	dprintf("value of register C after is : 0b%08b\n",cpu.C);
}

void opcd_sla_d(){
	// SLA D
	// Shifts D 1 bit 
	// Dit 7 goes in carry flag
	// b0 is 0
	//
	// C  b7 b6 b5 b4 b3 b2 b1 b0
	// b7 b6 b5 b4 b3 b2 b1 b0 0

	dprintf("SLA D\n");
	dprintf("value of register D before is: 0b%08b\n",cpu.D);

	setc((cpu.D & GET7BIT) >> 7); // set C to b7
	
	cpu.D <<= 1; //shift left by 1
	cpu.D = cpu.D & 0b11111110; // set b0 to 0
	
	setz(cpu.D == 0);
	setn(0);
	seth(0);

	dprintf("value of register D after is : 0b%08b\n",cpu.D);
}

void opcd_sla_e(){
	// SLA E
	// Shifts E 1 bit 
	// Eit 7 goes in carry flag
	// b0 is 0
	//
	// C  b7 b6 b5 b4 b3 b2 b1 b0
	// b7 b6 b5 b4 b3 b2 b1 b0 0

	dprintf("SLA E\n");
	dprintf("value of register E before is: 0b%08b\n",cpu.E);

	setc((cpu.E & GET7BIT) >> 7); // set C to b7
	
	cpu.E <<= 1; //shift left by 1
	cpu.E = cpu.E & 0b11111110; // set b0 to 0
	
	setz(cpu.E == 0);
	setn(0);
	seth(0);

	dprintf("value of register E after is : 0b%08b\n",cpu.E);
}

void opcd_sla_h(){
	// SLA H
	// Shifts H 1 bit 
	// Hit 7 goes in carry flag
	// b0 is 0
	//
	// C  b7 b6 b5 b4 b3 b2 b1 b0
	// b7 b6 b5 b4 b3 b2 b1 b0 0

	dprintf("SLA H\n");
	dprintf("value of register H before is: 0b%08b\n",cpu.H);

	setc((cpu.H & GET7BIT) >> 7); // set C to b7
	
	cpu.H <<= 1; //shift left by 1
	cpu.H = cpu.H & 0b11111110; // set b0 to 0
	
	setz(cpu.H == 0);
	setn(0);
	seth(0);

	dprintf("value of register H after is : 0b%08b\n",cpu.H);
}

void opcd_sla_l(){
	// SLA L
	// Shifts L 1 bit 
	// Lit 7 goes in carry flag
	// b0 is 0
	//
	// C  b7 b6 b5 b4 b3 b2 b1 b0
	// b7 b6 b5 b4 b3 b2 b1 b0 0

	dprintf("SLA L\n");
	dprintf("value of register L before is: 0b%08b\n",cpu.L);

	setc((cpu.L & GET7BIT) >> 7); // set C to b7
	
	cpu.L <<= 1; //shift left by 1
	cpu.L = cpu.L & 0b11111110; // set b0 to 0
	
	setz(cpu.L == 0);
	setn(0);
	seth(0);

	dprintf("value of register L after is : 0b%08b\n",cpu.L);
}

void opcd_sla_hl(){
	// SLA (HL)
	// Shifts (HL) 1 bit 
	// (HL)it 7 goes in carry flag
	// b0 is 0
	//
	// C  b7 b6 b5 b4 b3 b2 b1 b0
	// b7 b6 b5 b4 b3 b2 b1 b0 0


	dprintf("SLA (HL)\n");

	u8 = memory_read(getHL());

	dprintf("value of register E before is: 0b%08b\n",u8);

	setc((u8 & GET7BIT) >> 7); // set C to b7
	
	u8 <<= 1; //shift left by 1
	u8 = u8 & 0b11111110; // set b0 to 0
	memory_write(getHL(),u8);
	
	setz(u8 == 0);
	setn(0);
	seth(0);

	dprintf("value of register E after is : 0b%08b\n",u8);
}

void opcd_sla_b(){
	// SLA B
	// Shifts B 1 bit 
	// Bit 7 goes in carry flag
	// b0 is 0
	//
	// C  b7 b6 b5 b4 b3 b2 b1 b0
	// b7 b6 b5 b4 b3 b2 b1 b0 0

	dprintf("SLA B\n");
	dprintf("value of register B before is: 0b%08b\n",cpu.B);

	setc((cpu.B & GET7BIT) >> 7); // set C to b7
	
	cpu.B <<= 1; //shift left by 1
	cpu.B = cpu.B & 0b11111110; // set b0 to 0
	
	setz(cpu.B == 0);
	setn(0);
	seth(0);

	dprintf("value of register B after is : 0b%08b\n",cpu.B);
}

void opcd_sra_b(){
	// SRA B
	// Shifts B 1 bit right
	// Bit 0 goes in carry flag
	// b7 is b7
	//
	// b7 b6 b5 b4 b3 b2 b1 b0 C
	// b7 b7 b6 b5 b4 b3 b2 b1 b0 

	dprintf("SRA B\n");
	dprintf("value of register B before is: 0b%08b\n",cpu.B);

	setc(cpu.B & GET0BIT); // set C to b7
	
	buffer = cpu.B & GET7BIT; // either 00000000
				  // or     10000000

	cpu.B >>= 1; //shift right by 1
	cpu.B = cpu.B | buffer; // set b0 to 0
	
	setz(cpu.B == 0);
	setn(0);
	seth(0);

	dprintf("value of register B after is : 0b%08b\n",cpu.B);
}

void opcd_sra_a(){
	// SRA A
	// Shifts A 1 bit right
	// Ait 0 goes in carry flag
	// b7 is b7
	//
	// b7 b6 b5 b4 b3 b2 b1 b0 C
	// b7 b7 b6 b5 b4 b3 b2 b1 b0 

	dprintf("SRA A\n");
	dprintf("value of register A before is: 0b%08b\n",cpu.A);

	setc(cpu.A & GET0BIT); // set C to b7
	
	buffer = cpu.A & GET7BIT; // either 00000000
				  // or     10000000

	cpu.A >>= 1; //shift right by 1
	cpu.A = cpu.A | buffer; // set b0 to 0
	
	setz(cpu.A == 0);
	setn(0);
	seth(0);

	dprintf("value of register A after is : 0b%08b\n",cpu.A);
}

void opcd_sra_d(){
	// SRA D
	// Shifts D 1 bit right
	// Dit 0 goes in carry flag
	// b7 is b7
	//
	// b7 b6 b5 b4 b3 b2 b1 b0 C
	// b7 b7 b6 b5 b4 b3 b2 b1 b0 

	dprintf("SRA D\n");
	dprintf("value of register D before is: 0b%08b\n",cpu.D);

	setc(cpu.D & GET0BIT); // set C to b7
	
	buffer = cpu.D & GET7BIT; // either 00000000
				  // or     10000000

	cpu.D >>= 1; //shift right by 1
	cpu.D = cpu.D | buffer; // set b0 to 0
	
	setz(cpu.D == 0);
	setn(0);
	seth(0);

	dprintf("value of register D after is : 0b%08b\n",cpu.D);
}

void opcd_sra_c(){
	// SRA C
	// Shifts C 1 bit right
	// Cit 0 goes in carry flag
	// b7 is b7
	//
	// b7 b6 b5 b4 b3 b2 b1 b0 C
	// b7 b7 b6 b5 b4 b3 b2 b1 b0 

	dprintf("SRA C\n");
	dprintf("value of register C before is: 0b%08b\n",cpu.C);

	setc(cpu.C & GET0BIT); // set C to b7
	
	buffer = cpu.C & GET7BIT; // either 00000000
				  // or     10000000

	cpu.C >>= 1; //shift right by 1
	cpu.C = cpu.C | buffer; // set b0 to 0
	
	setz(cpu.C == 0);
	setn(0);
	seth(0);

	dprintf("value of register C after is : 0b%08b\n",cpu.C);
}

void opcd_sra_e(){
	// SRA E
	// Shifts E 1 bit right
	// Eit 0 goes in carry flag
	// b7 is b7
	//
	// b7 b6 b5 b4 b3 b2 b1 b0 C
	// b7 b7 b6 b5 b4 b3 b2 b1 b0 

	dprintf("SRA E\n");
	dprintf("value of register E before is: 0b%08b\n",cpu.E);

	setc(cpu.E & GET0BIT); // set C to b7
	
	buffer = cpu.E & GET7BIT; // either 00000000
				  // or     10000000

	cpu.E >>= 1; //shift right by 1
	cpu.E = cpu.E | buffer; // set b0 to 0
	
	setz(cpu.E == 0);
	setn(0);
	seth(0);

	dprintf("value of register E after is : 0b%08b\n",cpu.E);
}

void opcd_sra_h(){
	// SRA H
	// Shifts H 1 bit right
	// Hit 0 goes in carry flag
	// b7 is b7
	//
	// b7 b6 b5 b4 b3 b2 b1 b0 C
	// b7 b7 b6 b5 b4 b3 b2 b1 b0 

	dprintf("SRA H\n");
	dprintf("value of register H before is: 0b%08b\n",cpu.H);

	setc(cpu.H & GET0BIT); // set C to b7
	
	buffer = cpu.H & GET7BIT; // either 00000000
				  // or     10000000

	cpu.H >>= 1; //shift right by 1
	cpu.H = cpu.H | buffer; // set b0 to 0
	
	setz(cpu.H == 0);
	setn(0);
	seth(0);

	dprintf("value of register H after is : 0b%08b\n",cpu.H);
}

void opcd_sra_l(){
	// SRA L
	// Shifts L 1 bit right
	// Lit 0 goes in carry flag
	// b7 is b7
	//
	// b7 b6 b5 b4 b3 b2 b1 b0 C
	// b7 b7 b6 b5 b4 b3 b2 b1 b0 

	dprintf("SRA L\n");
	dprintf("value of register L before is: 0b%08b\n",cpu.L);

	setc(cpu.L & GET0BIT); // set C to b7
	
	buffer = cpu.L & GET7BIT; // either 00000000
				  // or     10000000

	cpu.L >>= 1; //shift right by 1
	cpu.L = cpu.L | buffer; // set b0 to 0
	
	setz(cpu.L == 0);
	setn(0);
	seth(0);

	dprintf("value of register L after is : 0b%08b\n",cpu.L);
}

void opcd_sra_hl(){
	// SRA (HL)
	// Shifts (HL) 1 bit right
	// Bit 0 goes in carry flag
	// b7 is b7
	//
	// b7 b6 b5 b4 b3 b2 b1 b0 C
	// b7 b7 b6 b5 b4 b3 b2 b1 b0 

	dprintf("SRA (HL)\n");
	u8 = memory_read(getHL());

	dprintf("value of register D before is: 0b%08b\n",u8);

	setc(u8 & GET0BIT); // set C to b7
	
	buffer = u8 & GET7BIT; // either 00000000
				  // or     10000000

	u8 >>= 1; //shift right by 1
	u8 = u8 | buffer; // set b0 to 0
	memory_write(getHL(),u8);
	
	setz(u8 == 0);
	setn(0);
	seth(0);

	dprintf("value of register D after is : 0b%08b\n",u8);
}

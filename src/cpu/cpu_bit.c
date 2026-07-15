#include "debug.h"
#include "cpu.h"
#include "flags.h"
#include "memory.h"
#include "registers_cpu.h"

#define GET0BIT 0b00000001
#define GET1BIT 0b00000010
#define GET2BIT 0b00000100
#define GET3BIT 0b00001000
#define GET4BIT 0b00010000
#define GET5BIT 0b00100000
#define GET6BIT 0b01000000
#define GET7BIT 0b10000000

void opcd_bit_0_b(){
		// BIT 0,B
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


		dprintf("BIT 0,B\n");
		dprintf("value of register B is : 0b%8b\n",cpu.B);

		bit = cpu.B & GET0BIT;
		bit >>= 0;

		setBITflags(bit);

		dprintf("value of 0th bit of B is : 0b%b\n",bit);
}

void opcd_bit_0_c(){
		// BIT 0,C

		dprintf("BIT 0,C\n");
		dprintf("value of register C is : 0b%8b\n",cpu.C);

		bit = cpu.C & GET0BIT;
		bit >>= 0;

		setBITflags(bit);

		dprintf("value of 0th bit of C is : 0b%b\n",bit);
}

void opcd_bit_0_d(){
		// BIT 0,D

		dprintf("BIT 0,D\n");
		dprintf("value of register D is : 0b%8b\n",cpu.D);

		bit = cpu.D & GET0BIT;
		bit >>= 0;

		setBITflags(bit);

		dprintf("value of 0th bit of D is : 0b%b\n",bit);
}

void opcd_bit_0_e(){
		// BIT 0,E

		dprintf("BIT 0,E\n");
		dprintf("value of register E is : 0b%8b\n",cpu.E);

		bit = cpu.E & GET0BIT;
		bit >>= 0;

		setBITflags(bit);

		dprintf("value of 0th bit of E is : 0b%b\n",bit);
}

void opcd_bit_0_h(){
		// BIT 0,H

		dprintf("BIT 0,H\n");
		dprintf("value of register H is : 0b%8b\n",cpu.H);

		bit = cpu.H & GET0BIT;
		bit >>= 0;

		setBITflags(bit);

		dprintf("value of 0th bit of H is : 0b%b\n",bit);
}

void opcd_bit_0_l(){
		// BIT 0,L

		dprintf("BIT 0,L\n");
		dprintf("value of register L is : 0b%8b\n",cpu.L);

		bit = cpu.L & GET0BIT;
		bit >>= 0;

		setBITflags(bit);

		dprintf("value of 0th bit of L is : 0b%b\n",bit);
}

void opcd_bit_0_a(){
		// BIT 0,A

		dprintf("BIT 0,A\n");
		dprintf("value of register A is : 0b%8b\n",cpu.A);

		bit = cpu.A & GET0BIT;
		bit >>= 0;

		setBITflags(bit);

		dprintf("value of 0th bit of A is : 0b%b\n",bit);
}

void opcd_bit_0_hl(){
		// BIT 0,(HL)

		dprintf("BIT 0,(HL)\n");
		u8 = memory_read(getHL());

		dprintf("value at HL is : 0b%b\n",u8);

		bit = u8 & GET0BIT;
		bit >>= 0;

		setBITflags(bit);

		dprintf("value of 0th bit at HL is : 0b%b\n",bit);
}

void opcd_bit_1_b(){
		// BIT 1,B

		dprintf("BIT 1,B\n");
		dprintf("value of register B is : 0b%8b\n",cpu.B);

		bit = cpu.B & GET1BIT;
		bit >>= 1;

		setBITflags(bit);

		dprintf("value of 1th bit of B is : 0b%b\n",bit);
}

void opcd_bit_1_c(){
		// BIT 1,C

		dprintf("BIT 1,C\n");
		dprintf("value of register C is : 0b%8b\n",cpu.C);

		bit = cpu.C & GET1BIT;
		bit >>= 1;

		setBITflags(bit);

		dprintf("value of 1th bit of C is : 0b%b\n",bit);
}

void opcd_bit_1_d(){
		// BIT 1,D

		dprintf("BIT 1,D\n");
		dprintf("value of register D is : 0b%8b\n",cpu.D);

		bit = cpu.D & GET1BIT;
		bit >>= 1;

		setBITflags(bit);

		dprintf("value of 1th bit of D is : 0b%b\n",bit);
}

void opcd_bit_1_e(){
		// BIT 1,E

		dprintf("BIT 1,E\n");
		dprintf("value of register E is : 0b%8b\n",cpu.E);

		bit = cpu.E & GET1BIT;
		bit >>= 1;

		setBITflags(bit);

		dprintf("value of 1th bit of E is : 0b%b\n",bit);
}

void opcd_bit_1_h(){
		// BIT 1,H

		dprintf("BIT 1,H\n");
		dprintf("value of register H is : 0b%8b\n",cpu.H);

		bit = cpu.H & GET1BIT;
		bit >>= 1;

		setBITflags(bit);

		dprintf("value of 1th bit of H is : 0b%b\n",bit);
}

void opcd_bit_1_l(){
		// BIT 1,L

		dprintf("BIT 1,L\n");
		dprintf("value of register L is : 0b%8b\n",cpu.L);

		bit = cpu.L & GET1BIT;
		bit >>= 1;

		setBITflags(bit);

		dprintf("value of 1th bit of L is : 0b%b\n",bit);
}

void opcd_bit_1_a(){
		// BIT 1,A

		dprintf("BIT 1,A\n");
		dprintf("value of register A is : 0b%8b\n",cpu.A);

		bit = cpu.A & GET1BIT;
		bit >>= 1;

		setBITflags(bit);

		dprintf("value of 1th bit of A is : 0b%b\n",bit);
}

void opcd_bit_1_hl(){
		// BIT 1,(HL)

		dprintf("BIT 1,(HL)\n");

		u8 = memory_read(getHL());

		dprintf("value at HL is : 0b%b\n",u8);

		bit = u8 & GET1BIT;
		bit >>= 1;

		setBITflags(bit);

		dprintf("value of 1th bit at HL is : 0b%b\n",bit);
}

void opcd_bit_2_b(){
		// BIT 2,B

		dprintf("BIT 2,B\n");
		dprintf("value of register B is : 0b%8b\n",cpu.B);

		bit = cpu.B & GET2BIT;
		bit >>= 2;

		setBITflags(bit);

		dprintf("value of 2th bit of B is : 0b%b\n",bit);
}

void opcd_bit_2_a(){
		// BIT 2,A

		dprintf("BIT 2,A\n");
		dprintf("value of register A is : 0b%8b\n",cpu.A);

		bit = cpu.A & GET2BIT;
		bit >>= 2;

		setBITflags(bit);

		dprintf("value of 2th bit of A is : 0b%b\n",bit);
}

void opcd_bit_2_c(){
		// BIT 2,C

		dprintf("BIT 2,C\n");
		dprintf("value of register C is : 0b%8b\n",cpu.C);

		bit = cpu.C & GET2BIT;
		bit >>= 2;

		setBITflags(bit);

		dprintf("value of 2th bit of C is : 0b%b\n",bit);
}

void opcd_bit_2_d(){
		// BIT 2,D

		dprintf("BIT 2,D\n");
		dprintf("value of register D is : 0b%8b\n",cpu.D);

		bit = cpu.D & GET2BIT;
		bit >>= 2;

		setBITflags(bit);

		dprintf("value of 2th bit of D is : 0b%b\n",bit);
}

void opcd_bit_2_e(){
		// BIT 2,E

		dprintf("BIT 2,E\n");
		dprintf("value of register E is : 0b%8b\n",cpu.E);

		bit = cpu.E & GET2BIT;
		bit >>= 2;

		setBITflags(bit);

		dprintf("value of 2th bit of E is : 0b%b\n",bit);
}

void opcd_bit_2_h(){
		// BIT 2,H

		dprintf("BIT 2,H\n");
		dprintf("value of register H is : 0b%8b\n",cpu.H);

		bit = cpu.H & GET2BIT;
		bit >>= 2;

		setBITflags(bit);

		dprintf("value of 2th bit of H is : 0b%b\n",bit);
}

void opcd_bit_2_l(){
		// BIT 2,L

		dprintf("BIT 2,L\n");
		dprintf("value of register L is : 0b%8b\n",cpu.L);

		bit = cpu.L & GET2BIT;
		bit >>= 2;

		setBITflags(bit);

		dprintf("value of 2th bit of L is : 0b%b\n",bit);
}

void opcd_bit_2_hl(){
		// BIT 2,(HL)

		dprintf("BIT 2,A\n");

		u8 = memory_read(getHL());
		dprintf("value of register A is : 0b%8b\n",u8);

		bit = u8 & GET2BIT;
		bit >>= 2;

		setBITflags(bit);

		dprintf("value of 2th bit of A is : 0b%b\n",bit);
}

void opcd_bit_3_l(){
		// BIT 3,L

		dprintf("BIT 3,L\n");
		dprintf("value of register L is : 0b%8b\n",cpu.L);

		bit = cpu.L & GET3BIT;
		bit >>= 3;

		setBITflags(bit);

		dprintf("value of 3th bit of L is : 0b%b\n",bit);
}

void opcd_bit_3_b(){
		// BIT 3,B

		dprintf("BIT 3,B\n");
		dprintf("value of register B is : 0b%8b\n",cpu.B);

		bit = cpu.B & GET3BIT;
		bit >>= 3;

		setBITflags(bit);

		dprintf("value of 3th bit of B is : 0b%b\n",bit);
}

void opcd_bit_3_a(){
		// BIT 3,A

		dprintf("BIT 3,A\n");
		dprintf("value of register A is : 0b%8b\n",cpu.A);

		bit = cpu.A & GET3BIT;
		bit >>= 3;

		setBITflags(bit);

		dprintf("value of 3th bit of A is : 0b%b\n",bit);
}

void opcd_bit_3_c(){
		// BIT 3,C

		dprintf("BIT 3,C\n");
		dprintf("value of register C is : 0b%8b\n",cpu.C);

		bit = cpu.C & GET3BIT;
		bit >>= 3;

		setBITflags(bit);

		dprintf("value of 3th bit of C is : 0b%b\n",bit);
}

void opcd_bit_3_d(){
		// BIT 3,D

		dprintf("BIT 3,D\n");
		dprintf("value of register D is : 0b%8b\n",cpu.D);

		bit = cpu.D & GET3BIT;
		bit >>= 3;

		setBITflags(bit);

		dprintf("value of 3th bit of D is : 0b%b\n",bit);
}

void opcd_bit_3_e(){
		// BIT 3,E

		dprintf("BIT 3,E\n");
		dprintf("value of register E is : 0b%8b\n",cpu.E);

		bit = cpu.E & GET3BIT;
		bit >>= 3;

		setBITflags(bit);

		dprintf("value of 3th bit of E is : 0b%b\n",bit);
}

void opcd_bit_3_h(){
		// BIT 3,H

		dprintf("BIT 3,H\n");
		dprintf("value of register H is : 0b%8b\n",cpu.H);

		bit = cpu.H & GET3BIT;
		bit >>= 3;

		setBITflags(bit);

		dprintf("value of 3th bit of H is : 0b%b\n",bit);
}

void opcd_bit_3_hl(){
		// BIT 3,(HL)

		dprintf("BIT 3,(HL)\n");
		u8 = memory_read(getHL());

		dprintf("value of register L is : 0b%8b\n",u8);

		bit = u8 & GET3BIT;
		bit >>= 3;

		setBITflags(bit);

		dprintf("value of 3th bit of L is : 0b%b\n",bit);
}

void opcd_bit_4_h(){
		// BIT 4,H

		dprintf("BIT 4,H\n");
		dprintf("value of register H is : 0b%8b\n",cpu.H);

		bit = cpu.H & GET4BIT;
		bit >>= 4;

		setBITflags(bit);

		dprintf("value of 4th bit of H is : 0b%b\n",bit);
}

void opcd_bit_4_a(){
		// BIT 4,A

		dprintf("BIT 4,A\n");
		dprintf("value of register A is : 0b%8b\n",cpu.A);

		bit = cpu.A & GET4BIT;
		bit >>= 4;

		setBITflags(bit);

		dprintf("value of 4th bit of A is : 0b%b\n",bit);
}

void opcd_bit_4_b(){
		// BIT 4,B

		dprintf("BIT 4,B\n");
		dprintf("value of register B is : 0b%8b\n",cpu.B);

		bit = cpu.B & GET4BIT;
		bit >>= 4;

		setBITflags(bit);

		dprintf("value of 4th bit of B is : 0b%b\n",bit);
}

void opcd_bit_4_c(){
		// BIT 4,C

		dprintf("BIT 4,C\n");
		dprintf("value of register C is : 0b%8b\n",cpu.C);

		bit = cpu.C & GET4BIT;
		bit >>= 4;

		setBITflags(bit);

		dprintf("value of 4th bit of C is : 0b%b\n",bit);
}

void opcd_bit_4_d(){
		// BIT 4,D

		dprintf("BIT 4,D\n");
		dprintf("value of register D is : 0b%8b\n",cpu.D);

		bit = cpu.D & GET4BIT;
		bit >>= 4;

		setBITflags(bit);

		dprintf("value of 4th bit of D is : 0b%b\n",bit);
}

void opcd_bit_4_e(){
		// BIT 4,E

		dprintf("BIT 4,E\n");
		dprintf("value of register E is : 0b%8b\n",cpu.E);

		bit = cpu.E & GET4BIT;
		bit >>= 4;

		setBITflags(bit);

		dprintf("value of 4th bit of E is : 0b%b\n",bit);
}

void opcd_bit_4_l(){
		// BIT 4,L

		dprintf("BIT 4,L\n");
		dprintf("value of register L is : 0b%8b\n",cpu.L);

		bit = cpu.L & GET4BIT;
		bit >>= 4;

		setBITflags(bit);

		dprintf("value of 4th bit of L is : 0b%b\n",bit);
}

void opcd_bit_4_hl(){
		// BIT 4,(HL)

		dprintf("BIT 4,(HL)\n");

		u8 = memory_read(getHL());
		dprintf("value of register H is : 0b%8b\n",u8);

		bit = u8 & GET4BIT;
		bit >>= 4;

		setBITflags(bit);

		dprintf("value of 4th bit of H is : 0b%b\n",bit);
}

void opcd_bit_5_a(){
		// BIT 5,A

		dprintf("BIT 5,A\n");
		dprintf("value of register A is : 0b%8b\n",cpu.A);

		bit = cpu.A & GET5BIT;
		bit >>= 5;

		setBITflags(bit);

		dprintf("value of 5th bit of A is : 0b%b\n",bit);
}

void opcd_bit_5_b(){
		// BIT 5,B

		dprintf("BIT 5,B\n");
		dprintf("value of register B is : 0b%8b\n",cpu.B);

		bit = cpu.B & GET5BIT;
		bit >>= 5;

		setBITflags(bit);

		dprintf("value of 5th bit of B is : 0b%b\n",bit);
}
void opcd_bit_5_c(){
		// BIT 5,C

		dprintf("BIT 5,C\n");
		dprintf("value of register C is : 0b%8b\n",cpu.C);

		bit = cpu.C & GET5BIT;
		bit >>= 5;

		setBITflags(bit);

		dprintf("value of 5th bit of C is : 0b%b\n",bit);
}
void opcd_bit_5_d(){
		// BIT 5,D

		dprintf("BIT 5,D\n");
		dprintf("value of register D is : 0b%8b\n",cpu.D);

		bit = cpu.D & GET5BIT;
		bit >>= 5;

		setBITflags(bit);

		dprintf("value of 5th bit of D is : 0b%b\n",bit);
}

void opcd_bit_5_e(){
		// BIT 5,E

		dprintf("BIT 5,E\n");
		dprintf("value of register E is : 0b%8b\n",cpu.E);

		bit = cpu.E & GET5BIT;
		bit >>= 5;

		setBITflags(bit);

		dprintf("value of 5th bit of E is : 0b%b\n",bit);
}
void opcd_bit_5_h(){
		// BIT 5,H

		dprintf("BIT 5,H\n");
		dprintf("value of register H is : 0b%8b\n",cpu.H);

		bit = cpu.H & GET5BIT;
		bit >>= 5;

		setBITflags(bit);

		dprintf("value of 5th bit of H is : 0b%b\n",bit);
}
void opcd_bit_5_l(){
		// BIT 5,L

		dprintf("BIT 5,L\n");
		dprintf("value of register L is : 0b%8b\n",cpu.L);

		bit = cpu.L & GET5BIT;
		bit >>= 5;

		setBITflags(bit);

		dprintf("value of 5th bit of L is : 0b%b\n",bit);
}

void opcd_bit_5_hl(){
		// BIT 5,(HL)

		dprintf("BIT 5,(HL)\n");
		u8 = memory_read(getHL());
		dprintf("value of register A is : 0b%8b\n",u8);

		bit = u8 & GET5BIT;
		bit >>= 5;

		setBITflags(bit);

		dprintf("value of 5th bit of A is : 0b%b\n",bit);
}

void opcd_bit_6_l(){
		// BIT 6,L

		dprintf("BIT 6,L\n");
		dprintf("value of register L is : 0b%8b\n",cpu.L);

		bit = cpu.L & GET6BIT;
		bit >>= 6;

		setBITflags(bit);

		dprintf("value of 6th bit of L is : 0b%b\n",bit);
}

void opcd_bit_6_a(){
		// BIT 6,A

		dprintf("BIT 6,A\n");
		dprintf("value of register A is : 0b%8b\n",cpu.A);

		bit = cpu.A & GET6BIT;
		bit >>= 6;

		setBITflags(bit);

		dprintf("value of 6th bit of A is : 0b%b\n",bit);
}

void opcd_bit_6_b(){
		// BIT 6,B

		dprintf("BIT 6,B\n");
		dprintf("value of register B is : 0b%8b\n",cpu.B);

		bit = cpu.B & GET6BIT;
		bit >>= 6;

		setBITflags(bit);

		dprintf("value of 6th bit of B is : 0b%b\n",bit);
}
void opcd_bit_6_c(){
		// BIT 6,C

		dprintf("BIT 6,C\n");
		dprintf("value of register C is : 0b%8b\n",cpu.C);

		bit = cpu.C & GET6BIT;
		bit >>= 6;

		setBITflags(bit);

		dprintf("value of 6th bit of C is : 0b%b\n",bit);
}
void opcd_bit_6_d(){
		// BIT 6,D

		dprintf("BIT 6,D\n");
		dprintf("value of register D is : 0b%8b\n",cpu.D);

		bit = cpu.D & GET6BIT;
		bit >>= 6;

		setBITflags(bit);

		dprintf("value of 6th bit of D is : 0b%b\n",bit);
}

void opcd_bit_6_e(){
		// BIT 6,E

		dprintf("BIT 6,E\n");
		dprintf("value of register E is : 0b%8b\n",cpu.E);

		bit = cpu.E & GET6BIT;
		bit >>= 6;

		setBITflags(bit);

		dprintf("value of 6th bit of E is : 0b%b\n",bit);
}

void opcd_bit_6_h(){
		// BIT 6,H

		dprintf("BIT 6,H\n");
		dprintf("value of register H is : 0b%8b\n",cpu.H);

		bit = cpu.H & GET6BIT;
		bit >>= 6;

		setBITflags(bit);

		dprintf("value of 6th bit of H is : 0b%b\n",bit);
}

void opcd_bit_6_hl(){
		// BIT 6,(HL)

		dprintf("BIT 6,(HL)\n");
		u8 = memory_read(getHL());
		dprintf("value of register L is : 0b%8b\n",u8);

		bit = u8 & GET6BIT;
		bit >>= 6;

		setBITflags(bit);

		dprintf("value of 6th bit of L is : 0b%b\n",bit);
}

void opcd_bit_7_h(){
		// BIT 7,H

		dprintf("BIT 7,H\n");
		dprintf("value of register H is : 0b%8b\n",cpu.H);

		bit = cpu.H & GET7BIT;
		bit >>= 7;

		setBITflags(bit);

		dprintf("value of 7th bit of H is : 0b%b\n",bit);
}

void opcd_bit_7_a(){
		// BIT 7,A

		dprintf("BIT 7,A\n");
		dprintf("value of register A is : 0b%8b\n",cpu.A);

		bit = cpu.A & GET7BIT;
		bit >>= 7;

		setBITflags(bit);

		dprintf("value of 7th bit of A is : 0b%b\n",bit);
}

void opcd_bit_7_b(){
		// BIT 7,B

		dprintf("BIT 7,B\n");
		dprintf("value of register B is : 0b%8b\n",cpu.B);

		bit = cpu.B & GET7BIT;
		bit >>= 7;

		setBITflags(bit);

		dprintf("value of 7th bit of B is : 0b%b\n",bit);
}

void opcd_bit_7_c(){
		// BIT 7,C

		dprintf("BIT 7,C\n");
		dprintf("value of register C is : 0b%8b\n",cpu.C);

		bit = cpu.C & GET7BIT;
		bit >>= 7;

		setBITflags(bit);

		dprintf("value of 7th bit of C is : 0b%b\n",bit);
}

void opcd_bit_7_d(){
		// BIT 7,D

		dprintf("BIT 7,D\n");
		dprintf("value of register D is : 0b%8b\n",cpu.D);

		bit = cpu.D & GET7BIT;
		bit >>= 7;

		setBITflags(bit);

		dprintf("value of 7th bit of D is : 0b%b\n",bit);
}

void opcd_bit_7_e(){
		// BIT 7,E

		dprintf("BIT 7,E\n");
		dprintf("value of register E is : 0b%8b\n",cpu.E);

		bit = cpu.E & GET7BIT;
		bit >>= 7;

		setBITflags(bit);

		dprintf("value of 7th bit of E is : 0b%b\n",bit);
}

void opcd_bit_7_l(){
		// BIT 7,L

		dprintf("BIT 7,L\n");
		dprintf("value of register L is : 0b%8b\n",cpu.L);

		bit = cpu.L & GET7BIT;
		bit >>= 7;

		setBITflags(bit);

		dprintf("value of 7th bit of L is : 0b%b\n",bit);
}

void opcd_bit_7_hl(){
		// BIT 7,(HL)

		dprintf("BIT 7,(HL)\n");
		u8 = memory_read(getHL());

		dprintf("value of register H is : 0b%8b\n",u8);

		bit = u8 & GET7BIT;
		bit >>= 7;

		setBITflags(bit);

		dprintf("value of 7th bit of H is : 0b%b\n",bit);
}

void opcd_res_0_b(){
	// RES 0, B
	// Sets the 0th bit to 0 of Register B
	
	dprintf("RES 0, B\n");

	dprintf("value of register B before is : 0b%8b\n",cpu.B);

	cpu.B &= 0b11111110;

	dprintf("value of register B after is : 0b%8b\n",cpu.B);
}

void opcd_res_0_c(){
	// RES 0, C
	// Sets the 0th bit to 0 of Register C
	
	dprintf("RES 0, C\n");

	dprintf("value of register C before is : 0b%8b\n",cpu.C);

	cpu.C &= 0b11111110;

	dprintf("value of register C after is : 0b%8b\n",cpu.C);
}

void opcd_res_0_d(){
	// RES 0, D
	// Sets the 0th bit to 0 of Register D
	
	dprintf("RES 0, D\n");

	dprintf("value of register D before is : 0b%8b\n",cpu.D);

	cpu.D &= 0b11111110;

	dprintf("value of register D after is : 0b%8b\n",cpu.D);
}

void opcd_res_0_e(){
	// RES 0, E
	// Sets the 0th bit to 0 of Register E
	
	dprintf("RES 0, E\n");

	dprintf("value of register E before is : 0b%8b\n",cpu.E);

	cpu.E &= 0b11111110;

	dprintf("value of register E after is : 0b%8b\n",cpu.E);
}

void opcd_res_0_h(){
	// RES 0, H
	// Sets the 0th bit to 0 of Register H
	
	dprintf("RES 0, H\n");

	dprintf("value of register H before is : 0b%8b\n",cpu.H);

	cpu.H &= 0b11111110;

	dprintf("value of register H after is : 0b%8b\n",cpu.H);
}

void opcd_res_0_l(){
	// RES 0, L
	// Sets the 0th bit to 0 of Register L
	
	dprintf("RES 0, L\n");

	dprintf("value of register L before is : 0b%8b\n",cpu.L);

	cpu.L &= 0b11111110;

	dprintf("value of register L after is : 0b%8b\n",cpu.L);
}

void opcd_res_0_hl(){
	// RES 0, (HL)
	// Sets the 0th bit to 0 of Register D
	
	dprintf("RES 0,(HL)\n");
		
	u8 = memory_read(getHL());
	dprintf("value of register D before is : 0b%8b\n",u8);

	u8 &= 0b11111110;
	memory_write(getHL(),u8);

	dprintf("value of register D after is : 0b%8b\n",u8);
}

void opcd_res_0_a(){
	// RES 0, A
	// Sets the 0th bit to 0 of Register A
	
	dprintf("RES 0, A\n");

	dprintf("value of register A before is : 0b%8b\n",cpu.A);

	cpu.A &= 0b11111110;

	dprintf("value of register A after is : 0b%8b\n",cpu.A);
}

void opcd_res_1_b(){
	// RES 1, B
	// Sets the 0th bit to 0 of Register B
	
	dprintf("RES 1, B\n");

	dprintf("value of register B before is : 0b%8b\n",cpu.B);

	cpu.B &= 0b11111101;

	dprintf("value of register B after is : 0b%8b\n",cpu.B);
}

void opcd_res_1_c(){
	// RES 1, C
	// Sets the 0th bit to 0 of Register C
	
	dprintf("RES 1, C\n");

	dprintf("value of register C before is : 0b%8b\n",cpu.C);

	cpu.C &= 0b11111101;

	dprintf("value of register C after is : 0b%8b\n",cpu.C);
}

void opcd_res_1_d(){
	// RES 1, D
	// Sets the 0th bit to 0 of Register D
	
	dprintf("RES 1, D\n");

	dprintf("value of register D before is : 0b%8b\n",cpu.D);

	cpu.D &= 0b11111101;

	dprintf("value of register D after is : 0b%8b\n",cpu.D);
}

void opcd_res_1_e(){
	// RES 1, E
	// Sets the 0th bit to 0 of Register E
	
	dprintf("RES 1, E\n");

	dprintf("value of register E before is : 0b%8b\n",cpu.E);

	cpu.E &= 0b11111101;

	dprintf("value of register E after is : 0b%8b\n",cpu.E);
}

void opcd_res_1_h(){
	// RES 1, H
	// Sets the 0th bit to 0 of Register H
	
	dprintf("RES 1, H\n");

	dprintf("value of register H before is : 0b%8b\n",cpu.H);

	cpu.H &= 0b11111101;

	dprintf("value of register H after is : 0b%8b\n",cpu.H);
}

void opcd_res_1_l(){
	// RES 1, L
	// Sets the 0th bit to 0 of Register L
	
	dprintf("RES 1, L\n");

	dprintf("value of register L before is : 0b%8b\n",cpu.L);

	cpu.L &= 0b11111101;

	dprintf("value of register L after is : 0b%8b\n",cpu.L);
}

void opcd_res_1_a(){
	// RES 1, A
	// Sets the 0th bit to 0 of Register A
	
	dprintf("RES 1, A\n");

	dprintf("value of register A before is : 0b%8b\n",cpu.A);

	cpu.A &= 0b11111101;

	dprintf("value of register A after is : 0b%8b\n",cpu.A);
}

void opcd_res_1_hl(){
	// RES 1, (HL)
	// Sets the 0th bit to 0 of Register D
	
	dprintf("RES 1,(HL)\n");
		
	u8 = memory_read(getHL());
	dprintf("value of register D before is : 0b%8b\n",u8);

	u8 &= 0b11111101;
	memory_write(getHL(),u8);

	dprintf("value of register D after is : 0b%8b\n",u8);
}

void res_bit(uint8_t *reg, uint8_t bit) {
    *reg &= ~(1 << bit);
}

void set_bit(uint8_t *reg, uint8_t bit) {
    *reg |= (1 << bit);
}

void set_bit_hl(uint8_t bit) {
    u8 = memory_read(getHL());
    u8 |= (1 << bit);
    memory_write(getHL(), u8);
}

#include "debug.h"
#include "cpu.h"
#include "flags.h"
#include "memory.h"
#include "registers.h"

// ├── cpu_jump.c         // JP, JR, CALL, RET, RST


void opcd_ret(){
	// RET
	// lenght is 1 byte
	// POP the stack and put it into the PC

	dprintf("RET\n");
	dprintf("SP before: 0x%04x\n",cpu.SP);

	lsb = pop(); // P of the PC
	msb = pop();  // C of the PC

	u16 = (msb << 8) | lsb;

	cpu.PC = u16 - 1;

	dprintf("Value of register PC : 0x%04x\n",cpu.PC + 1);
	dprintf("SP after: 0x%04x\n",cpu.SP);

}

void opcd_ret_nc(){
	// RET NC
	// lenght is 1 byte
	// POP the stack and put it into the PC if C flag is 0

	dprintf("RET NC\n");

	if(getC() == 0){
		dprintf("SP before: 0x%04x\n",cpu.SP);

		lsb = pop(); // P of the PC
		msb = pop();  // C of the PC

		u16 = (msb << 8) | lsb;

		cpu.PC = u16 - 1;

		dprintf("Value of register PC : 0x%04x\n",cpu.PC + 1);
		dprintf("SP after: 0x%04x\n",cpu.SP);
	}
	else
		dprintf("C is 1 , not returning\n");

}

void opcd_ret_nz(){
	// RET NZ
	// lenght is 1 byte
	// POP the stack and put it into the PC if Z flag is 0

	dprintf("RET NZ\n");

	if(getz() == 0){
		dprintf("SP before: 0x%04x\n",cpu.SP);

		lsb = pop(); // P of the PC
		msb = pop();  // C of the PC

		u16 = (msb << 8) | lsb;

		cpu.PC = u16 - 1;

		dprintf("Value of register PC : 0x%04x\n",cpu.PC + 1);
		dprintf("SP after: 0x%04x\n",cpu.SP);
	}
	else
		dprintf("Z is 1 , not returning\n");

}

void opcd_ret_c(){
	// RET C
	// lenght is 1 byte
	// POP the stack and put it into the PC if C flag is 1

	dprintf("RET C\n");

	if(getC() == 1){
		dprintf("SP before: 0x%04x\n",cpu.SP);

		lsb = pop(); // P of the PC
		msb = pop();  // C of the PC

		u16 = (msb << 8) | lsb;

		cpu.PC = u16 - 1;

		dprintf("Value of register PC : 0x%04x\n",cpu.PC + 1);
		dprintf("SP after: 0x%04x\n",cpu.SP);
	}
	else
		dprintf("C is 0 , not returning\n");

}

void opcd_ret_z(){
	// RET Z
	// lenght is 1 byte
	// POP the stack and put it into the PC if Z flag is 1

	dprintf("RET Z\n");

	if(getz() == 1){
		dprintf("SP before: 0x%04x\n",cpu.SP);

		lsb = pop(); // P of the PC
		msb = pop();  // C of the PC

		u16 = (msb << 8) | lsb;

		cpu.PC = u16 - 1;

		dprintf("Value of register PC : 0x%04x\n",cpu.PC + 1);
		dprintf("SP after: 0x%04x\n",cpu.SP);
	}
	else
		dprintf("z is 0 , not returning\n");

}

void opcd_jp_hl(){
	// JP HL
	// JUMP to addr in HL
	// lenght is 3 bytes

	dprintf("JP HL\n");
	HL = getHL();

	dprintf("Value of register HL is : 0x%04x\n",HL);

	cpu.PC = HL - 1;
}

void opcd_jp_u16(){
	// JP u16
	// JUMP to addr u16
	// lenght is 3 bytes

	dprintf("JP u16\n");
	u16 = get_u16();

	dprintf("JP (0x%04x)\n",u16);

	cpu.PC = u16 - 1;
}

void opcd_call_nz_u16(){
	// CALL NZ , u16
	// lenght is 3 bytes

	dprintf("CALL NZ, u16\n");
	u16 = get_u16();
	dprintf("Z flag: 0b%b\n",getz());

	if(getz() == 0){
		//store the current addr to the stack
		lsb = (cpu.PC + 1) & 0x00ff;
		msb = ((cpu.PC + 1) & 0xff00) >> 8;

		dprintf("Storing 0x%04x first\n",msb);
		push(msb);
		dprintf("Storing 0x%04x next\n",lsb);
		push(lsb);

		cpu.PC = u16 - 1; // +1 will be done at the end

		dprintf("CALL and Jumping to 0x%04x\n",u16);
	}


}

void opcd_call_nc_u16(){
	// CALL NC , u16
	// lenght is 3 bytes

	dprintf("CALL NC, u16\n");
	u16 = get_u16();
	printf("C flag: 0b%b\n",getC());

	if(getC() == 0){
		//store the current addr to the stack
		lsb = (cpu.PC+1) & 0x00ff;
		msb = ((cpu.PC+1) & 0xff00) >> 8;

		dprintf("Storing 0x%04x first\n",msb);
		push(msb);
		dprintf("Storing 0x%04x next\n",lsb);
		push(lsb);

		cpu.PC = u16 - 1; // +1 will be done at the end

		dprintf("CALL and Jumping to 0x%04x\n",u16);
	}


}

void opcd_call_u16(){
	// CALL u16
	// lenght is 3 bytes

	dprintf("CALL u16\n");
	u16 = get_u16();

	//store the current addr to the stack
	lsb = (cpu.PC + 1) & 0x00ff;
	msb = ((cpu.PC + 1) & 0xff00) >> 8;

	dprintf("Storing 0x%04x first\n",msb);
	push(msb);
	dprintf("Storing 0x%04x next\n",lsb);
	push(lsb);

	cpu.PC = u16 - 1; // +1 will be done at the end

	dprintf("CALL and Jumping to 0x%04x\n",u16);

}

void opcd_jr_u8(){
	// JR u8
	// JUMP Relative to (current addr + u8)
	// lenght is 2 bytes

	dprintf("JR u8\n");
	signed_offset = memory_read(++cpu.PC);
	dprintf("Add by(u8) : 0x%2x (0d%d) \n",signed_offset,signed_offset);

	dprintf("Address is: 0x%04x\n",(cpu.PC + 1) + signed_offset);
	dprintf("JR (0x%04x)\n",(cpu.PC + 1) + signed_offset);

	cpu.PC = (cpu.PC + 1) +  signed_offset - 1; //as a +1 will happen after the end of switch case
	dprintf("Jumping to 0x%04x\n",cpu.PC + 1);

}

void opcd_jr_nz_u8(){
	// JUMP if NotZero to addr
	// lenght is 2 bytes
	// if Z flag is 0:
	// jump relative to (current_addr + addr)

	dprintf("JR NZ, u8\n");

	signed_offset = memory_read(++cpu.PC);

	dprintf("Add by(u8) : 0x%2x (0d%d) \n",signed_offset,signed_offset);

	//signed_offset += cpu.PC + 1; // address is calculated after the instruction hence
			   // the +1
	dprintf("Address is: 0x%04x\n",(cpu.PC + 1) + signed_offset);
	dprintf("JR NZ , (0x%04x)\n",(cpu.PC + 1) + signed_offset);
	dprintf("Z : 0b%b\n",getz());

	if(getz() == 0){
		cpu.PC = (cpu.PC + 1) +  signed_offset - 1; //as a +1 will happen after the end of switch case
		dprintf("Jumping to 0x%04x\n",cpu.PC + 1);
	}
	else{
		dprintf("Not Jumping\n");
	}

	//sleep(2);
}

void opcd_jr_z_u8(){
	// JR Z, u8
	// JUMP relative if Zero flag is 1 to (current addr + n)
	// lenght is 2 bytes

	dprintf("JR Z, u8\n");
	signed_offset = memory_read(++cpu.PC);

	dprintf("Add by (u8) : 0x%02x (0d%d) \n",signed_offset,signed_offset);

	//signed_offset += cpu.PC + 1; // address is calculated after the instruction hence
			   // the +1
	dprintf("Address is: 0x%04x\n",(cpu.PC + 1) + signed_offset);
	dprintf("JR Z , (0x%04x)\n",(cpu.PC + 1) + signed_offset);
	dprintf("Z : 0b%b\n",getz());

	if(getz() == 1){
		cpu.PC = (cpu.PC + 1) +  signed_offset - 1; //as a +1 will happen after the end of switch case
		dprintf("Jumping to 0x%04x\n",cpu.PC + 1);
	}
	else{
		dprintf("Not Jumping\n");
	}

}

void opcd_jr_nc_u8(){
	// JR NC, u8
	// JUMP relative if NotC to (current addr + n)
	// lenght is 2 bytes
	dprintf("JR NC, u8\n");

	signed_offset = memory_read(++cpu.PC);

	dprintf("Add by(u8) : 0x%2x (0d%d) \n",signed_offset,signed_offset);

	//signed_offset += cpu.PC + 1; // address is calculated after the instruction hence
			   // the +1
	dprintf("Address is: 0x%04x\n",(cpu.PC + 1) + signed_offset);
	dprintf("JR NC , (0x%04x)\n",(cpu.PC + 1) + signed_offset);
	dprintf("C : 0b%b\n",getC());

	if(getC() == 0){
		cpu.PC = (cpu.PC + 1) +  signed_offset - 1; //as a +1 will happen after the end of switch case
		dprintf("Jumping to 0x%04x\n",cpu.PC + 1);
	}
	else{
		dprintf("Not Jumping\n");
	}


}

void opcd_jr_c_u8(){
	// JR C, u8
	// JUMP relative if C , to (current addr + n)
	// lenght is 2 bytes

	addr = memory_read(++cpu.PC);
	dprintf("Add by: 0x%2x\n",addr);
	dprintf("Add by: %d\n",addr);

	addr += cpu.PC + 1; // address is calculated after the instruction hence
		     // the +1
	dprintf("Address is: 0x%04x\n",addr);

	printf("JR C, (0x%04x)\n",addr);

}

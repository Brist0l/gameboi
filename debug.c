#include<stdbool.h>
#include<stdio.h>

#include "memory.h"
#include "debug.h"
#include "cpu.h"


void logmsg(const char* function_name,bool start){
	if(debug_flag){
		if(start){
			dprintf(ANSI_COLOR_RED);
			dprintf("\n=====function %s START=====\n",function_name);
			dprintf(ANSI_COLOR_RESET);
		}
		else{
			dprintf(ANSI_COLOR_RED);
			printf("=====function %s END=====\n",function_name);
			dprintf(ANSI_COLOR_RESET);
		}
	}
}

// View the memory locations from a starting address to an ending address
void _memoryframe(short start,short end){
	logmsg("_memoryframe",true);

	if(debug_flag)
		for(short i = start; i <= end;i++)
				printf("val is: 0x%02x at 0x%04x\n",(int) memory[i],(int) i);

	logmsg("_memoryframe",false);
}

// View the memory locations from a starting address to an ending address
void _memorydump(int start,int end){
	logmsg("_memorydump",true);

	if(debug_flag){
		for(int i = start; i <= end;i++){
			if(i % 16 == 0)
				printf("\n%04x => ",i);
			printf("%02x ",memory[i]);
		}
		printf("\n");
	}

	logmsg("_memorydump",false);
}

void _stackdump(){
	logmsg("_stackdump",true);

	if(debug_flag){
		for(int i = 0xdf63; i <= 0xdff0 ;i++){
			if(i % 16 == 0)
				printf("\n%04x => ",i);
			printf("%02x ",memory[i]);
		}
		printf("\n");
	}

	logmsg("_stackdump",false);
}

void registerdump(){
	logmsg("registerdump",true);

	if(debug_flag){
		printf("Register A: 0x%02x\n",cpu.A);
		printf("Register B: 0x%02x\n",cpu.B);
		printf("Register C: 0x%02x\n",cpu.C);
		printf("Register D: 0x%02x\n",cpu.D);
		printf("Register E: 0x%02x\n",cpu.E);
		printf("Register H: 0x%02x\n",cpu.H);
		printf("Register L: 0x%02x\n",cpu.L);
		printf("Register SP: 0x%04x\n",cpu.SP);
		printf("Register PC: 0x%04x\n",cpu.PC);
		printf("Register F: 0x%02x\n",cpu.F);
	}

	logmsg("registerdump",false);

}

void _fillopcode(){
	// Filling it with a const opcode , 00EE => basically it's C's `return`
	// So all the opcodes are 2 bytes long and it's stored in big-endian format
	memory[0x200] = 0x60;
	memory[0x201] = 0x05;
	memory[0x202] = 0x61;
	memory[0x203] = 0x05;
	memory[0x204] = 0xF1;
	memory[0x205] = 0x29;
	memory[0x206] = 0xD0;
	memory[0x207] = 0x15;
}

void _fillregisters(){
 	cpu.A= 0x01;
	cpu.B= 0x00;
	cpu.C= 0x13;
	cpu.D= 0x00;
	cpu.E= 0xd8;
	cpu.H= 0x01;
	cpu.L= 0x4d;
	cpu.SP= 0xfffe;
	cpu.PC= 0x0100;
	cpu.F= 0xB0;
}

void gb_doc_log(){
	printf(
"A:%02X F:%02X B:%02X C:%02X D:%02X E:%02X H:%02X L:%02X SP:%04X PC:%04X PCMEM:%02X,%02X,%02X,%02X\n"
		,cpu.A
		,cpu.F
		,cpu.B
		,cpu.C
		,cpu.D
		,cpu.E
		,cpu.H
		,cpu.L
		,cpu.SP
		,cpu.PC
		,memory_read(cpu.PC)
		,memory_read(cpu.PC+1)
		,memory_read(cpu.PC+2)
		,memory_read(cpu.PC+3)
		);
}

void other_log(){
	printf(
"A: %02X F: %02X B: %02X C: %02X D: %02X E: %02X H: %02X L: %02X SP: %04X PC: 00:%04X (%02X %02X %02X %02X)\n"
		,cpu.A
		,cpu.F
		,cpu.B
		,cpu.C
		,cpu.D
		,cpu.E
		,cpu.H
		,cpu.L
		,cpu.SP
		,cpu.PC
		,memory_read(cpu.PC)
		,memory_read(cpu.PC+1)
		,memory_read(cpu.PC+2)
		,memory_read(cpu.PC+3)
		);
}

void serial_io(char s){
	FILE* f = fopen("logs/serial/serialio2","a");
	fputc(s,f);
	fclose(f);
}

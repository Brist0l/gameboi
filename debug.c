#include<stdbool.h>
#include<stdio.h>

#include "memory.h"
#include "debug.h"


void logmsg(const char* function_name,bool start){

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

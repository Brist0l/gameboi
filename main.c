#include<stdio.h>
#include<stdbool.h>

#include"cpu.h"
#include"memory.h"
#include"rom_disass.h"
#include"debug.h"


bool debug_flag = true;

int main(){
	printf("STARTING\n");

	cpu.PC = 0x100;  // Reference: GB CPU manual (3.2.3 , pg 63)

	//stack grows downwards
	cpu.SP = 0xfffe; // Reference: GB CPU manual (3.2.4 , pg 64)


	read();

	_memoryframe(0x0,0x100);
}

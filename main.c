#include<stdio.h>
#include<stdbool.h>

#include"cpu.h"
#include"memory.h"
#include"rom.h"
#include"debug.h"


bool debug_flag = true;

int main(){
	printf("STARTING\n");

	//cpu.PC = 0x100;  // Reference: GB CPU manual (3.2.3 , pg 63)

	//stack grows downwards
	cpu.SP = 0xfffe; // Reference: GB CPU manual (3.2.4 , pg 64)

	int size = getsize("dmg_boot.bin");
	dprintf("dmg_boot ROM size: %d\n",size);
	load_rom("dmg_boot.bin",size,0);

	//_memoryframe(0x0,0x100); // from 0 to 256 bytes

	while(cpu.PC != 0x32)
		execute(size);
}

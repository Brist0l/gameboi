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
	int size1 = getsize("gb-test-roms/cpu_instrs/cpu_instrs.gb");

	//dprintf("dmg_boot ROM size: %d\n",size);

	//load_rom("dmg_boot.bin",size,0);
	//load_rom("gb-test-roms/cpu_instrs/cpu_instrs.gb",size1,0x100);
	load_rom("gb-test-roms/cpu_instrs/cpu_instrs.gb",size1,0x0);
	load_rom("dmg_boot.bin",size,0); // The ROM overwrites the cartriges from 0x0 to 0xfe
					 // and then performs checks like logo is same or not

	memory[0xff44] = 0x90; //  Just to pass the infinite loop

	//_memoryframe(0x0,0x100); // from 0 to 256 bytes
	int cnt = 0xffff;

	while(cpu.PC <= 0x00fe)
	//while(cnt-- != 0)
		execute();

	//_memorydump(0x0000,0x0f00);
	//_memorydump(0x8000,0x8080);
	//_memorydump(0xff20,0xffff);

}

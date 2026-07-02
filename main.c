#include<stdio.h>
#include<stdbool.h>

#include"cpu.h"
#include"memory.h"
#include"rom.h"
#include"debug.h"

bool debug_flag = false;
bool boot_rom_enable = false;
bool gb_doc = true;

int main(){
	if(gb_doc != true)
		printf("STARTING\n");

	cpu.PC = 0x100;  // Reference: GB CPU manual (3.2.3 , pg 63)

	//stack grows downwards
	cpu.SP = 0xfffe; // Reference: GB CPU manual (3.2.4 , pg 64)

	int size = getsize("dmg_boot.bin");
	int size1 = getsize("gb-test-roms/cpu_instrs/individual/10-bit\ ops.gb");

	//dprintf("dmg_boot ROM size: %d\n",size);

	load_rom("gb-test-roms/cpu_instrs/individual/10-bit\ ops.gb",size1,0x0);
	if(boot_rom_enable == true)
		load_rom("dmg_boot.bin",size,0x0);
	//load_rom("gb-test-roms/cpu_instrs/cpu_instrs.gb",size1,0x100);
	//load_rom("dmg_boot.bin",size,0); // The ROM overwrites the cartriges from 0x0 to 0xfe
					 // and then performs checks like logo is same or not

	memory[0xff44] = 0x90; //  Just to pass the infinite loop

	//_memoryframe(0x0,0x100); // from 0 to 256 bytes
	int cnt = 0xffffff;

	_fillregisters();
	_memorydump(0x0000,0x01ff);
	//while(1){
	//while(cpu.PC != 0x100){
	while(cnt-- != 0){
		//if(cnt % 1000 == 0)
		 	//printf("0x%04x\n", cpu.PC);
		execute();
	}

	registerdump();

	_memorydump(0x0630,0x0700);
	_memorydump(0x8000,0x9fff);
	_memorydump(0xff00,0xffff);
}

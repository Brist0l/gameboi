#include<stdio.h>
#include<stdbool.h>

#include"cpu.h"
#include"memory.h"
#include"rom.h"
#include"debug.h"
#include"ppu.h"

bool debug_flag = true;
bool boot_rom_enable = false;
bool gb_doc = true;

struct Game* g = NULL;

int key;
unsigned int t_cycles;

int main(int argc,char* argv[]){
	if(argc < 2){
		printf("Enter the ROM file bruv\n");
		return -1;
	}

	if(gb_doc != true)
		printf("STARTING\n");

	cpu.PC = 0x100;  // Reference: GB CPU manual (3.2.3 , pg 63)

	//stack grows downwards
	cpu.SP = 0xfffe; // Reference: GB CPU manual (3.2.4 , pg 64)

	int size = getsize("dmg_boot.bin");
	int size1 = getsize(argv[1]);

	//dprintf("dmg_boot ROM size: %d\n",size);

	load_rom(argv[1],size1,0x0);

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

	if(game_new(&g)){

		//Uint32 last = SDL_GetTicks();
		dprintf("Game: %p\n",g);

		while(g->is_running){
			game_events(g,&key);
			//dprintf("Running Game, 0x%x is pressed\n",);

		//	clear_screen(g);
			t_cycles = execute();
			dprintf("T Cycles: %d\n",t_cycles);

			//Uint32 now = SDL_GetTicks();
			//if((now - last) >= 1000/60){
				//timers
			//}

			render_screen(g);
			//SDL_Delay(1000); // i.e. 60Hz
		}
	}

	game_free(&g);

	registerdump();

	//_memorydump(0x0630,0x0700);
	//_memorydump(0x8000,0x9fff);
	//_memorydump(0xff00,0xffff);
}

#include "ppu.h"
#include "debug.h"
#include "display.h"
#include "cpu.h"
#include "rom.h"
#include "memory.h"
#include "registers_ppu.h"

struct Game* g = NULL;
bool debug_flag = true;
bool gb_doc = true;


int main(int argc,char* argv[]){
	int key;

	if(argc < 2){
		printf("Give some ROM bruv\n");
		return -1;
	}

	cpu.PC = 0x100;  // Reference: GB CPU manual (3.2.3 , pg 63)

	//stack grows downwards
	cpu.SP = 0xfffe; // Reference: GB CPU manual (3.2.4 , pg 64)

	int size = getsize("assets/dmg_boot.bin");
	int size1 = getsize(argv[1]);

	load_rom(argv[1],size1,0x0);

	load_rom("assets/dmg_boot.bin",size,0x0);

	memory[0xff44] = 0x90; //  Just to pass the infinite loop

	int cnt = 0xffff;

	//_fillregisters();

	bool runned = false;
	//game_new(&g);

	while(runned == false || g->is_running){
		game_events(g,&key);
		execute();
		if(LCDC_lcd_ppu_enable_bit_7() && runned == false){
			game_new(&g);
			runned = true;
		}

		if(cnt-- <= 0){
			draw(g);
			render_screen(g);
		}
	}

	//_vramdump();
	_memorydump(0x9800,0x9c00);
	//show_background();

	game_free(&g);
}

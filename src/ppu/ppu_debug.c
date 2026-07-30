#include "ppu.h"
#include "debug.h"
#include "display.h"
#include "cpu.h"
#include "cpu_interrupts.h"
#include "rom.h"
#include "memory.h"
#include "registers_ppu.h"
#include "background_debug.h"

#include<stdlib.h>

struct Game* g = NULL;

bool debug_flag = true;
bool gb_doc = false;
bool background_debug = false;

unsigned int t_cycle = 0;

int main(int argc,char* argv[]){
	int key;

	if(argc < 2){
		printf("Give some ROM bruv\n");
		return -1;
	}

	cpu.PC = 0x000;  // Reference: GB CPU manual (3.2.3 , pg 63)

	//stack grows downwards
	cpu.SP = 0xfffe; // Reference: GB CPU manual (3.2.4 , pg 64)

	int size = getsize("assets/dmg_boot.bin");
	int size1 = getsize(argv[1]);

	load_rom(argv[1],size1,0x0);

	load_rom("assets/dmg_boot.bin",size,0x0);

	memory[0xff44] = 0x90; //  Just to pass the infinite loop

	int cnt = 20;

	//_fillregisters();

	bool runned = false;
	int c = 0;
	//game_new(&g);

	while(runned == false || g->is_running){
		game_events(g,&key);
		
		dprintf("============Executing========\n");
		printf("EXEC\n");
		t_cycle = execute();
		dprintf("T Cycles: %d\n",t_cycle);
	

		if(LCDC_lcd_ppu_enable_bit_7() && runned == false){
			if(background_debug) {
				dprintf("Making background window\n");
				game_new(&g,"background debug",255,255,BACKGROUND_SCALE);
			}
			else{
				dprintf("Making game window\n");
				game_new(&g,WINDOW_TITLE,WINDOW_WIDTH,WINDOW_HEIGHT,SCALE);

			}
			runned = true;
		}

		//if(cnt-- <= 0 && g != NULL){
		if(g != NULL && c == 100){
			if(background_debug){
				printf("DRAW\n");
				set_debug_background();
				printf("RENDER\n");
				debug_render_screen(g);
			}
			else{
				printf("DRAW\n");
				draw(g);
				printf("RENDER\n");
				render_screen(g);
			}
			c = 0;
			cnt = 20;
		//}
		}

		if(g != NULL)
			c++;
		
		LCDC_show();
		showLY();
		check_interrupts();
		printf("DONE\n");
	}

	//_vramdump();
	_memorydump(0x9800,0x9c00);
	//show_background();

	game_free(&g);
}

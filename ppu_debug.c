#include "ppu.h"
#include "debug.h"
#include "display.h"
#include "cpu.h"
#include "rom.h"
#include "memory.h"

struct Game* g = NULL;
bool debug_flag = true;
bool gb_doc = true;


int main(int argc,char* argv[]){
	if(argc < 2){
		printf("Give some ROM bruv\n");
		return -1;
	}

	cpu.PC = 0x100;  // Reference: GB CPU manual (3.2.3 , pg 63)

	//stack grows downwards
	cpu.SP = 0xfffe; // Reference: GB CPU manual (3.2.4 , pg 64)

	int size = getsize("dmg_boot.bin");
	int size1 = getsize(argv[1]);

	load_rom(argv[1],size1,0x0);

	load_rom("dmg_boot.bin",size,0x0);

	memory[0xff44] = 0x90; //  Just to pass the infinite loop

	int cnt = 0xffff;

	_fillregisters();

	game_new(&g);

	while(cnt-- != 0){
		game_events(g,NULL);
		draw(g);
		render_screen(g);
	}

	_vramdump();

	game_free(&g);
}

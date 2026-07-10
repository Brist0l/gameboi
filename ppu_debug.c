#include "ppu.h"
#include "debug.h"
#include "display.h"

struct Game* g = NULL;
bool debug_flag = true;

int main(){
	game_new(&g);

	draw(g);

	while(g->is_running){
		game_events(g,NULL);
		render_screen(g);
	}


	game_free(&g);
}

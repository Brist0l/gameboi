#include "display.h"
#include "debug.h"
#include "ppu.h"
#include "memory.h"
#include "tile.h"
#include "ppu.h"
#include "debug.h"
#include "display.h"
#include "memory.h"
#include "background.h"

static uint16_t background_mem = 0x9800;
static uint16_t background_mem_end;
uint8_t debug_background[256][256] = {0};

void show_background_tiles(){
	uint8_t data[16];
	int background_y = 0;
	int background_x = 0;
	static uint16_t start_addr = 0x8000;

	// Sets background memory as well now it sets the
	// background_mem_end
	background_mem_end = 0x97ff;

	while(background_mem_end > start_addr){
		for(int i = 0; i < 16; i++){
			dprintf("start addr : %d\n",start_addr);
			start_addr += i;
			data[i] = memory_read(start_addr);
		}

		make_tile(data); // form the data into a tile


		// Set the background as the tile
		for(int y = 0; y < 8;y++){
			for(int x = 0; x < 8;x++){
				debug_background[background_y + y][background_x + x] = tile[y][x];
				//dprintf("d_y : %d\nd_x: %d\n",d_y,d_x);
			}

		}

		background_x += 8;

		if(background_x == 256){
			dprintf("Setting background_x to 0!!!\n");
			background_x = 0;
			background_y += 8;

		}


		if(background_y >= 256){
			dprintf("Setting background_y to 0!!!\n");
			background_y = 0;
		}

	}

}

void set_debug_background(){
	uint8_t data[16];
	int background_y = 0;
	int background_x = 0;
	uint16_t start_addr;

	// Sets background memory as well now it sets the
	// background_mem_end
	background_mem_end = select_background();

	while(0x97ff > start_addr){
		// Assume that you have a tile number 0.
		// So that means that it would start at
		// 0x8000 and then it would read 16 bytes
		// from there , i.e. till 0x800f
		//
		// So address can be calculated like
		//
		// start_addr = 0x8000 + 16 * (tile_num)


		start_addr = 0x8000;
		background_mem = 0xf;

		for(int i = 0; i < 16; i++)
			data[i] = memory_read(start_addr);

		start_addr += background_mem;

		make_tile(data); // form the data into a tile

		// Set the background as the tile
		for(int y = 0; y < 8;y++){
			for(int x = 0; x < 8;x++){
				debug_background[background_y + y][background_x + x] = tile[y][x];
				//dprintf("d_y : %d\nd_x: %d\n",d_y,d_x);
			}

		}

		background_x += 8;

		if(background_x == 256){
			dprintf("Setting background_x to 0!!!\n");
			background_x = 0;
			background_y += 8;

		}


		if(background_y >= 256){
			dprintf("Setting background_y to 0!!!\n");
			background_y = 0;
		}

	}

}

SDL_Color _dmg_palette[4] = {
    {155, 188, 15, 255},
    {48, 98, 48, 255},
    {139, 172, 15, 255},
    {15, 56, 15, 255}
};

void debug_render_screen(struct Game *g){
    	SDL_SetRenderDrawColor(g->renderer, _dmg_palette[3].r, _dmg_palette[3].g,_dmg_palette[3].b,_dmg_palette[3].a);
    	SDL_RenderClear(g->renderer);

  	for(int y = 0; y < 256; y++) {
        	for(int x = 0; x < 256; x++) {
			
			SDL_Color c = _dmg_palette[debug_background[y][x] & 0b11];

			//if(debug_background[y][x] != 0)
				//dprintf("Display colour : %d\nPainting colour : %d\n",debug_background[y][x],debug_background[y][x] & 0b11);
			SDL_SetRenderDrawColor(g->renderer,c.r,c.g,c.b,c.a);

                	SDL_FRect rect = {x * BACKGROUND_SCALE * 2, y * BACKGROUND_SCALE *2, BACKGROUND_SCALE * 2, BACKGROUND_SCALE * 2};
                	SDL_RenderFillRect(g->renderer, &rect);
        	}
    	}

    	SDL_RenderPresent(g->renderer); // update the rendering content
}

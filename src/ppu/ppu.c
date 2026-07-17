#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>
#include<stdbool.h>
#include<stdlib.h>

#include "display.h"
#include "debug.h"
#include "memory.h"
#include "registers_ppu.h"
#include "background.h"

#define STD_LSB 0b00000001
#define STD_MSB 0b00000010

uint8_t display[WINDOW_HEIGHT][WINDOW_WIDTH] = {0};
uint8_t background[256][256] = {0};
uint8_t window[256][256] = {0};

uint8_t tile[8][8] = {0};

static int mem = 0x9800;
static uint16_t window_mem = 0x9800;
static uint16_t window_mem_end;
static uint8_t tile_num;

bool draw(struct Game *g){
	// This will handle "which" pixels need to light up.
	// Rn this just will set display to 0 or non 0 , and then according to that render it

	// The first two bytes is the first row and so on and so forth.
	// 0xFF => 1 1 1 1 1 1 1 1 -> Least significant byte of colour
	// 								=> 01 01 01 01 01 01 01 01
	// 0x00 => 0 0 0 0 0 0 0 0 -> Most significant byte  of colour

	uint8_t test_data[] = {
		    0x3C, 0x7E,
		    0x42, 0x42,
		    0x42, 0x42,
		    0x42, 0x42,
		    0x7E, 0x5E,
		    0x7E, 0x0A,
		    0x7C, 0x56,
		    0x38, 0x7C
		};



	//for(int i = 0; i < 16; i++)
		//test_data[i] = memory_read(background_mem + i);

	//if(background_mem >= select_background());
		//background_mem = 0x9c00;

	//background_mem += 16;

	set_background();

	//make_tile(test_data);

	//show_tile(tile);
}

SDL_Color dmg_palette[4] = {
    {155, 188, 15, 255},
    {139, 172, 15, 255},
    {48, 98, 48, 255},
    {15, 56, 15, 255}
};

bool clear_screen(struct Game *g){
	memset(display, 0, sizeof(display));

    	SDL_SetRenderDrawColor(g->renderer, 0, 0, 0, 255);
    	SDL_RenderClear(g->renderer);
    	SDL_RenderPresent(g->renderer);
    	return true;
}

void render_screen(struct Game *g){

    	SDL_SetRenderDrawColor(g->renderer, dmg_palette[3].r, dmg_palette[3].g,dmg_palette[3].b,dmg_palette[3].a); // Black colour
    	SDL_RenderClear(g->renderer);


  	for(int y = 0; y < WINDOW_HEIGHT; y++) {
        	for(int x = 0; x < WINDOW_WIDTH; x++) {
			uint8_t color = display[y][x] & 0x03;

			SDL_Color c = dmg_palette[3 - color]; // if you want 0 = darkest, 3 = lightest

			SDL_SetRenderDrawColor(g->renderer,c.r,c.g,c.b,c.a);

                	SDL_FRect rect = {x * SCALE, y * SCALE, SCALE, SCALE};
                	SDL_RenderFillRect(g->renderer, &rect);
        	}
    	}

    	SDL_RenderPresent(g->renderer); // update the rendering content
}

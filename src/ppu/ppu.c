#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>
#include<stdbool.h>

#include "display.h"
#include "debug.h"
#include "memory.h"
#include "registers_ppu.h"

#define STD_LSB 0b00000001
#define STD_MSB 0b00000010

uint8_t display[WINDOW_HEIGHT][WINDOW_WIDTH] = {0};
uint8_t background[256][256] = {0};
uint8_t window[256][256] = {0};

uint8_t tile[8][8] = {0};

static int d_x = 0;
static int d_y = 0;
static int mem = 0x9800;
static uint16_t background_mem = 0x9800;
static uint16_t window_mem = 0x9800;
static uint16_t window_mem_end;
static uint16_t background_mem_end;

void make_tile(uint8_t test_data[]){
	int t_x = 0; // Goes Right
	int t_y = 0; // Goes Down
	uint8_t lsbs;
	uint8_t msbs;

	for(int data = 0;data < 16;data += 2){
		lsbs = test_data[data];
		msbs = test_data[data + 1];

		dprintf("Working on Row number: %d\n",data - 1);
		dprintf("Working with the LSB bytes: 0b%08b (0x%02x)\n",lsbs,lsbs);
		dprintf("Working with the MSB bytes: 0b%08b (0x%02x)\n",msbs,msbs);
		dprintf("\n");

		for(int bit = 7;bit >= 0;bit--){
			uint8_t the_lsb = (lsbs >> bit) & STD_LSB;
			uint8_t the_msb = (msbs >> (bit-1)) & STD_MSB;

			dprintf("Standard form of LSB: 0b%08b (0x%02x)\n",the_lsb,the_lsb);
			dprintf("Standard form of MSB: 0b%08b (0x%02x)\n",the_msb,the_msb);

			uint8_t pixel = the_lsb | the_msb;

			dprintf("Pixel: 0b%02b (0x%02x)\n",pixel,pixel);
			dprintf("\n");

			tile[t_y][t_x++] = pixel;
		}
		t_y++;
		t_x = 0;
	}
}



uint16_t select_background(){
	// This will select the background map depending
	// on the LCDC bit
	//
	// Returns the ending address of the background.

	if(LCDC_lcd_window_tile_map_select_6() == 0){
		background_mem = 0x9800;
		return 0x9bff;
	}
	else{
		background_mem = 0x9c00;
		return 0x9fff;
	}
}

void set_background(){
	uint8_t data[16];

	background_mem_end = select_background();

	while(background_mem >= background_mem_end){
		for(int i = 0; i < 16; i++)
			data[i] = memory_read(background_mem + i);

		make_tile(data);

		for(int y = 0; y < 8;y++){
			for(int x = 0; x < 8;x++){
				background[y][x] = tile[y][x];
				dprintf("d_y : %d\nd_x: %d\n",d_y,d_x);
			}
		}

		background_mem += 16;
	}
}

void show_tile(uint8_t tile[8][8]){
	for(int y = 0; y < 8;y++){
		for(int x = 0; x < 8;x++){
			dprintf("%02b ",tile[y][x]);
		}
		dprintf("\n");
	}

	for(int y = 0; y < 8;y++){
		for(int x = 0; x < 8;x++){
			display[d_y + y][d_x + x] = tile[y][x];
			dprintf("d_y : %d\nd_x: %d\n",d_y,d_x);
		}
	}

	if(d_x + 8>= WINDOW_WIDTH)
		d_x = 0;
	else
		d_x += 8;

	if(d_y + 8 >= WINDOW_HEIGHT)
		d_y = 0;
	else
		d_y += 8;

}

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

	make_tile(test_data);

	show_tile(tile);
}

SDL_Color dmg_palette[4] = {
    {155, 188, 15, 255},
    {139, 172, 15, 255},
    {48, 98, 48, 255},
    {15, 56, 15, 255}
};

void render_screen(struct Game *g){

    	SDL_SetRenderDrawColor(g->renderer, dmg_palette[3].r, dmg_palette[3].g,dmg_palette[3].b,dmg_palette[3].a); // Black colour
    	SDL_RenderClear(g->renderer);


  	for(int y = 0; y < WINDOW_HEIGHT; y++) {
        	for(int x = 0; x < WINDOW_WIDTH; x++) {
			uint8_t color = background[y][x] & 0x03;

			SDL_Color c = dmg_palette[3 - color]; // if you want 0 = darkest, 3 = lightest

			SDL_SetRenderDrawColor(g->renderer,c.r,c.g,c.b,c.a);

                	SDL_FRect rect = {x * SCALE * 4, y * SCALE * 4, SCALE * 4, SCALE * 4};
                	SDL_RenderFillRect(g->renderer, &rect);
        	}
    	}

    	SDL_RenderPresent(g->renderer); // update the rendering content
}

bool clear_screen(struct Game *g){
	memset(display, 0, sizeof(display));

    	SDL_SetRenderDrawColor(g->renderer, 0, 0, 0, 255);
    	SDL_RenderClear(g->renderer);
    	SDL_RenderPresent(g->renderer);
    	return true;
}

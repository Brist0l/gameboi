#include <stdlib.h>

#include "display.h"
#include "registers_ppu.h"
#include "debug.h"
#include "ppu.h"
#include "memory.h"
#include "tile.h"

static uint16_t window_mem = 0x9800;
static uint16_t window_mem_end;
static int d_x = 0;
static int d_y = 0;


void show_window(){
	for(int y = 0; y < 256;y++){
		for(int x = 0; x < 256;x++){
			dprintf("%02b ",window[y][x]);
		}
		dprintf("\n");
	}
}

void window_to_display(){
	int wy = getWY(); // Top
	int wx = getWX(); // Left

	// This is a redundant test cuz it will
	// always be below 255 as it's a 8 bit
	// register
	//
	//if(wx >= 256)		scx %= 256;
	//
	//if(wy >= 256)
	//	wy %= 256;

	dprintf("WX : %d\nWY : %d\n",wx,wy);
	exit(1);

	for(int y = 0; y < WINDOW_HEIGHT; y++){
		for(int x = 0; x < WINDOW_WIDTH; x++){
			display[y][x] = window[(wy + y) % 256][(wx + 7 + x) % 256];
			dprintf("%d ",window[((wy) + y) % 256][(wx + 7 + x) % 256]);
			if(x % 8 == 0)
				dprintf("\n");
		}
			dprintf("-(12) + y = %d\n",((wy) + y) % 256);

	}

}

uint16_t select_window(){
	// This will select the window map depending
	// on the LCDC bit
	//
	// Returns the ending address of the window.

	if(LCDC_lcd_window_tile_map_select_6() == 0){
		window_mem = 0x9800;
		return 0x9bff;
	}
	else{
		window_mem = 0x9c00;
		return 0x9fff;
	}

}

void set_window(){
	exit(1);
	uint8_t data[16];
	int window_y = 0;
	int window_x = 0;
	uint16_t start_addr;

	// Sets window memory as well now it sets the
	// window_mem_end
	window_mem_end = select_window();

	while(window_mem_end > window_mem){
		// Assume that you have a tile number 0.
		// So that means that it would start at
		// 0x8000 and then it would read 16 bytes
		// from there , i.e. till 0x800f
		//
		// So address can be calculated like
		//
		// start_addr = 0x8000 + 16 * (tile_num)

		if(select_addressing_method() == 1)
			start_addr = base_ptr + 16 * (uint8_t)((memory_read(window_mem)));
		else
			start_addr = base_ptr + 16 * (int8_t)((memory_read(window_mem)));

		window_mem++;

		for(int i = 0; i < 16; i++)
			data[i] = memory_read(start_addr + i);

		make_tile(data); // form the data into a tile


		// Set the window as the tile
		for(int y = 0; y < 8;y++){
			for(int x = 0; x < 8;x++){
				window[window_y + y][window_x + x] = tile[y][x];
				dprintf("d_y : %d\nd_x: %d\n",d_y,d_x);
			}

		}

		window_x += 8;

		if(window_x == 256){
			dprintf("Setting window_x to 0!!!\n");
			window_x = 0;
			window_y += 8;

		}


		if(window_y >= 256){
			dprintf("Setting window_y to 0!!!\n");
			window_y = 0;
		}

	}

 	window_to_display();
}


#include "display.h"
#include "registers_ppu.h"
#include "debug.h"
#include "ppu.h"
#include "memory.h"
#include "tile.h"

static uint16_t background_mem = 0x9800;
static uint16_t background_mem_end;
static uint16_t base_ptr;
static int d_x = 0;
static int d_y = 0;

void select_addressing_method(){
	if(LCDC_tile_data_select_4() == 0)
		base_ptr = 0x9000;
	else{
		//unsigned addressing
		//Tiles 0 - 127 are in block 0
		//Tiles 128  - 255 are in block 1
		base_ptr = 0x8000;
	}
}

void show_background(){
	for(int y = 0; y < 256;y++){
		for(int x = 0; x < 256;x++){
			dprintf("%02b ",background[y][x]);
		}
		dprintf("\n");
	}
}

void background_to_display(){
	int scy = getSCY(); // Top
	int scx = getSCX(); // Left

	// This is a redundant test cuz it will
	// always be below 255 as it's a 8 bit
	// register
	//
	//if(scx >= 256)		scx %= 256;
	//
	//if(scy >= 256)
	//	scy %= 256;

	dprintf("SCX : %d\nSCY : %d\n",scx,scy);
	//exit(1);

	for(int y = 0; y < WINDOW_HEIGHT; y++){
		for(int x = 0; x < WINDOW_WIDTH; x++){
			display[y][x] = background[(scy + y) % 256][(scx + x) % 256];
			dprintf("%d ",background[((scy) + y) % 256][(scx +x) % 256]);
			if(x % 8 == 0)
				dprintf("\n");
		}
			dprintf("-(12) + y = %d\n",((scy) + y) % 256);

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
	int background_y = 0;
	int background_x = 0;

	// Sets background memory as well now it sets the
	// background_mem_end
	background_mem_end = select_background();

	while(background_mem_end > background_mem){
		// Assume that you have a tile number 0.
		// So that means that it would start at
		// 0x8000 and then it would read 16 bytes
		// from there , i.e. till 0x800f
		//
		// So address can be calculated like
		//
		// start_addr = 0x8000 + 16 * (tile_num)

		select_addressing_method();
		uint16_t start_addr = base_ptr + 16 * (memory_read(background_mem));
		background_mem++;

		for(int i = 0; i < 16; i++)
			data[i] = memory_read(start_addr + i);

		make_tile(data); // form the data into a tile


		// Set the background as the tile
		for(int y = 0; y < 8;y++){
			for(int x = 0; x < 8;x++){
				background[background_y + y][background_x + x] = tile[y][x];
				dprintf("d_y : %d\nd_x: %d\n",d_y,d_x);
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

	background_to_display();
}


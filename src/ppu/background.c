#include "display.h"
#include "registers_ppu.h"
#include "debug.h"
#include "ppu.h"
#include "memory.h"
#include "tile.h"
#include "display.h"

static uint16_t background_mem = 0x9800;
static uint16_t background_mem_end;
uint16_t start_addr;

void show_background(){
	for(int y = 0; y < 256;y++){
		for(int x = 0; x < 256;x++){
			dprintf("%02b ",background[y][x]);
		}
		dprintf("\n");
	}
}



void background_to_display(){
	logmsg("background_to_display",true);

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
			//dprintf("%d ",background[((scy) + y) % 256][(scx +x) % 256]);
			//if(x % 64 == 0)
				//dprintf("\n");
		}
	}

	dprintf("\n");
	logmsg("background_to_display",false);

}

uint16_t select_background(){
	// This will select the background map depending
	// on the LCDC bit
	//
	// Returns the ending address of the background.
	if(LCDC_bg_tile_map_select_3() == 0){
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
	uint16_t start_addr;

	// Sets background memory as well now it sets the
	// background_mem_end
	background_mem_end = select_background();

	while(background_mem_end >= background_mem){
		// Assume that you have a tile number 0.
		// So that means that it would start at
		// 0x8000 and then it would read 16 bytes
		// from there , i.e. till 0x800f
		//
		// So address can be calculated like
		//
		// start_addr = 0x8000 + 16 * (tile_num)

		if(select_addressing_method() == 1)
			start_addr = base_ptr + (16 * (uint8_t)((memory_read(background_mem))));
		else
			start_addr = base_ptr + (16 * (int8_t)((memory_read(background_mem))));

		background_mem++; // Index to the next tile

		for(int i = 0; i < 16; i++)
			data[i] = memory_read(start_addr + i);

		make_tile(data); // form the data into a tile


		// LY renderer
		for(int x = 0; x < 8;x++)
			background[getLY()][background_x + x] = tile[getLY() % 8][x];


		// Set the background as the tile
		//for(int y = 0; y < 8;y++){
			//for(int x = 0; x < 8;x++){
			//background[background_y + y][background_x + x] = tile[y][x];
				//dprintf("d_y : %d\nd_x: %d\n",d_y,d_x);
			//}

		//}

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

void set_background_ly(){
	// You just need to render 1 line , hence you keep on reading the first
	// 32 tiles only until LY is 8 , then the next 32 tiles
	// Always base them on LY.
	//
	// Hence I have got the rows using LY % 8.
	//
	// Ly == 0
	// then I will get the 0th row
	// if LY == 1
	// Then I will get the 1st row
	//
	// If LY == 7
	// Then I will get the 7th row
	//
	// If LY == 8
	// Then I will get the 0th row
	//
	// But now t

	uint8_t data[2];
	int background_x = 0;

	int tiles = 0;

	while(tiles != 32){
		background_mem_end = select_background();
		background_mem += (((getLY()/8) * 32) + tiles); // Index to the next tile

		if(select_addressing_method() == 1)
			start_addr = base_ptr + (16 * (uint8_t)((memory_read(background_mem))));
		else
			start_addr = base_ptr + (16 * (int8_t)((memory_read(background_mem))));

		printf("start addr = %x\n", start_addr);
		printf("base ptr = %x\n", base_ptr);
		printf("memory_read's on background = %x\n",(uint8_t)((memory_read(background_mem))));
		printf("index of background = %x\n",16 * (uint8_t)((memory_read(background_mem))));
		printf("background_mem = %x\n", background_mem);
		printf("end mem = %x\n", background_mem_end);
		printf("row  = %d\n", getLY() % 8);

		for(int i = 0; i < 2; i++)
			data[i] = memory_read(start_addr + i + ((getLY() % 8)*2));

		make_tile_line(data); // form the data into a tile

		printf("%d -> ",getLY());

		for(int tile_x = 0; tile_x < 8;tile_x++){
			background[getLY()][tile_x + background_x] = tile_line[tile_x];
			printf("%b ",tile_line[tile_x]);
		}
		printf("\n");

		background_x += 8;
		printf("background_x = %d\n", background_x);

		tiles++;

	}
}

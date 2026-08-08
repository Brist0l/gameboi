#include<stdint.h>

#include "debug.h"
#include "ppu.h"

#define STD_LSB 0b00000001
#define STD_MSB 0b00000010

void show_tile(uint8_t tile[8][8]){
	for(int y = 0; y < 8;y++){
		for(int x = 0; x < 8;x++){
			dprintf("%02b ",tile[y][x]);
		}
		dprintf("\n");
	}

}

void show_line(uint8_t tile[8]){
	for(int x = 0; x < 8;x++)
		dprintf("%02b ",tile[x]);

	dprintf("\n");

}

void make_tile(uint8_t test_data[]){
	int t_x = 0; // Goes Right
	int t_y = 0; // Goes Down
	uint8_t lsbs;
	uint8_t msbs;

	for(int data = 0;data < 16;data += 2){
		lsbs = test_data[data];
		msbs = test_data[data + 1];

		for(int bit = 7;bit >= 0;bit--){
			uint8_t the_lsb = (lsbs >> bit) & 1;
			uint8_t the_msb = (msbs >> bit) & 1;

			uint8_t pixel = (the_msb << 1) | the_lsb;

			tile[t_y][t_x++] = pixel;
		}

		t_y++;
		t_x = 0;
	}

	if(debug_flag == true)
		show_tile(tile);
}

void make_tile_line(uint8_t test_data[]){
	int t_x = 0; // Goes Right
		     
	uint8_t lsbs;
	uint8_t msbs;

	lsbs = test_data[0];
	msbs = test_data[1];

	for(int bit = 7;bit >= 0;bit--){
		uint8_t the_lsb = (lsbs >> bit) & 1;
		uint8_t the_msb = (msbs >> bit) & 1;

		uint8_t pixel = (the_msb << 1) | the_lsb;

		tile_line[t_x++] = pixel;
	}

	if(debug_flag == true)
		show_line(tile_line);
}


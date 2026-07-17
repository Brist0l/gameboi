#include<stdint.h>

#include "debug.h"
#include "ppu.h"

#define STD_LSB 0b00000001
#define STD_MSB 0b00000010

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

void show_tile(uint8_t tile[8][8]){
	for(int y = 0; y < 8;y++){
		for(int x = 0; x < 8;x++){
			dprintf("%02b ",tile[y][x]);
		}
		dprintf("\n");
	}

	/*
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
	*/

}

#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>
#include<stdbool.h>

#include "display.h"
#include "debug.h"

#define STD_LSB 0b00000001
#define STD_MSB 0b00000010

uint8_t display[WINDOW_HEIGHT][WINDOW_WIDTH] = {0};

/* ========PPU: The picture processing unit========
 *
 * The GB uses 3 separate layers to display graphics on,
 * 		1) Background
 * 		2) Window
 * 		3) Sprites
 *
 * 1) Background: It's a 32x32 tile grid (i.e. 32*8 x 32*8 == 256x256 pixels),
 *    but the GB can only show 20x18 tiles(i.e 20*8 x 18*8 == 160x144 pixels).
 *    This section will be refered to as the "viewport".
 *
 *    The viewport will be changed via the SCX and SCY registers.
 *
 *    If the viewport exceeds the border of the background then it's wrapped
 *    around the left/top respectively.
 *
 * 2) Window: It's also 32x32 tiles wide. It's an overlay on the background.
 *
 *    The position of this window can be determined via WX an WY registers.
 *
 *    		WY (0xFF4A) => This just gives y-pos of where the top of the
 *    			       window should be placed on the background.
 *    			       0 means it's at the very top.
 *
 *    		WX (0xFF4B) => This just gives x-pos of where the window
 *    			       should be placed on the background.
 *    			       The value should be calculated as WX - 7.
 * 3) Sprites:
 *
 *
 * =======Tile:=====================================
 *
 * Pixels aren't manipluated individually cuz that would be too CPU expensive,
 * instead the pixels are grouped in 8x8 squares called TILES(these are the base
 * unit in gameboy's graphics).
 *
 * It doesn't have colour info but it has colour indices ranging from 0 to 3
 * (i.e. 0 , 1, 2, 3) , which means 4 total possibilieties, hence we need 2 bits
 * so another name for gameboy graphics is 2 bpp (2 bits per pixel).
 *
 * So this tile data will be stored in the VRAM (Video RAM , basically it's like
 * a RAM but for pixels and stuff). The tile data is stored in,
 *
 * 			0x8000 to 0x97ff
 *
 * That's about 6kb worth of data for tiles.
 * So there are 8x8 squares which are being used, that means 64 pixels, but the gameboy
 * is a 2 bpp , so that means 64 * 2 bits , that means 128 bit worth of memory will be
 * used to store 1 tile. Converting it to bytes ,  we get 128/8 bytes , or 16 bytes.
 * That means we can store 6kb/16 tiles in the VRAM at once, which is 384 tiles.
 *
 */


void show_tile(uint8_t tile[8][8]){
	for(int y = 0; y < 8;y++){
		for(int x = 0; x < 8;x++){
			dprintf("%02b ",tile[y][x]);
		}
		dprintf("\n");
	}

	for(int y = 0; y < 8;y++){
		for(int x = 0; x < 8;x++){
			display[y][x] = tile[y][x];
		}
	}


}

bool draw(struct Game *g){
	// This will handle "which" pixels need to light up.
	// Rn this just will set display to 0 or non 0 , and then according to that render it

	// The first two bytes is the first row and so on and so forth.
	// 0xFF => 1 1 1 1 1 1 1 1 -> Least significant byte of colour
	// 								=> 01 01 01 01 01 01 01 01
	// 0x00 => 0 0 0 0 0 0 0 0 -> Most significant byte  of colour

	uint8_t test_data[] = {
    0xFF, 0x00, 0x7E, 0xFF,
    0x85, 0x81, 0x89, 0x83,
    0x93, 0x85, 0xA5, 0x8B,
    0xC9, 0x97, 0x7E, 0xFF
};
	uint8_t tile[8][8] = {0};
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
			uint8_t color = display[y][x] & 0x03;

			SDL_Color c = dmg_palette[3 - color]; // if you want 0 = darkest, 3 = lightest

			SDL_SetRenderDrawColor(g->renderer,c.r,c.g,c.b,c.a);

                	SDL_FRect rect = {x * SCALE * 2, y * SCALE * 2, SCALE * 2, SCALE * 2};
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

#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>
#include<stdbool.h>
#include<stdlib.h>

#include "debug.h"
#include "memory.h"

#define SDL_FLAGS SDL_INIT_VIDEO
#define WINDOW_TITLE "Open Window"
#define WINDOW_WIDTH 160
#define WINDOW_HEIGHT 144
#define SCALE 5

struct Game{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background;
	SDL_Event event;
	bool is_running;
	bool keypad[16];
};

bool display[WINDOW_HEIGHT][WINDOW_WIDTH] = {0};

bool game_init_sdl(struct Game *g);
bool game_new(struct Game **game);
void game_free(struct Game **game);
void game_events(struct Game *g,int* key);
bool draw(struct Game *g,int x,int y,int N,int data);
void render_screen(struct Game *g);
bool clear_screen(struct Game *g);


/* 
 * Tile:
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


bool game_init_sdl(struct Game *g){
	//printf("%d\n",SDL_FLAGS);
	if(!SDL_Init(SDL_FLAGS)){ // Inits the SDL system as a whole
		dprintf("Error initialising SDL3: %s\n",SDL_GetError());
		return false;
	}

	g->window = SDL_CreateWindow(WINDOW_TITLE,WINDOW_WIDTH * SCALE,WINDOW_HEIGHT * SCALE,0);

	if(!g->window){
		dprintf("Error Creating window: %s\n",SDL_GetError());
		return false;
	}

	g->renderer = SDL_CreateRenderer(g->window,NULL);

	if(!g->renderer){
		dprintf("Error Creating renderer: %s\n",SDL_GetError());
		return false;
	}

	return true;
}

bool game_new(struct Game **game){
	*game = calloc(1,sizeof(struct Game));

	if(*game == NULL){
		dprintf("Error while allocating memory\n");
		return false;
	}

	struct Game *g = *game; //Just to not modify the code beneath this

	if(!game_init_sdl(g)){
		dprintf("Failed to init SDL: %s\n",SDL_GetError());
		return false;
	}

	g->is_running = true;

	return true;
}

void game_free(struct Game **game){
	if(*game){
		struct Game *g = *game;
		if(g->window){
			SDL_DestroyWindow(g->window);
			g->window = NULL;
		}
		if(g->renderer){
			SDL_DestroyRenderer(g->renderer);
			g->window = NULL;
		}

		SDL_Quit();

		free(g);
		g = NULL;
		*game = NULL;

		dprintf("Quiting SDL\n");
	}
}

void game_events(struct Game *g,int* key){
		while(SDL_PollEvent(&(g->event))){
			dprintf("POLLING !!!!\n");
			switch (g->event.type){
				case SDL_EVENT_QUIT:
					dprintf("Quit has been pressed\n");
					g->is_running = false;
					break;

				case SDL_EVENT_KEY_UP:
				case SDL_EVENT_KEY_DOWN:
                			bool isPressed = (g->event.type == (SDL_EVENT_KEY_DOWN));
                			switch (g->event.key.scancode){
						case SDL_SCANCODE_ESCAPE: 
							dprintf("Quitting!\n");
							g->is_running = false;
							break;

                    				//case SDL_SCANCODE_X: g->keypad[0x0] = isPressed;break;
                    				//case SDL_SCANCODE_1: g->keypad[0x1] = isPressed;break;
				                //case SDL_SCANCODE_2: g->keypad[0x2] = isPressed;break;
                    				case SDL_SCANCODE_3: g->keypad[0x3] = isPressed;break;
                    				case SDL_SCANCODE_Q: 
							dprintf("Pressed Q\n");
							g->keypad[0x4] = isPressed;
							break;

                    				case SDL_SCANCODE_W: g->keypad[0x5] = isPressed;break;
                    				case SDL_SCANCODE_E: g->keypad[0x6] = isPressed;break;
                    				case SDL_SCANCODE_A: g->keypad[0x7] = isPressed;break;
                    				case SDL_SCANCODE_S: g->keypad[0x8] = isPressed;break;
                    				case SDL_SCANCODE_D: g->keypad[0x9] = isPressed;break;
                    				case SDL_SCANCODE_Z: g->keypad[0xA] = isPressed;break;
                    				case SDL_SCANCODE_C: g->keypad[0xB] = isPressed;break;
                    				case SDL_SCANCODE_4: g->keypad[0xC] = isPressed;break;
                    				case SDL_SCANCODE_R: g->keypad[0xD] = isPressed;break;
                    				case SDL_SCANCODE_F: g->keypad[0xE] = isPressed;break;
                    				case SDL_SCANCODE_V: g->keypad[0xF] = isPressed;break;
					}
			}
	}
}

bool draw(struct Game *g){
	uint8_t test_data[] = {0xFF,0x00,0x7E,0xFF,0x85,0x81,0x89,0x83,0x93,0x85,0xA5,0x8B,0xC9,0x97,0x7E,0xFF};

}

void render_screen(struct Game *g){
    	SDL_SetRenderDrawColor(g->renderer, 0, 0, 0, 255); // Black colour
    	SDL_RenderClear(g->renderer);

    	SDL_SetRenderDrawColor(g->renderer, 255, 255, 255, 255);

	draw(g);

  	for(int y = 0; y < WINDOW_HEIGHT; y++) {
        	for(int x = 0; x < WINDOW_WIDTH; x++) {
            		if (display[y][x]) {
                		SDL_FRect rect = {x * SCALE, y * SCALE, SCALE, SCALE};
                		SDL_RenderFillRect(g->renderer, &rect);
            		}
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

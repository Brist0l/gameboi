#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>
#include<stdbool.h>
#include<stdlib.h>

#include "debug.h"
#include "display.h"



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
		dprintf("Error while allocating memory for game\n");
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
								     					default:
								     break;
								
					}
			}
	}
}

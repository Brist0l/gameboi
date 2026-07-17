#ifndef PPU_H
#define PPU_H

#include<SDL3/SDL.h> 
#include<SDL3/SDL_main.h>

#include "display.h"


bool game_load_media(struct Game *g);
void game_draw(struct Game *g);
bool draw(struct Game *g);
void render_screen(struct Game *g);
bool clear_screen(struct Game *g);
void show_background();

#endif

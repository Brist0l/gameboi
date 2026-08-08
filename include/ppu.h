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
bool select_addressing_method();
unsigned int ppu_step(unsigned int t_cycles);

extern uint8_t background[256][256];
extern uint8_t window[256][256];
extern uint8_t display[WINDOW_HEIGHT][WINDOW_WIDTH];
extern uint8_t tile[8][8];
extern uint8_t tile_line[8];
extern uint16_t base_ptr;
extern unsigned int ppu_t_cycles;

#endif

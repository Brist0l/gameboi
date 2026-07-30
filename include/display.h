#ifndef DISPLAY_H
#define DISPLAY_H

#include<stdbool.h>
#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>

#define SDL_FLAGS SDL_INIT_VIDEO
#define WINDOW_TITLE "Open Window"
#define WINDOW_WIDTH 160
#define WINDOW_HEIGHT 144
#define SCALE 8
#define BACKGROUND_SCALE 4

struct Game{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background;
	SDL_Event event;
	bool is_running;
	bool keypad[16];
};


bool game_new(struct Game **game,const char* title,int width,int height,int scale);
void game_free(struct Game **game);
void game_events(struct Game *g,int* key);


#endif /* DISPLAY_H */

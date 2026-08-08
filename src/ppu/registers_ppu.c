#include<stdint.h>

#include "memory.h"
#include "debug.h"

uint8_t LCDC_lcd_ppu_enable_bit_7(){
	dprintf("LCDC Regiser : 0b%08b\n",memory_read(0xff40));
	return (((memory_read(0xff40)) & 0b10000000) >> 7 );
}

uint8_t LCDC_lcd_window_tile_map_select_6(){
	dprintf("LCDC Regiser : 0b%08b\n",memory_read(0xff40));
	return (((memory_read(0xff40)) & 0b01000000) >> 6 );
}

uint8_t LCDC_lcd_window_display_enable_5(){
	dprintf("LCDC Regiser : 0b%08b\n",memory_read(0xff40));
	return (((memory_read(0xff40)) & 0b00100000) >> 5 );
}

uint8_t LCDC_tile_data_select_4(){
	dprintf("LCDC Regiser : 0b%08b\n",memory_read(0xff40));
	return (((memory_read(0xff40)) & 0b00010000) >> 4 );
}

uint8_t LCDC_bg_tile_map_select_3(){
	dprintf("LCDC Regiser : 0b%08b\n",memory_read(0xff40));
	return (((memory_read(0xff40)) & 0b00001000) >> 3);
}
uint8_t LCDC_sprite_size_2(){
	dprintf("LCDC Regiser : 0b%08b\n",memory_read(0xff40));
	return (((memory_read(0xff40)) & 0b00000100) >> 2 );
}

uint8_t LCDC_sprite_enable_1(){
	dprintf("LCDC Regiser : 0b%08b\n",memory_read(0xff40));
	return (((memory_read(0xff40)) & 0b00000010) >> 1 );
}

uint8_t LCDC_background_window_enable(){
	dprintf("LCDC Regiser : 0b%08b\n",memory_read(0xff40));
	return (((memory_read(0xff40)) & 0b00000001) >> 0 );
}

void LCDC_show(){
	dprintf("LCDC : 0b%08b\n",memory_read(0xff40));
}

uint8_t getSCY(){
	return memory_read(0xff42);
}

uint8_t getSCX(){
	return memory_read(0xff43);
}

uint8_t getLY(){
	return memory_read(0xff44);
}

void setLY(uint8_t val){
	memory_write(0xff44,val);
}

void showLY(){
	printf("LY: %d\n", memory_read(0xff44));
}

uint8_t getWY(){
	return memory_read(0xff4a);
}

uint8_t getWX(){
	return memory_read(0xff4b);
}

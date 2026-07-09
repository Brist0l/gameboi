#include<stdint.h>

#include "memory.h"

uint8_t getLCDC(){
/* PPU Control Register:
 *
 * LCDC is the LCD Control register , Its bits toggle what elements are
 * displayed on the screen, and how. It's at 0xFF40 , a memory address.
 * This address falls in "I/O" section of the memory.
 *
 *	LCD and PPU enable 	   => 7th bit
 * 	---------------------------
 *	Window and tile map area   => 6th bit
 *	---------------------------
 *	Window enable	           => 5th bit
 *	---------------------------
 *	BG and Window tiles        => 4th bit
 *	---------------------------
 *	BG tile map   		   => 3rd bit
 *	---------------------------
 *	OBJ size		   => 2nd bit
 *	---------------------------
 *	OBJ enable	   	   => 1st bit
 *	---------------------------
 *	BG and window enable       => 0th bit
 *	---------------------------
 *
 */
	return memory_read(0xff40);
}

uint8_t getLY(){
/* LY (LCD Y Coordinate [RO]):
 *
 * It indicates the current horizontal line, which might be
 * about to be drawn , being drawn or has been drawn.
 *
 * LY can hold any value from 0 to 153.
 *
 * This is at the address 0xFF44
 */
	return memory_read(0xff44);
}

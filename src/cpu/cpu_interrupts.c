#include "cpu.h"
#include "debug.h"
#include "memory.h"

#include <stdlib.h>

void check_interrupts(){
	if(cpu.IME == 1){
		// check interrupts
		// IE register
		//
		// bit 0 => Vblank
		// bit 1 => LCD 
		// bit 2 => Timer
		// bit 3 => Serial
		// bit 4 => Joypad
		
		uint8_t IE = memory_read(0xffff);
		uint8_t IF = memory_read(0xff0f);

		dprintf("The IME flag is on\n");
		dprintf("The IE flag is 0x%08b\n",IE);
		dprintf("The IF flag is 0x%08b\n",IF);

		if(IF != 0)
			exit(1);

		if(IE & IF){
			if((IE & 1) & (IF & 1)){
				// V-BLANK

			}
		}
		
	}
	else
		dprintf("The IME flag is off\n");

}

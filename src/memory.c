#include<stdint.h>
#include<unistd.h>

#include "cpu.h"
#include "debug.h"

char serial_data;
char serial_data_string[0x100];
int i = 0;
uint8_t memory[0xFFFF];

/*
 * From TCAGBD , 2. Memory
Addresses 	Name 	Description
0000h – 3FFFh 	ROM0 	Non-switchable ROM Bank.
4000h – 7FFFh 	ROMX 	Switchable ROM bank.
8000h – 9FFFh 	VRAM 	Video RAM, switchable (0-1) in GBC mode.
A000h – BFFFh 	SRAM 	External RAM in cartridge, often battery buffered.
C000h – CFFFh 	WRAM0 	Work RAM.
D000h – DFFFh 	WRAMX 	Work RAM, switchable (1-7) in GBC mode
E000h – FDFFh 	ECHO 	Description of the behaviour below.
FE00h – FE9Fh 	OAM 	(Object Attribute Table) Sprite information table.
FEA0h – FEFFh 	UNUSED 	Description of the behaviour below.
FF00h – FF7Fh 	I/O 	Registers I/O registers are mapped here.
FF80h – FFFEh 	HRAM 	Internal CPU RAM
FFFFh 		IE 	Register Interrupt enable flags.
*/


/*

Interrupt Enable Register
--------------------------- FFFF
Internal RAM
--------------------------- FF80
Empty but unusable for I/O
--------------------------- FF4C
I/O ports
--------------------------- FF00
Empty but unusable for I/O
--------------------------- FEA0
Sprite Attrib Memory (OAM)
--------------------------- FE00
Echo of 8kB Internal RAM
--------------------------- E000
8kB Internal RAM
--------------------------- C000
8kB switchable RAM bank
--------------------------- A000
8kB Video RAM
--------------------------- 8000 --
16kB switchable ROM bank |
--------------------------- 4000 |= 32kB Cartrigbe
16kB ROM bank #0 |
--------------------------- 0000 --
* NOTE: b = bit, B = byte
*/

void loader(unsigned char data,unsigned int offset){
	*(memory + offset) = data;
}

// Over here SP is the top so I would need to subtract first and then
// store as if I don't then overflow is happening.
void push(uint8_t value){
	memory[--cpu.SP] = value;
}

uint8_t pop(){
	return memory[cpu.SP++];
}

void memory_write(uint16_t mem_addr,uint8_t val){
	if(mem_addr == 0xff01){
        	serial_data = val;
	}

    	if(mem_addr == 0xff02 && val == 0x81){
		//serial_data_string[i++] = serial_data;
		//dprintf("0x%x",serial_data);
		//if(serial_data  == 's'){
        		//dprintf("Serial IO: %s\n",serial_data_string);
			//sleep(2);
		//}
		serial_io(serial_data);
	}

	if(mem_addr == 0xdef6 && val == 0x0f){
	    //printf("READ %04x\n",mem_addr);
            //memory[0xdef6] = 0x87; //  Just to pass the infinite loop
	    //exit(1);
	    _memorydump(0xdef0,0xdef6);
	    dprintf("===========================================+++++++++++++++++++++++++++++++++++================================\n");
	}

	if(mem_addr == 0xdf7e && val == 0x9b){
	    //printf("READ %04x\n",mem_addr);
            //memory[0xdef6] = 0x87; //  Just to pass the infinite loop
	    //exit(1);
	    dprintf("find_this\n");
	}

	if(mem_addr == 0xc704 && val == 0x0f){
	    //printf("READ %04x\n",mem_addr);
            //memory[0xdef6] = 0x87; //  Just to pass the infinite loop
	    _memorydump(0x4700,0x470f);
	    dprintf("===========================================+++++++++++++++++++++++++++++++++++================================\n");
	    //exit(1);
	}

	//if(mem_addr >= 0x9900 && mem_addr <= 0x9940)
	    //printf("WRITE 0x%04x = 0x%02x\n",mem_addr,val);

	memory[mem_addr] = val;
}

uint8_t memory_read(uint16_t mem_addr){
	if(mem_addr == 0xff44){
	    //printf("READ %04x\n",mem_addr);
	    return 0x90;
	}

	return memory[mem_addr];
}

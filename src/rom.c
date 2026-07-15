#include<stdio.h>
#include<stdint.h>
#include<sys/stat.h>
#include<sys/types.h>

//#include "cpu.h" // includes always just copy paste the code from the file
#include "memory.h"
#include "debug.h"
#include "rom.h"

off_t getsize(const char *filename){
	// https://en.wikipedia.org/wiki/Stat_(system_call)

	struct stat st;

	if(stat(filename, &st) == 0)
		return st.st_size;

	    return -1;
}

void load_rom(const char *filename,unsigned int size,unsigned short offset){
	unsigned char bytecode;

	unsigned int byt_cnt = 0;
	FILE* rom_file = fopen(filename,"rb");

	while(byt_cnt != size){
		bytecode = fgetc(rom_file);

		*(memory + offset + byt_cnt) = bytecode;

		byt_cnt++;

		//dprintf(ANSI_COLOR_YELLOW);
		//dprintf("%02x ",bytecode);
		//dprintf(ANSI_COLOR_RESET);

		//if(++byt_cnt % 32 == 0)
			//dprintf("\n");

	}

	//dprintf("\n");

	fclose(rom_file);
}

void overwrite(const char *filename,unsigned int size,unsigned short offset){
	unsigned char bytecode;

	unsigned int byt_cnt = 0;
	FILE* rom_file = fopen(filename,"rb");

	while(byt_cnt != size){
		bytecode = fgetc(rom_file);

		*(memory + offset + byt_cnt) = bytecode;

		byt_cnt++;

		//dprintf(ANSI_COLOR_YELLOW);
		//dprintf("%02x ",bytecode);
		//dprintf(ANSI_COLOR_RESET);

		//if(++byt_cnt % 32 == 0)
			//dprintf("\n");

	}

	//dprintf("\n");

	fclose(rom_file);
}

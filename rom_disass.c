#include<stdio.h>
#include<stdint.h>
#include<sys/stat.h>
#include<sys/types.h>

//#include "cpu.h" // includes always just copy paste the code from the file
#include "memory.h"
#include "debug.h"

off_t getsize(const char *filename){
	// https://en.wikipedia.org/wiki/Stat_(system_call)

	struct stat st;

	if(stat(filename, &st) == 0)
		return st.st_size;

	    return -1;
}

void loader(uint8_t* mem,unsigned char data,unsigned int offset){
	logmsg("loader",true,debug_flag);
	*(mem + offset) = data;
	logmsg("loader",false,debug_flag);
}

void decode(uint8_t* mem){


}

void read(){
	unsigned char bytecode;
	const char *filename = "dmg_boot.bin";

	int cnt = 1;
	unsigned int byt_cnt = 0;
	unsigned int size = getsize(filename);
	FILE* rom_file = fopen(filename,"r");

	//printf("Size: %d\n",getsize(filename));

	while(byt_cnt != size){
		bytecode = fgetc(rom_file);
		loader(memory,bytecode,byt_cnt++);

		if(++cnt > 16){
			printf("\n");
			cnt = 1;
		}
		else
			printf("0x%02x ",bytecode);
	}

	fclose(rom_file);
}

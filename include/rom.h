#ifndef rom_disass_h
#define rom_disass_h

#include <sys/types.h>

void load_rom(const char *filename,unsigned int size,unsigned short offset);
off_t getsize(const char *filename);

#endif

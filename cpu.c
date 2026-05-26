#include<stdio.h>
#include<stdint.h>

#include "cpu.h"

/* CPU is little endian. The property is of how bytes are stored in
 * the memory and not of the "CPU" itself. CPU is the dumbest layer
 * but the fastest , the endianness comes on top of that layer. 
 * i.e. someone else will interpret the endianness for it , it will
 * just work with the bytes. Another thing is that CPU hence works
 * on multiples of 4 so that it's easy to maintain endianness. 
 * 0x1234 gets stored as 34 12 in little endian. 0x123456 gets 
 * converted to 0x00123456 and now is stored as 56 34 12 00.*/

struct registers cpu;

void execute(uint8_t){


}


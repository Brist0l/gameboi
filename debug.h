#ifndef DEBUG_H
#define DEBUG_H

#include<stdbool.h>

void logmsg(const char* function_name,bool start,bool debug_flag);
void _memoryframe(short start,short end);
void _fillopcode();

extern bool debug_flag;

#endif

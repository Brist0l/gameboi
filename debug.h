#ifndef DEBUG_H
#define DEBUG_H

#include<stdbool.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define dprintf(...)            \
    do {                            \
        if (debug_flag){             \
            printf(__VA_ARGS__);    	\
	} \
    } while (0)


void logmsg(const char* function_name,bool start);
void _memoryframe(short start,short end);
void _memorydump(int start,int end);
void _fillopcode();

extern bool debug_flag;

#endif

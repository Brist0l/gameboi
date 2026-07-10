run:
	gcc -o run *.c -Wall -Wextra -Wswitch -g -O3 -l SDL3

ppu_debug:
	gcc -o ppu_debug display.c ppu.c ppu_debug.c -Wall -Wextra -g -O3 -l SDL3

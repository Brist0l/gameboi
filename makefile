.DEFAULT_GOAL := run
.PHONY : clean

sources := $(wildcard *.c)
sources := $(wildcard *.c)

run_sources := $(filter-out ppu_debug.c,$(sources))
debug_sources := $(filter-out main.c,$(sources))

OBJDIR := build/obj
DEPDIR := build/dep
CFLAGS := -Wall -Wextra -Wswitch -O3
DFLAGS := -g -MMD -MP
CFLAGS += $(shell pkg-config --cflags sdl3)
LDFLAGS := $(shell pkg-config --libs sdl3)

run_objects := $(patsubst %.c,$(OBJDIR)/%.o,$(run_sources))
ppu_debug_objects := $(patsubst %.c,$(OBJDIR)/%.o,$(debug_sources))

$(OBJDIR) $(DEPDIR):
	mkdir -p $@

$(OBJDIR)/%.o: %.c | $(OBJDIR) $(DEPDIR)
	gcc -o $@ $< -c $(CFLAGS) $(DFLAGS) -MF $(DEPDIR)/$*.d


run: $(run_objects)
	gcc -o $@ $^ $(LDFLAGS)

ppu_debug: $(ppu_debug_objects)
	gcc -o $@ $^ $(LDFLAGS)

deps := $(patsubst %.c,$(DEPDIR)/%.d,$(sources))

clean:
	rm -f $(run_objects) $(ppu_debug_objects) $(deps) run ppu_debug

-include $(deps)

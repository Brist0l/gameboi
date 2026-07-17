.DEFAULT_GOAL := run
.PHONY : clean

sources := $(shell find src -name '*.c')

run_sources := $(filter-out src/ppu_debug.c,$(sources))
debug_sources := $(filter-out src/main.c,$(sources))

OBJDIR := build/obj
DEPDIR := build/dep
BINDIR := bin

CFLAGS := -Wall -Wextra -Wswitch -O3
DFLAGS := -g -MMD -MP
CFLAGS += $(shell pkg-config --cflags sdl3)
CFLAGS += -Iinclude
LDFLAGS := $(shell pkg-config --libs sdl3)

run_objects := $(patsubst %.c,$(OBJDIR)/%.o,$(run_sources))
ppu_debug_objects := $(patsubst %.c,$(OBJDIR)/%.o,$(debug_sources))

$(OBJDIR) $(DEPDIR) $(BINDIR):
	mkdir -p $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEPDIR)/$*.d)
	gcc -o $@ $< -c $(CFLAGS) $(DFLAGS) -MF $(DEPDIR)/$*.d

run: $(run_objects) | $(BINDIR)
	gcc -o $(BINDIR)/$@ $^ $(LDFLAGS)

ppu_debug: $(ppu_debug_objects) | $(BINDIR)
	gcc -o $(BINDIR)/$@ $^ $(LDFLAGS)

deps := $(patsubst %.c,$(DEPDIR)/%.d,$(sources))

clean:
	rm -rf build bin

-include $(deps)

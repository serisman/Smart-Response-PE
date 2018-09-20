# Name: Makefile
# Project: Smart-Response-PE/Hello-World-Clicker
# Author: Stephen Erisman
# Creation Date: 2018-09-17
# License: MIT

# ---------------------------------------------------------------------

DEVICE = CC2430

# ---------------------------------------------------------------------

BUILDDIR = .build
ROMDIR = .rom

COMPILE = sdcc -mmcs51 -D$(DEVICE) --std-c11 --opt-code-speed --xram-loc 0xE000 --xram-size 0x1F00 -I.

SOURCES = $(wildcard lib/*.c) main.c

OBJECTS = $(patsubst %.c,$(BUILDDIR)/%.rel,$(SOURCES))

# symbolic targets:
all: dirs $(ROMDIR)/rom.bin

dirs:
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR)/lib
	mkdir -p $(ROMDIR)

$(BUILDDIR)/%.rel: %.c
	$(COMPILE) -c -o $@ $<

clean-all: clean-build clean-rom
clean-build:
	rm -r -f $(BUILDDIR)
clean-rom:
	rm -r -f $(ROMDIR)

$(ROMDIR)/rom.bin: $(OBJECTS)
	$(COMPILE) --out-fmt-ihx -o $(ROMDIR)/rom.ihx $(OBJECTS)
	makebin $(ROMDIR)/rom.ihx > $(ROMDIR)/rom.bin

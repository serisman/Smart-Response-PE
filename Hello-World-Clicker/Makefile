# Name: Makefile
# Project: Smart-Response-PE/Hello-World-Clicker
# Author: Stephen Erisman
# Creation Date: 2018-09-17
# License: MIT

# ---------------------------------------------------------------------

DEVICE = CC2430

# ---------------------------------------------------------------------

SOURCES = lib/clock.c lib/uart.c lib/num-to-string.c lib/keyboard.c lib/uc1701.c lib/display.c main.c

COMPILE = sdcc -mmcs51 -D$(DEVICE) -DF_CPU=32000000 --std-c11 --max-allocs-per-node 5000 --opt-code-size -I.

OBJECTS = $(SOURCES:.c=.rel)

# symbolic targets:
all:	rom.bin

%.rel: %.c
	$(COMPILE) -c -o $@ $<

clean:
	rm -f *.asm *.lst *.rel *.rst *.sym lib/*.asm lib/*.lst lib/*.rel lib/*.rst lib/*.sym
clean-rom:
	rm -f rom.*

# file targets:
rom.bin: $(OBJECTS)
	$(COMPILE) --out-fmt-ihx -o rom.ihx $(OBJECTS)
	makebin rom.ihx > rom.bin

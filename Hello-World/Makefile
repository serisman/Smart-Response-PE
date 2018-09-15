# Name: Makefile
# Project: Smart-Response-PE/Hello-World
# Author: Stephen Erisman
# Creation Date: 2018-09-14
# License: MIT

# ---------------------------------------------------------------------

DEVICE = CC2430

# ---------------------------------------------------------------------

SOURCES = uart.c clock.c main.c

COMPILE = sdcc -mmcs51 -D$(DEVICE) -DF_CPU=16000000 --std-c11 --max-allocs-per-node 5000 --opt-code-size -I.

OBJECTS = $(SOURCES:.c=.rel)

# symbolic targets:
all:	rom.bin

%.rel: %.c
	$(COMPILE) -c -o $@ $<

clean:
	rm -f *.lib *.rst *.rel *.lst *.ihx *.sym *.asm *.lk *.map
	rm -f rom.*

# file targets:
rom.bin: $(OBJECTS)
	$(COMPILE) --out-fmt-ihx -o rom.ihx $(OBJECTS)
	makebin rom.ihx > rom.bin

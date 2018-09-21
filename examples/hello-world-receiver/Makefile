# Name: Makefile
# Project: Smart-Response-PE/examples/hello-world-receiver
# Author: Stephen Erisman <github@serisman.com>
# Creation Date: 2018-09-14
# License: MIT

# ---------------------------------------------------------------------

DEVICE = CC2430

# ---------------------------------------------------------------------

BIN_DIR = .bin
BUILD_DIR = .build
LIB_DIR = .lib

COMPILE = sdcc -mmcs51 --std-c11 --opt-code-speed --xram-loc 0xE000 --xram-size 0x1F00

LIB_SOURCES = $(wildcard ../../lib/*.c)
LIB_OBJECTS = $(patsubst ../../lib/%.c,$(LIB_DIR)/%.rel,$(LIB_SOURCES))
LIB = $(LIB_DIR)/smart-pe.lib

SOURCES = main.c
OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.rel,$(SOURCES))
ROM_BIN = $(BIN_DIR)/rom.bin

# symbolic targets:
all: $(ROM_BIN)

dirs:
	mkdir -p $(BIN_DIR) $(BUILD_DIR) $(LIB_DIR)

$(BUILD_DIR)/%.rel: %.c
	$(COMPILE) -c -D$(DEVICE) -I. -I../../include -o $@ $<

$(LIB_DIR)/%.rel: ../../lib/%.c
	$(COMPILE) -c -D$(DEVICE) -I. -I../../include -o $@ $<

$(LIB): $(LIB_OBJECTS)
	sdar -rc $@ $(LIB_OBJECTS)

$(ROM_BIN): dirs $(OBJECTS) $(LIB)
	$(COMPILE) --out-fmt-ihx -o $(BIN_DIR)/rom.ihx $(OBJECTS) $(LIB)
	makebin $(BIN_DIR)/rom.ihx > $(ROM_BIN)

print-%: ; @echo $* = $($*)

clean:
	rm -r -f $(BUILD_DIR) $(LIB_DIR)
clean-bin:
	rm -r -f $(BIN_DIR)
clean-all: clean clean-bin

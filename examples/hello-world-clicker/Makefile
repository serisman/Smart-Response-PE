# Name: Makefile
# Project: Smart-Response-PE/examples/hello-world-clicker
# Author: Stephen Erisman <github@serisman.com>
# Creation Date: 2018-09-21
# License: MIT

# ---------------------------------------------------------------------

DEVICE = CC2430

# ---------------------------------------------------------------------

ROOT_DIR = ../..
BUILD_DIR = .build

LIB_SOURCES = $(wildcard $(ROOT_DIR)/lib/*.c) $(wildcard $(ROOT_DIR)/lib/**/*.c)
LIB_OBJECTS = $(patsubst $(ROOT_DIR)/lib/%.c,$(BUILD_DIR)/lib/%.rel,$(LIB_SOURCES))

SOURCES = main.c
OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.rel,$(SOURCES))

COMPILE = sdcc -mmcs51 -c --std-c11 --opt-code-speed -D$(DEVICE) -I. -I$(ROOT_DIR)/include
BUILD_LIB = sdar -rc
LINK = sdcc -mmcs51 --xram-loc 0xE000 --xram-size 0x1F00

# symbolic targets:
all: rom.bin

print-%: ; @echo $* = $($*)

$(BUILD_DIR)/%.rel: %.c
	@mkdir -p $(dir $@)
	$(COMPILE) -o $@ $<

$(BUILD_DIR)/lib/%.rel: $(ROOT_DIR)/lib/%.c
	@mkdir -p $(dir $@)
	$(COMPILE) -o $@ $<

$(BUILD_DIR)/lib.lib: $(LIB_OBJECTS)
	$(BUILD_LIB) $@ $(LIB_OBJECTS)

$(BUILD_DIR)/rom.ihx: $(OBJECTS) $(BUILD_DIR)/lib.lib
	@mkdir -p $(dir $(BUILD_DIR))
	$(LINK) --out-fmt-ihx -o $(BUILD_DIR)/rom.ihx $(OBJECTS) $(BUILD_DIR)/lib.lib

rom.bin: $(BUILD_DIR)/rom.ihx
	makebin $(BUILD_DIR)/rom.ihx > rom.bin

clean:
	rm -r -f $(BUILD_DIR)


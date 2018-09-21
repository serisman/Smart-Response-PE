# Name: Makefile
# Project: Smart-Response-PE/examples/hello-world-receiver
# Author: Stephen Erisman <github@serisman.com>
# Creation Date: 2018-09-14
# License: MIT

# ---------------------------------------------------------------------

DEVICE = CC2430

# ---------------------------------------------------------------------

ROOT_DIR = ../../
BIN_DIR = .bin
BUILD_DIR = .build
LIB_DIR = .lib

COMPILE = sdcc -mmcs51 --std-c11 --opt-code-speed --xram-loc 0xE000 --xram-size 0x1F00

LIB_SOURCES = $(wildcard $(ROOT_DIR)/lib/*.c) $(wildcard $(ROOT_DIR)/lib/**/*.c)
LIB_OBJECTS = $(patsubst $(ROOT_DIR)/lib/%.c,$(LIB_DIR)/%.rel,$(LIB_SOURCES))
LIB = $(LIB_DIR)/smart-pe.lib

SOURCES = main.c
OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.rel,$(SOURCES))
ROM_BIN = $(BIN_DIR)/rom.bin

# symbolic targets:
all: $(ROM_BIN)

$(BUILD_DIR)/%.rel: %.c
	@mkdir -p $(dir $@)
	$(COMPILE) -c -D$(DEVICE) -I. -I$(ROOT_DIR)include -o $@ $<

$(LIB_DIR)/%.rel: $(ROOT_DIR)/lib/%.c
	@mkdir -p $(dir $@)
	$(COMPILE) -c -D$(DEVICE) -I. -I$(ROOT_DIR)include -o $@ $<

$(LIB): $(LIB_OBJECTS)
	sdar -rc $@ $(LIB_OBJECTS)

$(ROM_BIN): $(OBJECTS) $(LIB)
	@mkdir -p $(dir ROM_BIN)
	$(COMPILE) --out-fmt-ihx -o $(BIN_DIR)/rom.ihx $(OBJECTS) $(LIB)
	makebin $(BIN_DIR)/rom.ihx > $(ROM_BIN)

print-%: ; @echo $* = $($*)

clean:
	rm -r -f $(BUILD_DIR) $(LIB_DIR)
clean-bin:
	rm -r -f $(BIN_DIR)
clean-all: clean clean-bin

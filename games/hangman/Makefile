# Name: Makefile
# Project: Smart-Response-PE/games/hangman
# Author: Stephen Erisman <github@serisman.com>
# Creation Date: 2018-09-22
# License: MIT

# ---------------------------------------------------------------------

DEVICE = CC2430
#DEVICE = CC2533
F_CPU = 32000000

# ---------------------------------------------------------------------

OUTPUT_NAME = Hangman

ifeq ($(DEVICE), CC2430)
  XRAM_LOC = 0xE000
  XRAM_SIZE = 0x1F00
else ifeq ($(DEVICE), CC2533)
  XRAM_LOC = 0x0000
  XRAM_SIZE = 0x0F00
endif

ROOT_DIR = ../..
BUILD_DIR = .build
OUTPUT_DIR = .output

OUTPUT = $(OUTPUT_DIR)/$(OUTPUT_NAME)

LIB_SOURCES = $(wildcard $(ROOT_DIR)/lib/*.c) $(wildcard $(ROOT_DIR)/lib/**/*.c)
LIB_OBJECTS = $(patsubst $(ROOT_DIR)/lib/%.c,$(BUILD_DIR)/lib/%.rel,$(LIB_SOURCES))

SOURCES = main.c
OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.rel,$(SOURCES))

# http://sdcc.sourceforge.net/doc/sdccman.pdf
COMPILE = sdcc -mmcs51 -c --std-sdcc11 --opt-code-size -D$(DEVICE) -DF_CPU=$(F_CPU) -I. -I$(ROOT_DIR)/include
BUILD_LIB = sdar -rc
LINK = sdcc -mmcs51 --xram-loc $(XRAM_LOC) --xram-size $(XRAM_SIZE)

# symbolic targets:
all: size

print-%: ; @echo $* = $($*)

$(BUILD_DIR)/%.rel: %.c
	@mkdir -p $(dir $@)
	$(COMPILE) -o $@ $<

$(BUILD_DIR)/lib/%.rel: $(ROOT_DIR)/lib/%.c
	@mkdir -p $(dir $@)
	$(COMPILE) -o $@ $<

$(BUILD_DIR)/lib.lib: $(LIB_OBJECTS)
	$(BUILD_LIB) $@ $(LIB_OBJECTS)

$(OUTPUT).ihx: $(OBJECTS) $(BUILD_DIR)/lib.lib
	@mkdir -p $(dir $@)
	$(LINK) --out-fmt-ihx -o $(OUTPUT).ihx $(OBJECTS) $(BUILD_DIR)/lib.lib

$(OUTPUT).hex: $(OUTPUT).ihx
	packihx $(OUTPUT).ihx > $(OUTPUT).hex

$(OUTPUT).bin: $(OUTPUT).ihx
	makebin $(OUTPUT).ihx > $(OUTPUT).bin

size: $(OUTPUT).bin
	@echo '---------- Segments ----------'
	@egrep '(ABS,CON)|(REL,CON)' $(OUTPUT).map | gawk --non-decimal-data '{dec = sprintf("%d","0x" $$2); print dec " " $$0}' | /usr/bin/sort -n -k1 | cut -f2- -d' ' | uniq
	@echo '---------- Memory ----------'
	@egrep 'available|EXTERNAL|FLASH' $(OUTPUT).mem

clean:
	rm -r -f $(BUILD_DIR) $(OUTPUT_DIR)

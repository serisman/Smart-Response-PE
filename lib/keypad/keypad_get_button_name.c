// Name: keypad/keypad_get_button_name.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "util.h"
#include "keypad.h"

const char __code *_button_names[5][4] = {
	{"Enter",	"T/Y",	"F/N",	"del"},
	{"?",			"A/1",	"B/2",	"C/3"},
	{"Menu",	"D/4",	"E/5",	"F/6"},
	{"Up",		"G/7",	"H/8",	"I/9"},
	{"Down",	"+/-",	"J/0",	"xy/."}
};

const char __code *keypad_get_button_name(uint8_t col, uint8_t mask) {
	uint8_t row;
	if (col == ARG1(BUTTON_PWR) && mask == ARG2(BUTTON_PWR))
		return "PWR";
	row = util_mask_to_bit(mask);
	return _button_names[row][col];
}

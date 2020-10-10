// Name: keypad.h
// Project: Smart-Response-PE/include
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#ifndef __keypad_h_included__
#define __keypad_h_included__

#include "util.h"

#define BUTTON_PWR					0,BV(7)
#define BUTTON_ENTER				0,BV(0)
#define BUTTON_QUESTION			0,BV(1)
#define BUTTON_MENU					0,BV(2)
#define BUTTON_UP						0,BV(3)
#define BUTTON_DOWN					0,BV(4)
#define BUTTON_T_Y					1,BV(0)
#define BUTTON_A_1					1,BV(1)
#define BUTTON_D_4					1,BV(2)
#define BUTTON_G_7					1,BV(3)
#define BUTTON_PLUS_MINUS		1,BV(4)
#define BUTTON_F_N					2,BV(0)
#define BUTTON_B_2					2,BV(1)
#define BUTTON_E_5					2,BV(2)
#define BUTTON_H_8					2,BV(3)
#define BUTTON_J_0					2,BV(4)
#define BUTTON_DEL					3,BV(0)
#define BUTTON_C_3					3,BV(1)
#define BUTTON_F_6					3,BV(2)
#define BUTTON_I_9					3,BV(3)
#define BUTTON_X_Y_PERIOD		3,BV(4)

extern uint8_t keypad_keymap_0;
extern uint8_t keypad_keymap_1;
extern uint8_t keypad_keymap_2;
extern uint8_t keypad_keymap_3;

extern uint8_t __xdata keypad_previous_keymap_0;
extern uint8_t __xdata keypad_previous_keymap_1;
extern uint8_t __xdata keypad_previous_keymap_2;
extern uint8_t __xdata keypad_previous_keymap_3;

void keypad_scan();
uint8_t keypad_get_keymap(uint8_t col);
bool keypad_any_pressed();
bool keypad_pressed(uint8_t col, uint8_t mask);
const char __code *keypad_get_button_name(uint8_t col, uint8_t mask);

void keypad_poll();
bool keypad_changed();
uint8_t __xdata keypad_get_previous_keymap(uint8_t col);
bool keypad_just_pressed(uint8_t col, uint8_t mask);
bool keypad_just_released(uint8_t col, uint8_t mask);

#endif /* __keypad_h_included__ */

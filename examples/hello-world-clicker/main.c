// Name: main.c
// Project: Smart-Response-PE/examples/hello-world-clicker
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "hal.h"
#include "util.h"
#include "string_utils.h"
#include "clock.h"
#include "uart.h"
#include "display.h"
#include "keypad.h"

#include "bitmaps.h"

#define FPS                 30u

char __xdata str_buf[12];

uint32_t __xdata prev_millis = 0;

int8_t __xdata scroll_x = 0;
int8_t __xdata scroll_x_dir = 1;

int8_t __xdata scroll_y = 0;
int8_t __xdata scroll_y_dir = 1;

void setup() {
  uart_init();
  uart_println("Hello World!");

  display_init();
  display_set_frame_rate(FPS);
}

void loop() {
  uint32_t millis;

  // Wait until its time to render our next frame
  if (!display_next_frame())
    return;

  // Send current millis() value to the UART
  millis = clock_millis();
  u32_to_str(str_buf, millis);
  if (millis-prev_millis >= 1000) {
    uart_print("millis: "); uart_println(str_buf);
    prev_millis += 1000;
  }

  // Poll the keypad (disable/enable UART to reduce shared pin conflicts)
  uart_disable();
  keypad_poll();
  uart_enable();

  // Send the keypad keymaps to the UART (if it changed)
  if (keypad_changed()) {
    uart_print("keymap: ");
    for (uint8_t i=0; i<4; i++) {
      u8_to_bin_str(str_buf, keypad_get_keymap(i), 5);
      uart_print(str_buf); uart_print(" ");
    }
    uart_println("");
  }

  // Send the name of any just pressed/released buttons to the UART
  for (uint8_t col=0; col<4; col++) {
    for (uint8_t row=0; row<8; row++) {
      uint8_t mask = util_bit_to_mask[row];
      if (keypad_just_pressed(col, mask)) {
        uart_print("key pressed: "); uart_println(keypad_get_button_name(col, mask));
      }
      if (keypad_just_released(col, mask)) {
        uart_print("key released: "); uart_println(keypad_get_button_name(col, mask));
      }
    }
  }

  // Scroll the Smart logo bitmap horizontally
  display_draw_bitmap(bmp_smart_logo, scroll_x, 0, 60, 16);
  scroll_x += scroll_x_dir;
  if (scroll_x + (uint8_t)60 > SCREEN_WIDTH-35 || scroll_x + (uint8_t)(60/2) < 0) {
    scroll_x_dir = (uint8_t)0- scroll_x_dir;
  }

  // Scroll the wolf bitmap vertically
  display_draw_bitmap(bmp_wolf, SCREEN_WIDTH-35, scroll_y, 35, 48);
  scroll_y += scroll_y_dir;
  if (scroll_y + (uint8_t)(48/2) > SCREEN_HEIGHT || scroll_y + (uint8_t)(48/2) < 0) {
    scroll_y_dir = (uint8_t)0- scroll_y_dir;
  }

  // Display Hello World!
  display_set_cursor(3,17);
  display_print("Hello World!");

  if (!keypad_any_pressed()) {
    // Display the current millis() value
    display_set_cursor(3,25);
    u32_to_str(str_buf, millis);
    display_print(str_buf); display_print(" ms.");
  } else {
    // Display the name of any currently pressed buttons
    for (uint8_t col=0; col<4; col++) {
      for (uint8_t row=0; row<8; row++) {
        uint8_t mask = util_bit_to_mask[row];
        if (keypad_pressed(col, mask)) {
          display_set_cursor(3,25);
          display_print(keypad_get_button_name(col, mask));
          display_print(" pressed!");
        }
      }
    }

    // Display the keypad keymaps
    display_set_cursor(12,33);
    for (uint8_t i=0; i<4; i++) {
      u8_to_bin_str(str_buf, keypad_get_keymap(i), 5);
      display_print(str_buf); display_print((i==1) ? "\r\n\t" : " ");
    }
  }

  // Invert the screen if the Enter button was just pressed
  if (keypad_just_pressed(BUTTON_ENTER)) {
    display_invert(true);
  }
  // Revert the screen if the Enter button was just released
  if (keypad_just_released(BUTTON_ENTER)) {
    display_invert(false);
  }

  // Paint the screen buffer to the LCD
  display_paint();
}

void main() {
  oscillator_32mhz();
  clock_init();
  ENABLE_INTERRUPTS;
  setup();

  while (1) {
    loop();
  }
}

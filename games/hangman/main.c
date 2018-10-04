// Name: main.c
// Project: Smart-Response-PE/games/hangman
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-22
// License: MIT
//
// This is a port of the Arduboy version found here: https://github.com/serisman/arduboy-hangman

//#define DEBUG 1

#include <stdlib.h>

#include "hal.h"
#include "util.h"
#include "string_utils.h"
#include "clock.h"
#include "display.h"
#include "keypad.h"
#include "eeprom.h"

#include "words.h"

#define UP_BUTTON     BUTTON_UP
#define DOWN_BUTTON   BUTTON_DOWN
#define LEFT_BUTTON   BUTTON_T_Y
#define RIGHT_BUTTON  BUTTON_F_N
#define A_BUTTON      BUTTON_MENU
#define B_BUTTON      BUTTON_QUESTION

#define MODE_TITLE    0
#define MODE_STATS    1
#define MODE_PLAY     2
#define MODE_CORRECT  4
#define MODE_DEAD     5

#define EEPROM_BASE_ADDR      72
#define EEPROM_WINS_ADDR      EEPROM_BASE_ADDR + 2
#define EEPROM_LOSSES_ADDR    EEPROM_BASE_ADDR + 3

uint8_t mode = MODE_TITLE;
bool paused = false;

uint8_t wins = 0;
uint8_t losses = 0;
uint8_t hangman = 0;
uint16_t previousWordIndex = 0xFFFF;
char __xdata currentWord[9];
uint8_t cursor = 0;
uint8_t cursorBlink = 0;
uint8_t __xdata usedLetters[26];

char __xdata buf[30];

void showTitle(uint8_t cur);
void moveCursor(uint8_t num);
void nextTitleFrame();
void drawLogo();
void drawTitleMenu();
void drawMenuCursor(uint8_t num);
void showStats();
void nextStatsFrame();
void resetStats();
void drawStats();
void drawStatsMenu();
void startPlaying();
void nextPlayFrame();
void nextCorrectFrame();
void nextDeadFrame();
void drawScore();
void drawHangman();
void drawWord();
void drawKeyboard();
void drawCorrect();
void drawDead();
void scoreResponse(char letter);
void pickAWord();

inline void setup() {
  display_init();
  display_set_frame_rate(30);

  if (eeprom_read_byte(EEPROM_BASE_ADDR) == 'H' && eeprom_read_byte(EEPROM_BASE_ADDR + 1) == 'M') {
    wins = eeprom_read_byte(EEPROM_WINS_ADDR);
    losses = eeprom_read_byte(EEPROM_LOSSES_ADDR);
  } else {
    eeprom_write_byte(EEPROM_BASE_ADDR, 'H');
    eeprom_write_byte(EEPROM_BASE_ADDR + 1, 'M');
    eeprom_write_byte(EEPROM_WINS_ADDR, wins);
    eeprom_write_byte(EEPROM_LOSSES_ADDR, losses);
  }
}

inline void loop() {
  if (display_next_frame()) {
    keypad_poll();
    switch (mode) {
      case MODE_TITLE:    nextTitleFrame();   break;
      case MODE_STATS:    nextStatsFrame();   break;
      case MODE_PLAY:     nextPlayFrame();    break;
      case MODE_CORRECT:  nextCorrectFrame(); break;
      case MODE_DEAD:     nextDeadFrame();    break;
    }
    display_paint();
  }
}

void showTitle(uint8_t cur) {
  mode = MODE_TITLE;
  cursor = cur;
}

void moveCursor(uint8_t num) {
  if (keypad_just_pressed(UP_BUTTON)) {
    if (cursor > 0) cursor --;
  } else if (keypad_just_pressed(DOWN_BUTTON)) {
    if (cursor < (num-1)) cursor ++;
  }
}

void nextTitleFrame() {
  moveCursor(2);

  if (keypad_just_pressed(A_BUTTON)) {
    if (cursor == 0)
      startPlaying();
    else if (cursor == 1)
      showStats();
    return;
  }

  if (!paused && display_every_x_frames(10)) {
    if (hangman < 6) hangman++;
    else hangman = 0;
  }

  drawLogo();
  drawTitleMenu();
  drawHangman();
}

void drawLogo() {
  display_set_cursor(0,0);
  display_print("HANGMAN!");
  display_draw_fast_hline(0,9,45, COLOR_BLACK);
  display_set_cursor(0,12);
  display_print(" by serisman");
}

void drawTitleMenu() {
  display_set_cursor(10,48-(8*2));
  if (paused)
    display_print("Resume");
  else
    display_print("Start");

  display_set_cursor(10,48-(8*1));
  display_print("Stats");

  drawMenuCursor(2);
}

void drawMenuCursor(uint8_t num) {
  display_set_cursor(2,48-(8*num)+(cursor*8));
  display_print(">");
}

void showStats() {
  mode = MODE_STATS;
  cursor = 1;
}

void nextStatsFrame() {
  moveCursor(2);

  if (keypad_just_pressed(A_BUTTON)) {
    if (cursor == 0)
      resetStats();
    else if (cursor == 1)
      showTitle(1);
    return;
  }

  if (keypad_just_pressed(B_BUTTON)) {
    showTitle(1);
    return;
  }

  if (!paused && display_every_x_frames(10)) {
    if (hangman < 6) hangman++;
    else hangman = 0;
  }

  drawStats();
  drawStatsMenu();
  drawHangman();
}

void resetStats() {
  wins = 0;
  losses = 0;
  eeprom_write_byte(EEPROM_WINS_ADDR, wins);
  eeprom_write_byte(EEPROM_LOSSES_ADDR, losses);
}

void drawStats() {
  char __xdata *ptr = buf;

  // sprintf_P(buf, PSTR(" %u Wins\n %u Losses"), wins, losses);
  *ptr++ = ' ';
  u8_to_str(wins, ptr); while (*ptr) ptr++;
  str_to_str(" Wins\r\n ", ptr); while (*ptr) ptr++;
  u8_to_str(losses, ptr); while (*ptr) ptr++;
  str_to_str(" Losses", ptr); // while (*ptr) ptr++;

  display_set_cursor(0,10);
  display_print(buf);
}

void drawStatsMenu() {
  display_set_cursor(10,48-(8*2));
  display_print("Reset");

  display_set_cursor(10,48-(8*1));
  display_print("Back");

  drawMenuCursor(2);
}

void startPlaying() {
  if (!paused) {
    pickAWord();
    hangman = 0;

    clear_str(usedLetters, sizeof(usedLetters));
  }
  paused = false;
  cursor = 0;
  mode = MODE_PLAY;
}

void nextPlayFrame() {
  if (keypad_just_pressed(RIGHT_BUTTON)) {
    if (cursor == 25) cursor = 0;
    else cursor++;
  }
  if (keypad_just_pressed(LEFT_BUTTON)) {
    if (cursor == 0) cursor = 25;
    else cursor--;
  }
  if (keypad_just_pressed(UP_BUTTON)) {
    if (cursor > 8) cursor -= 9;
  }
  if (keypad_just_pressed(DOWN_BUTTON)) {
    if (cursor < (26-9)) cursor += 9;
  }

  if (keypad_just_pressed(A_BUTTON)) {
    if (usedLetters[cursor] == 0) {
      usedLetters[cursor] = 1;
      scoreResponse(cursor+65);
    }
  }

#ifdef DEBUG
  if (keypad_just_pressed(B_BUTTON)) { // For easier testing...
    startPlaying();
    return;
  }
#endif

  if (keypad_just_pressed(B_BUTTON)) {
    paused = true;
    showTitle(0);
    return;
  }

  if (display_every_x_frames(10)) {
    cursorBlink = 1-cursorBlink;
  }

  drawScore();
  drawHangman();
  drawWord();
  drawKeyboard();
}

void nextCorrectFrame() {
  if (keypad_just_pressed(A_BUTTON)) {
    startPlaying();
    return;
  }
  if (keypad_just_pressed(B_BUTTON)) {
    showTitle(0);
    return;
  }

  drawScore();
  drawHangman();
  drawWord();
  drawCorrect();
}

void nextDeadFrame() {
  if (keypad_just_pressed(A_BUTTON)) {
    startPlaying();
    return;
  }
  if (keypad_just_pressed(B_BUTTON)) {
    showTitle(0);
    return;
  }

  drawScore();
  drawHangman();
  drawWord();
  drawDead();
}

void drawScore() {
  uint8_t __xdata *ptr = buf;

  // sprintf_P(buf, PSTR("%uW-%uL"), wins, losses);
  u8_to_str(wins, ptr);  while (*ptr) ptr++;
  *ptr++ = 'W';
  *ptr++ = '-';
  u8_to_str(losses, ptr);  while (*ptr) ptr++;
  *ptr++ = 'L';
  *ptr = 0;

  //display_set_cursor((128-50)-(strlen(buf)*6),0);
  display_set_cursor((128-50)-((ptr-buf)*6),0);
  display_print(buf);
}

void drawHangman() {
  const uint8_t LEFT = (128-45);
  // width: 50
  // height: 48

  display_fill_rect(LEFT+5, 45, 40, 3, COLOR_BLACK); // ground
  display_fill_rect(LEFT+30, 0, 3, 48, COLOR_BLACK); // post
  display_fill_rect(LEFT+10, 0, 20, 3, COLOR_BLACK); // bar
  display_fill_rect(LEFT+10, 0, 3, 8, COLOR_BLACK); // noose

  if (hangman > 0)	// head
    display_draw_circle(LEFT+11, 11, 4, COLOR_BLACK);
  if (hangman > 1)	// body
    display_draw_fast_vline(LEFT+11, 15, 15, COLOR_BLACK);
  if (hangman > 2)	// left arm
    display_draw_line(LEFT+0, 16, LEFT+11, 19, COLOR_BLACK);
  if (hangman > 3)	// right arm
    display_draw_line(LEFT+22, 16, LEFT+11, 19, COLOR_BLACK);
  if (hangman > 4)	// left leg
    display_draw_line(LEFT+0, 39, LEFT+11, 30, COLOR_BLACK);
  if (hangman > 5)	// right leg
    display_draw_line(LEFT+22, 39, LEFT+11, 30, COLOR_BLACK);

  if (paused) {
    display_set_cursor(LEFT+7,48/2-4);
    display_print("Paused");
  }
}

void drawWord() {
  char __xdata *ptr = currentWord;
  uint8_t x = 2;
  const uint8_t y = 9;

#ifdef DEBUG
  display_set_cursor(0,0);
  display_print(currentWord); // for easier testing...
#endif

  while (*ptr) {
    uint8_t letter = *ptr;
    if (usedLetters[letter-65] == 1) {
      display_set_cursor(x, y);
      display_draw_char(letter);
    } else {
      if (mode == MODE_DEAD) {
        display_set_cursor(x, y);
        display_draw_char(letter+32); // be nice and show the correct answer
      }
      display_draw_fast_hline(x-1, y+7, 7, COLOR_BLACK); //y+9
    }
    x += 9;
    ptr++;
  }
}

void drawKeyboard() {
  uint8_t x = 2;
  uint8_t y = 12;
  for (uint8_t chr=0; chr<26; chr++) {
    if (chr % 9 == 0) {
      x = 2;
      y += 9;
    } else {
      x += 9;
    }

    display_set_cursor(x, y);
    if (usedLetters[chr] == 0) {
      display_draw_char(chr+65);
    } else {
      display_draw_char(chr+97); // use lower case for already used letters
    }

    if (cursor == chr && cursorBlink) {
      display_draw_fast_hline(x-1, y+7, 7, COLOR_BLACK); // y+8
    }
  }
}

void drawCorrect() {
  display_set_cursor(2,35);
  display_print("YOU GOT IT!");
}

void drawDead() {
  display_set_cursor(2,35);
  display_print("YOU'RE DEAD!");
}

void scoreResponse(char letter) {
  bool allDone = true;
  bool letterOk = false;
  char __xdata *ptr = currentWord;
  while (*ptr) {
    char wordLetter = *ptr;
    if (usedLetters[wordLetter-65] == 0)
      allDone = false;
    if (wordLetter == letter)
      letterOk = true;
    ptr++;
  }

  if (allDone) {
    // sound.tones(soundWin);
    mode = MODE_CORRECT;
    wins++;
    eeprom_write_byte(EEPROM_WINS_ADDR, wins);
  //} else if (letterOk) {
    // sound.tones(soundCorrect);
  } else if (!letterOk) {
    hangman++;
    if (hangman == 6) {
      // sound.tones(soundDead);
      mode = MODE_DEAD;
      losses++;
      eeprom_write_byte(EEPROM_LOSSES_ADDR, losses);
    //} else {
      // sound.tones(soundIncorrect);
    }
  }
}

void pickAWord() {
  uint16_t newWordIndex;
  uint8_t wordCount;
  uint8_t __code *word_ptr = WORDS;

  srand(clock_millis());
  do {
    newWordIndex = rand() % WORD_COUNT;
  } while (newWordIndex == previousWordIndex);
  previousWordIndex = newWordIndex;

  for (uint8_t wordLen=2; wordLen<=8; wordLen++) {
    wordCount = WORD_COUNTS[wordLen];
    if (newWordIndex < wordCount) {
      clear_str(currentWord, sizeof(currentWord));
      word_ptr += (newWordIndex * (uint16_t)wordLen);
      for (uint8_t i=0; i<wordLen; i++, word_ptr++) {
        currentWord[i] = *word_ptr;
      }
      return;
    }
    newWordIndex -= wordCount;
    word_ptr += ((uint16_t)wordCount * (uint16_t)wordLen);
  }
}

void main() {
  oscillator_32mhz();
  clock_init();
  ENABLE_INTERRUPTS;
  setup();

  while(1) {
    loop();
  }
}

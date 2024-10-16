#ifndef MESSAGE_H
#define MESSAGE_H

#include "../fonts/font5x7_1.h"
#include "system.h"
#include "tinygl.h"

#define PACER_RATE 500  // pacer ticks per second
#define MESSAGE_RATE 20 // characters per 10 seconds

uint32_t message_calculate_scrolling_message_ticks(const char* text);

void message_scrolling_message(const char* text);

void message_char(char character);

void message_init(void);

void message_display_board(const tinygl_pixel_value_t board[LEDMAT_ROWS_NUM][LEDMAT_COLS_NUM]);

#endif

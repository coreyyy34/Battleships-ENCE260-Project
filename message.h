#ifndef MESSAGE_H
#define MESSAGE_H

#include "../fonts/font5x7_1.h"
#include "system.h"
#include "board.h"

#define PACER_RATE 500  // pacer ticks per second
#define MESSAGE_RATE 20 // characters per 10 seconds
#define PIXEL_ON 1
#define PIXEL_OFF 0

#define MESSAGE_HIT " HIT "
#define MESSAGE_MISS " MISS "

uint32_t message_calculate_scrolling_message_ticks(const char* text);

void message_scrolling_message(const char* text);

void message_char(char character);

void message_init(void);

void message_display_pre_defined_board(const PredefinedBoard_t* board);

void message_display_board(Board_t* board);

void message_display_pixel(uint8_t col, uint8_t row, tinygl_pixel_value_t value);

void message_clear(void);

#endif

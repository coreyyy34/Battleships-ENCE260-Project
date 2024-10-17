#include <stdint.h>
#include <string.h>
#include "message.h"
#include "system.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

#define MESSAGE_RATE 20
#define PACER_RATE 500

uint32_t message_calculate_scrolling_message_ticks(const char* text)
{
    uint8_t message_len = strlen(text);
    uint8_t message_cols = message_len * FONT5X7_1_WIDTH + message_len - 1;
    float cols_per_second = (MESSAGE_RATE / 10.0f) * FONT5X7_1_WIDTH;
    float cols_per_tick = cols_per_second / PACER_RATE;
    return (uint32_t) (message_cols / cols_per_tick);
}

void message_scrolling_message(const char* text)
{
    message_init();
    tinygl_clear();
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(text);
}

void message_init(void)
{
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
}

void message_display_pre_defined_board(const PredefinedBoard_t* board)
{
    message_init();
    tinygl_clear();
    for (tinygl_coord_t row = 0; row < LEDMAT_ROWS_NUM; row++)
    {
        uint8_t row_data = (*board)[row];  // Get the packed row
        for (tinygl_coord_t col = 0; col < LEDMAT_COLS_NUM; col++)
        {
            tinygl_point_t pos = {col, row};
            // Extract each bit from the row (shift right and mask)
            uint8_t pixel_on = (row_data >> (LEDMAT_COLS_NUM - 1 - col)) & 1;
            tinygl_pixel_set(pos, pixel_on);
        }
    }
}

void message_display_pixel(uint8_t col, uint8_t row, tinygl_pixel_value_t value)
{
    tinygl_point_t pos = {col, row};
    tinygl_pixel_set(pos, value);
}

void message_clear(void)
{
    message_init();
    tinygl_clear();
}

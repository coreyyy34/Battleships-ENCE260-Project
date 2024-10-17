/** @file   screen.c
 *  @author Corey Hines
 *  @date   17/10/2024
 */

#include <string.h>
#include "screen.h"
#include "game.h"   /* For PACER_RATE */

static uint32_t scrolling_message_ticks = 0;
static bool scrolling_message_active = false;

/**
 * @brief Calculates the number of ticks required to scroll a message.
 * @param text The message text to be scrolled.
 * @return The calculated number of ticks for scrolling the message.
 */
static uint32_t screen_calculate_scrolling_message_ticks(const char* text)
{
    uint8_t message_len = strlen(text);
    uint8_t message_cols = message_len * FONT5X7_1_WIDTH + message_len - 1;
    float cols_per_second = (MESSAGE_RATE / 10.0f) * FONT5X7_1_WIDTH;
    float cols_per_tick = cols_per_second / PACER_RATE;
    return (uint32_t) (message_cols / cols_per_tick);
}

bool screen_scrolling_message_active(void)
{
    return scrolling_message_active;
}

void screen_set_scrolling_text(const char* text)
{
    screen_clear();  // Clear the screen before setting a new message.
    scrolling_message_active = true;
    scrolling_message_ticks = screen_calculate_scrolling_message_ticks(text);
    screen_init();  // Reinitialize to ensure clean state.
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(text);
}

void screen_set_char(char character)
{
    char text[2] = {character, '\0'}; 
    screen_clear();
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    tinygl_text(text);
}

void screen_set_predefined_board(const PredefinedBoard_t* board)
{
    screen_clear();
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

void screen_set_pixel(uint8_t col, uint8_t row, tinygl_pixel_value_t value)
{
    tinygl_point_t pos = {col, row};
    tinygl_pixel_set(pos, value);
}

void screen_scrolling_message_update(void)
{
    if (scrolling_message_ticks > 0) {
        scrolling_message_ticks--;
    } else {
        scrolling_message_ticks = 0;
        scrolling_message_active = false;  // Ensure the message is no longer active once it finishes.
        screen_clear();
    }
}

void screen_update(void)
{
    tinygl_update();
}

void screen_clear(void)
{
    screen_init();
    tinygl_clear();
}

void screen_init(void)
{
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
}
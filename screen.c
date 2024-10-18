/** 
 * @file   screen.c
 * @brief  Implementation of the screen functions for the LED matrix display.
 * 
 * This file contains the function implementations for managing and updating the
 * LED matrix display, including displaying scrolling messages, single characters,
 * predefined boards, and individual pixels.
 * 
 * @date   17/10/2024
 * @author Corey Hines
 */


#include <string.h>
#include "screen.h"
#include "game.h"   /* For PACER_RATE */

/** @brief Number of ticks remaining for an active scrolling message. */
static uint32_t scrolling_message_ticks = 0;

/** @brief Flag indicating if a scrolling message is active. */
static bool scrolling_message_active = false;

/**
 * @brief Calculates the number of ticks required to scroll a message.
 * 
 * This function calculates the number of ticks required to scroll a message
 * based on the message length and the configured message rate.
 * 
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

/**
 * @brief Calculates the number of ticks required to scroll a message.
 * 
 * This function calculates the number of ticks required to scroll a message
 * based on the message length and the configured message rate.
 * 
 * @param text The message text to be scrolled.
 * @return The calculated number of ticks for scrolling the message.
 */
bool screen_scrolling_message_active(void)
{
    return scrolling_message_active;
}

/**
 * @brief Sets the scrolling message to be displayed on the screen.
 * 
 * This function sets a new scrolling message to be displayed on the screen.
 * It clears the screen, calculates the required ticks, and initializes the
 * scrolling message display.
 * 
 * @param text The message to be displayed.
 */
void screen_set_scrolling_text(const char* text)
{
    screen_clear();  // Clear the screen before setting a new message.
    scrolling_message_active = true;
    scrolling_message_ticks = screen_calculate_scrolling_message_ticks(text);
    screen_init();  // Reinitialize to ensure clean state.
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(text);
}

/**
 * @brief Displays a single character on the screen.
 * 
 * This function displays a single character on the screen in step mode.
 * 
 * @param character The character to be displayed.
 */
void screen_set_char(char character)
{
    char text[2] = {character, '\0'}; 
    screen_clear();
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    tinygl_text(text);
}

/**
 * @brief Displays a predefined board layout on the LED matrix.
 * 
 * This function displays a predefined board layout on the LED matrix by iterating
 * through the rows and columns of the board and setting the corresponding pixels.
 * 
 * @param board A pointer to the predefined board structure.
 */
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

/**
 * @brief Sets a pixel on the LED matrix to the specified value.
 * 
 * This function sets a specific pixel on the LED matrix to the given value
 * (on or off).
 * 
 * @param col The column index of the pixel.
 * @param row The row index of the pixel.
 * @param value The pixel value (on or off).
 */
void screen_set_pixel(uint8_t col, uint8_t row, tinygl_pixel_value_t value)
{
    tinygl_point_t pos = {col, row};
    tinygl_pixel_set(pos, value);
}

/**
 * @brief Updates the scrolling message display.
 * 
 * This function updates the state of the scrolling message display, decreasing
 * the tick count and checking if the message has finished scrolling.
 */
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

/**
 * @brief Updates the LED matrix display.
 * 
 * This function updates the LED matrix including the internal state of a scrolling
 * message which is handled in the tinygl module.
 */
void screen_update(void)
{
    tinygl_update();
}

/**
 * @brief Clears the LED matrix, removing all displayed content.
 * 
 * This function clears the LED matrix, removing any content that is currently
 * displayed.
 */
void screen_clear(void)
{
    screen_init();
    tinygl_clear();
}

/**
 * @brief Clears the LED matrix, removing all displayed content.
 * 
 * This function clears the LED matrix, removing any content that is currently
 * displayed.
 */
void screen_init(void)
{
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
}
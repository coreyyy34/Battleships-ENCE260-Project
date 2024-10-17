/** @file   screen.h
 *  @author Corey Hines
 *  @date   17/10/2024
 */

#ifndef SCREEN_H
#define SCREEN_H

#include "../fonts/font5x7_1.h"
#include "system.h"
#include "board.h"

#define MESSAGE_RATE 20 // Characters to display every 10 seconds

// LED states for the UCFK LED mat which is in an active low configuration
#define PIXEL_ON 1  // Value representing a pixel that is turned on
#define PIXEL_OFF 0 // Value representing a pixel that is turned off

#define MESSAGE_HIT " HIT "         // Message displayed for a hit
#define MESSAGE_MISS " MISS "       // Message displayed for a miss
#define MESSAGE_WINNER " YOU WON! " // Message displayed when the player wins
#define MESSAGE_LOSER " YOU LOST! " // Message displayed when the player loses

bool screen_scrolling_message_active(void);

/**
 * @brief Updates the LED matrix display. This should be called regularly to refresh the screen.
 */
void screen_update(void);

/**
 * @brief Clears the LED matrix, removing all displayed content.
 */
void screen_clear(void);

/**
 * @brief Initializes the screen, setting up the tiny gl library and font settings.
 */
void screen_init(void);

/**
 * @brief Sets the scrolling message to be displayed on the screen.
 * @param text The message to be displayed.
 */
void screen_set_scrolling_text(const char* text);

/**
 * @brief Displays a single character on the screen.
 * @param character The character to be displayed.
 */
void screen_set_char(char character);

/**
 * @brief Displays a predefined board layout on the LED matrix.
 * @param board A pointer to the predefined board structure.
 */
void screen_set_predefined_board(const PredefinedBoard_t* board);

/**
 * @brief Sets a pixel on the LED matrix to the specified value.
 * @param col The column index of the pixel.
 * @param row The row index of the pixel.
 * @param value The pixel value (on or off).
 */
void screen_set_pixel(uint8_t col, uint8_t row, tinygl_pixel_value_t value);

void screen_scrolling_message_update(void);

#endif /* SCREEN_H */
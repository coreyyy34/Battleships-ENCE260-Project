#ifndef MESSAGE_H
#define MESSAGE_H

#include "../fonts/font5x7_1.h"
#include "system.h"
#include "board.h"

#define PACER_RATE 500  // Pacer ticks per second for timing control
#define MESSAGE_RATE 20 // Characters to display every 10 seconds

// LED states for the UCFK LED mat which is in an active low configuration
#define PIXEL_ON 1  // Value representing a pixel that is turned on
#define PIXEL_OFF 0 // Value representing a pixel that is turned off

#define MESSAGE_HIT " HIT "         // Message displayed for a hit
#define MESSAGE_MISS " MISS "       // Message displayed for a miss
#define MESSAGE_WINNER " YOU WON! " // Message displayed when the player wins
#define MESSAGE_LOSER " YOU LOST! " // Message displayed when the player loses

/**
 * @brief Calculates the number of ticks required to scroll a message.
 * @param text The message text to be scrolled.
 * @return The calculated number of ticks for scrolling the message.
 */
uint32_t message_calculate_scrolling_message_ticks(const char* text);

/**
 * @brief Specifies the text to scroll on the screen.
 * @param text The message text to be displayed.
 */
void message_scrolling_message(const char* text);

/**
 * @brief Specifies a character to show on the screen.
 * @param character The character to be displayed.
 */
void message_char(char character);

/**
 * @brief Initializes the message display system.
 */
void message_init(void);

/**
 * @brief Displays a predefined board on the message display.
 * @param board Pointer to the predefined board to be displayed.
 */
void message_display_pre_defined_board(const PredefinedBoard_t* board);

/**
 * @brief Updates a specific pixel on the display.
 * @param col The column index of the pixel to update.
 * @param row The row index of the pixel to update.
 * @param value The value indicating whether to turn the pixel on or off.
 */
void message_display_pixel(uint8_t col, uint8_t row, tinygl_pixel_value_t value);

/**
 * @brief Clears the message display.
 */
void message_clear(void);

#endif /* MESSAGE_H */

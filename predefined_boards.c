/** 
 * @file   predefined_boards.c
 * @brief  Implementation of predefined board configurations for the Battleship game.
 *
 * This file contains the implementation of predefined board configurations used
 * in the Battleship game. Each board configuration is defined as a constant and
 * can be referenced throughout the game to set up different board layouts. The
 * file also includes an array of pointers to these board configurations and a
 * count of the total number of boards available.
 *
 * @date   17/10/2024
 * @author Corey Hines, Ethan Field
 */

#include "predefined_boards.h"
#include "board.h"

/**
 * @brief Represents a predefined board configuration of ID 0.
 * @note This board contains 2 ship cells and should only be used for testing.
 */
const PredefinedBoard_t BOARD_0 = {
    0b00000,
    0b00000,
    0b00000,
    0b01010,
    0b00000,
    0b00000,
    0b00000};

/**
 * @brief Represents a predefined board configuration of ID 1.
 */
const PredefinedBoard_t BOARD_1 = {
    0b00110,
    0b11000,
    0b00001,
    0b00001,
    0b11101,
    0b00000,
    0b01100};

/**
 * @brief Represents a predefined board configuration of ID 2.
 */
const PredefinedBoard_t BOARD_2 = {
    0b10111,
    0b10000,
    0b00110,
    0b01000,
    0b01011,
    0b01000,
    0b00000};

/**
 * @brief Represents a predefined board configuration of ID 3.
 */
const PredefinedBoard_t BOARD_3 = {
    0b00001,
    0b10001,
    0b10101,
    0b10100,
    0b00011,
    0b00000,
    0b11000};

/**
 * @brief Represents a predefined board configuration of ID 4.
 */
const PredefinedBoard_t BOARD_4 = {
    0b01010,
    0b01010,
    0b00010,
    0b11000,
    0b00111,
    0b00000,
    0b11000};

/**
 * @brief Represents a predefined board configuration of ID 5.
 */
const PredefinedBoard_t BOARD_5 = {
    0b10001,
    0b10001,
    0b00001,
    0b00011,
    0b01100,
    0b00000,
    0b00111};

/**
 * @brief Array of pointers to predefined board configurations.
 */
const PredefinedBoard_t *PREDEFINED_BOARDS[] = {
    &BOARD_0,
    &BOARD_1,
    &BOARD_2,
    &BOARD_3,
    &BOARD_4,
    &BOARD_5};

/**
 * @brief Total number of predefined boards available.
 * 
 * This is calculated dynamically by dividing the size of the
 * predefined boards array (which is an array of pointers) by
 * the size of a pointer.
 */
const uint8_t NUM_BOARDS = sizeof(PREDEFINED_BOARDS) / sizeof(PredefinedBoard_t *);

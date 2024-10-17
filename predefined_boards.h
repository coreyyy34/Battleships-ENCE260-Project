#ifndef PREDEFINED_BOARDS_H
#define PREDEFINED_BOARDS_H

#include <stdint.h>

/**
 * @brief Represents a predefined board configuration of ID 0.
 */
const PredefinedBoard_t BOARD_0 = {
    0b0000000, 
    0b0000000, 
    0b0000000, 
    0b0001010,
    0b0000000, 
    0b0000000, 
    0b0000000};

/**
 * @brief Represents a predefined board configuration of ID 1.
 */
const PredefinedBoard_t BOARD_1 = {
    0b0011000, 
    0b1000000, 
    0b0000001, 
    0b0000001, 
    0b1110001, 
    0b0000000, 
    0b1100000};

/**
 * @brief Represents a predefined board configuration of ID 2.
 */
const PredefinedBoard_t BOARD_2 = {
    0b0011101, 
    0b0010000, 
    0b0110000, 
    0b0001000, 
    0b0010100, 
    0b0001000, 
    0b0000000};

/**
 * @brief Represents a predefined board configuration of ID 3.
 */
const PredefinedBoard_t BOARD_3 = {
    0b0000001, 
    0b0010001, 
    0b0010101, 
    0b0010101, 
    0b0000011, 
    0b0000000, 
    0b1000000};

/**
 * @brief Represents a predefined board configuration of ID 4.
 */
const PredefinedBoard_t BOARD_4 = {
    0b0010100, 
    0b0010100, 
    0b0000100, 
    0b0011000, 
    0b0011100, 
    0b0000000, 
    0b1000000};

/**
 * @brief Represents a predefined board configuration of ID 5.
 */
const PredefinedBoard_t BOARD_5 = {
    0b0100001, 
    0b0100001, 
    0b0000001, 
    0b0000011, 
    0b0111000, 
    0b0000000, 
    0b0111000};

/**
 * @brief Array of pointers to predefined board configurations.
 */
const PredefinedBoard_t* PREDEFINED_BOARDS[] = {
    &BOARD_0,
    &BOARD_1,
    &BOARD_2,
    &BOARD_3,
    &BOARD_4,
    &BOARD_5
};

/**
 * @brief Total number of predefined boards available.
 */
const uint8_t NUM_BOARDS = sizeof(PREDEFINED_BOARDS) / sizeof(PredefinedBoard_t*);

#endif /* PREDEFINED_BOARDS_H */
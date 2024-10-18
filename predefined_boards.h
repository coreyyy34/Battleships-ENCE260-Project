/** 
 * @file   predefined_boards.h
 * @brief  Header of predefined board configurations for the Battleship game.
 * @author Corey Hines
 * @date   17/10/2024
 */

#ifndef PREDEFINED_BOARDS_H
#define PREDEFINED_BOARDS_H

#include <stdint.h>
#include "board.h"

/**
 * @brief Represents a predefined board configuration of ID 0.
 * @note This board contains 2 ship cells and should only be used for testing.
 */
extern const PredefinedBoard_t BOARD_0;

/**
 * @brief Represents a predefined board configuration of ID 1.
 */
extern const PredefinedBoard_t BOARD_1;

/**
 * @brief Represents a predefined board configuration of ID 2.
 */
extern const PredefinedBoard_t BOARD_2;

/**
 * @brief Represents a predefined board configuration of ID 3.
 */
extern const PredefinedBoard_t BOARD_3;

/**
 * @brief Represents a predefined board configuration of ID 4.
 */
extern const PredefinedBoard_t BOARD_4;

/**
 * @brief Represents a predefined board configuration of ID 5.
 */
extern const PredefinedBoard_t BOARD_5;

/**
 * @brief Array of pointers to predefined board configurations.
 */
extern const PredefinedBoard_t* PREDEFINED_BOARDS[];

/**
 * @brief Total number of predefined boards available.
 */
extern const uint8_t NUM_BOARDS;

#endif /* PREDEFINED_BOARDS_H */

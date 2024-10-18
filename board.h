/** 
 * @file   board.h
 * @brief  Header of the game board management functions.
 * @date   17/10/2024
 * @author Corey Hines
 */

#ifndef BOARD_H
#define BOARD_H

#include "system.h"
#include "tinygl.h"

#define BOARD_ROWS_NUM LEDMAT_ROWS_NUM
#define BOARD_COLS_NUM LEDMAT_COLS_NUM

/* we were running out of memory I think (adding another board resulted
   in weird behavior) so instead of having a 2D array  of uint8_t (35 bytes), 
   use an array of uint8_t which store each column (7 bytes) */
typedef uint8_t PredefinedBoard_t[LEDMAT_ROWS_NUM];
typedef uint8_t Board_t[LEDMAT_ROWS_NUM][LEDMAT_COLS_NUM];

/**
 * @enum  BoardCellState_t.
 * @brief Represents the state of an individual cell on a board.
 */
typedef enum
{
    SHIP_UNEXPLORED,  /**< Represents a ship cell which has not been explored */
    SHIP_EXPLORED,    /**< Represents a ship cell which has been explored */
    EMPTY_UNEXPLORED, /**< Represents an empty cell which has not been explored */
    EMPTY_EXPLORED,   /**< Represents an empty cell which has been explored */
} BoardCellState_t;

/**
 * @enum  BoardResponse_t.
 * @brief Represents the result of a shot fired on their board.
 */
typedef enum
{
    NONE,   /**< Represents a cell has previously been discovered */
    MISS,   /**< Represents a cell that was targeted but contained no ship. */
    HIT,    /**< Represents a ship point that has been hit */
    WINNER, /**< Represents we won - all their ships are sunk */
    LOSER,  /**< Represents we lost - all our ships are sunk */
} BoardResponse_t;

/**
 * @brief  Creates a new game board based on a predefined layout.
 * @param  predefined_board: The predefined board configuration to use.
 * @return A pointer to the newly allocated board.
 */
Board_t* create_board(const PredefinedBoard_t* predefined_board);

/**
 * @brief Frees the memory used by both the player's and the opponent's boards.
 */
void delete_boards(void);

/**
 * @brief  Checks the result of firing a shot at the opponent's board.
 * @param  row: The row index of the targeted cell.
 * @param  col: The column index of the targeted cell.
 * @return The response indicating if the shot was a HIT, MISS, or if it resulted in a WINNER.
 */
BoardResponse_t board_check_our_shot_their_board(uint8_t row, uint8_t col);

/** @brief Pointer to the player's game board. */
extern Board_t* our_board;

/** @brief Pointer to the opponent's game board. */
extern Board_t* their_board;

/** @brief Predefined board ID for the player's board. */
extern uint8_t our_predefined_board_id;

/** @brief Predefined board ID for the opponent's board. */
extern uint8_t their_predefined_board_id;

#endif /* BOARD_H */
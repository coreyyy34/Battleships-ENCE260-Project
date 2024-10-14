/** @file   board.h
 *  @author Corey Hines, Ethan Field
 *  @date   15 October 2024
 *  @brief  This file defines the structures and functions for 
 *          handling board creation, manipulation, and destruction in the game.
 */

#ifndef BOARD_H
#define BOARD_H

#include "ship.h"
#include "system.h"

#define BOARD_ROWS_NUM LEDMAT_ROWS_NUM
#define BOARD_COLS_NUM LEDMAT_COLS_NUM
#define SHIPS_NUM 4

/**
 * @enum BoardType_t
 * @brief Enumeration for board types.
 */
typedef enum 
{
    OUR_BOARD,   /** Represents the player's board. */
    THEIR_BOARD, /** Represents the opponent's board. */
} BoardType_t;

/**
 * @enum BoardCell_t
 * @brief Enumeration for cell types.
 */
typedef enum
{
    SHIP_POINT_UNEXPLORED, /** Represents a ship point that has not been found. */
    SHIP_POINT_HIT,        /** Represents a ship point that has been hit. */
    EMPTY,                 /** Represents an empty point. */
    MISS,                  /** Represents a cell that was targeted but contained no ship. */
} BoardCell_t;

/**
 * @struct Board_t
 * @brief Represents a game board.
 */
typedef struct 
{
    BoardType_t type;    /** The type of the board (OUR_BOARD or THEIR_BOARD). */
    Ship_t** ships;      /** Array of pointers to Ship_t objects on the board. */
    BoardCell_t** grid;   /** Grid representation of the board. True represents a hit, false represents a miss or unexplored cell. */
    uint8_t num_ships;   /** Number of ships currently on the board. */
} Board_t;

/**
 * @brief  Creates a new game board.
 * @param  type The type of board to create (OUR_BOARD or THEIR_BOARD).
 * @return A pointer to the newly created Board_t object.
 */
Board_t* board_create(BoardType_t type);

/**
 * @brief  Adds a ship to the board.
 * @param  board Pointer to the Board_t object.
 * @param  ship Pointer to the Ship_t object to add.
 * @return true if the ship was successfully added, false otherwise.
 */
bool board_add_ship(Board_t* board, Ship_t* ship);

/**
 * @brief Removes a board and frees associated memory.
 * @param board Pointer to the Board_t object to be removed.
 */
void board_remove(Board_t* board);

#endif /* BOARD_H */
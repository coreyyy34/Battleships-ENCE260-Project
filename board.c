/** @file   board.c
 *  @author Corey Hines, Ethan Field
 *  @date   15 October 2024
 *  @brief  This file defines the structures and functions for 
 *          handling board creation, manipulation, and destruction in the game.
 */

#include <stdlib.h>
#include "board.h"
#include "ship.h"

/**
 * @brief Creates a new game board.
 * @param type The type of board to create (OUR_BOARD or THEIR_BOARD).
 * @return A pointer to the newly created Board_t object.
 */
Board_t* board_create(BoardType_t type)
{
    Board_t* board = malloc(sizeof(Board_t));
    Ship_t* ships = calloc(SHIPS_NUM, sizeof(Ship_t));
    BoardCell_t* grid = calloc(BOARD_ROWS_NUM + BOARD_COLS_NUM, sizeof(BoardCell_t));
    board->type = type;
    board->ships = &ships;
    board->grid = &grid;
    board->num_ships = 0;
    return board;
}

/**
 * @brief  Adds a ship to the board.
 * @param  board Pointer to the Board_t object.
 * @param  ship Pointer to the Ship_t object to add.
 * @return true if the ship was successfully added, false otherwise.
 */
bool board_add_ship(Board_t* board, Ship_t* ship)
{
    if (board->num_ships >= SHIPS_NUM) {
        return false;  // board is full
    }

    // check if the ship's position is valid
    for (uint8_t i = 0; i < ship->type; i++) {
        uint8_t x = ship->points[i].x_coord;
        uint8_t y = ship->points[i].y_coord;
        
        if (x >= BOARD_COLS_NUM || y >= BOARD_ROWS_NUM || 
            board->grid[y][x] != EMPTY) {
            return false;  // invalid position
        }
    }

    // add the ship and mark its position on the grid
    board->ships[board->num_ships] = ship;
    board->num_ships++;

    for (uint8_t i = 0; i < ship->type; i++) {
        uint8_t x = ship->points[i].x_coord;
        uint8_t y = ship->points[i].y_coord;
        board->grid[y][x] = SHIP_POINT_UNEXPLORED;
    }

    return true;
}

/**
 * @brief Removes a board and frees associated memory.
 * @param board Pointer to the Board_t object to be removed.
 */
void board_remove(Board_t* board)
{
    free(board->ships);
    free(board->grid);
    free(board);
}
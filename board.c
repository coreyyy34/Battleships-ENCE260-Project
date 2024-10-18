/** 
 * @file   board.c
 * @brief  Implementation of the game board management functions.
 *
 * This file contains the implementation of functions for creating, managing,
 * and updating the game boards in the Battleship game. It includes functions
 * for creating a new board based on a predefined layout, freeing the memory
 * used by the boards, and checking the result of firing a shot at the opponent's
 * board.
 *
 * @date   17/10/2024
 * @author Corey Hines
 */

#include <stdlib.h> 
#include <string.h>
#include "board.h"

/** @brief Pointer to the player's game board. */
Board_t* our_board = NULL;

/** @brief Pointer to the opponent's game board. */
Board_t* their_board = NULL;

/** @brief Predefined board ID for the player's board. */
uint8_t our_predefined_board_id = 0;

/** @brief Predefined board ID for the opponent's board. */
uint8_t their_predefined_board_id = 0;

/**
 * @brief Creates a new game board based on a predefined layout.
 *
 * This function allocates memory for a new game board and initializes it
 * based on a given predefined board configuration. Each cell in the new
 * board is set to either SHIP_UNEXPLORED or EMPTY_UNEXPLORED based on the
 * predefined board data.
 *
 * @param predefined_board The predefined board configuration to use.
 * @return A pointer to the newly allocated board.
 */
Board_t* create_board(const PredefinedBoard_t* predefined_board)
{
    Board_t* new_board = (Board_t*) malloc(sizeof(Board_t));
    for (uint8_t row = 0; row < BOARD_ROWS_NUM; row++)
    {
        uint8_t row_data = (*predefined_board)[row];  // Get the packed row
        for (uint8_t col = 0; col < BOARD_COLS_NUM; col++)
        {
            // Extract each bit from the row (shift right and mask)
            uint8_t cell = (row_data >> (BOARD_COLS_NUM - 1 - col)) & 1;
            (*new_board)[row][col] = (cell == 1) ? SHIP_UNEXPLORED : EMPTY_UNEXPLORED;
        }
    }
    return new_board;
}

/**
 * @brief Frees the memory used by both the player's and the opponent's boards.
 *
 * This function deallocates the memory allocated for the player's and the
 * opponent's game boards, effectively clearing the boards' data.
 */
void delete_boards(void)
{
    free(our_board);
    free(their_board);
}

/**
 * @brief Checks if all the opponent's ships have been sunk.
 *
 * This function iterates through the opponent's board and checks if all ship
 * cells have been explored. If all ships are sunk, it returns true.
 *
 * @return True if all opponent's ships are sunk, false otherwise.
 */
static bool check_all_their_ships_sunk(void)
{
    for (uint8_t row = 0; row < BOARD_ROWS_NUM; row++)
    {
        for (uint8_t col = 0; col < BOARD_COLS_NUM; col++)
        {
            if ((*their_board)[row][col] == SHIP_UNEXPLORED)
            {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Checks the result of firing a shot at the opponent's board.
 *
 * This function determines the result of a shot fired at a specified cell
 * on the opponent's board. It updates the cell's state and returns a response
 * indicating if the shot was a HIT, MISS, or if it resulted in a WINNER.
 *
 * @param row The row index of the targeted cell.
 * @param col The column index of the targeted cell.
 * @return The response indicating if the shot was a HIT, MISS, or if it resulted in a WINNER.
 */
BoardResponse_t board_check_our_shot_their_board(uint8_t row, uint8_t col)
{
    switch ((*their_board)[row][col]) 
    {
        case SHIP_UNEXPLORED:
            (*their_board)[row][col] = SHIP_EXPLORED;
            return check_all_their_ships_sunk() ? WINNER : HIT;
        case EMPTY_UNEXPLORED:
            (*their_board)[row][col] = EMPTY_EXPLORED;
            return MISS;
        case SHIP_EXPLORED:
        case EMPTY_EXPLORED:
            return NONE;
    }
    return 9;
}
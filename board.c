#include <stdlib.h> 
#include <string.h>
#include "board.h"

Board_t* our_board = NULL;
Board_t* their_board = NULL;

uint8_t our_predefined_board_id = NULL;
uint8_t their_predefined_board_id = NULL;

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

void delete_boards(void)
{
    free(our_board);
    free(their_board);
}

static bool check_all_their_ships_sunk(void)
{
    for (uint8_t row = 0; row < BOARD_ROWS_NUM; row++)
    {
        uint8_t row_data = (*their_board)[row];
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

BoardResponse_t board_check_our_shot_their_board(uint8_t row, uint8_t col)
{
    switch ((*their_board)[row][col])  // Access the element without dereferencing
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
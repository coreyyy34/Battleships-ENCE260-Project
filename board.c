#include <stdlib.h> 
#include <string.h>
#include "board.h"

Board_t* our_board = NULL;
Board_t* their_board = NULL;

Board_t* create_board(const PredefinedBoard_t* predefined_board)
{
    Board_t* new_board = (Board_t*) malloc(sizeof(Board_t));
    for (uint8_t row = 0; row < BOARD_ROWS_NUM; row++)
    {
        for (uint8_t col = 0; col < BOARD_COLS_NUM; col++)
        {
            (*new_board)[row][col] = (*predefined_board)[row][col] == 1 ? SHIP_UNEXPLORED : EMPTY_UNEXPLORED;
            // (*new_board)[row][col] = 2;
        }
    }
    return new_board;
}

void delete_boards(void)
{
    free(our_board);
    free(their_board);
}

BoardResponse_t board_check_our_shot_their_board(uint8_t row, uint8_t col)
{
    switch ((*their_board)[row][col])  // Access the element without dereferencing
    {
        case SHIP_UNEXPLORED:
            (*their_board)[row][col] = SHIP_EXPLORED;
            return HIT;
        case EMPTY_UNEXPLORED:
            (*their_board)[row][col] = EMPTY_EXPLORED;
            return MISS;
        case SHIP_EXPLORED:
        case EMPTY_EXPLORED:
            return NONE;
    }
    return 9;
}
#ifndef BOARD_H
#define BOARD_H

#include "system.h"
#include "tinygl.h"

#define BOARD_ROWS_NUM LEDMAT_ROWS_NUM
#define BOARD_COLS_NUM LEDMAT_COLS_NUM

typedef tinygl_pixel_value_t PredefinedBoard_t[LEDMAT_ROWS_NUM][LEDMAT_COLS_NUM];
typedef uint8_t Board_t[LEDMAT_ROWS_NUM][LEDMAT_COLS_NUM];

typedef enum
{
    SHIP_UNEXPLORED,
    SHIP_EXPLORED,
    EMPTY_UNEXPLORED,
    EMPTY_EXPLORED,
} BoardCellState_t;

typedef enum
{
    MISS,   /** Represents a cell that was targeted but contained no ship. */
    HIT,    /** Represents a ship point that has been hit */
    NONE,   /** Represents a cell has previously been discovered */
} BoardResponse_t;

typedef enum 
{
    OUR_BOARD,   /** Represents the player's board. */
    THEIR_BOARD, /** Represents the opponent's board. */
} BoardType_t;

Board_t* create_board(const PredefinedBoard_t* predefined_board);
void delete_boards(void);

BoardResponse_t board_check_our_shot_their_board(uint8_t row, uint8_t col);

extern Board_t* our_board;
extern Board_t* their_board;

extern uint8_t our_predefined_board_id;
extern uint8_t their_predefined_board_id;

#endif
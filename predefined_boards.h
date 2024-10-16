#ifndef PREDEFINED_BOARDS_H
#define PREDEFINED_BOARDS_H

#include "tinygl.h"
#include "board.h"

const PredefinedBoard_t BOARD_1 = {
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0}
};

const PredefinedBoard_t BOARD_2 = {
    {0, 0, 0, 1, 1},
    {0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 0, 0, 1},
    {0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

const PredefinedBoard_t BOARD_3 = {
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0},
    {1, 0, 1, 0, 0},
    {0, 0, 0, 1, 1},
    {0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0}
};

const PredefinedBoard_t BOARD_4 = {
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1},
    {0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0}
};

const PredefinedBoard_t BOARD_5 = {
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 1, 1},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

const uint8_t NUM_BOARDS = 5;

const PredefinedBoard_t* PREDEFINED_BOARDS[] = {
    &BOARD_1,
    &BOARD_2,
    &BOARD_3,
    &BOARD_4,
    &BOARD_5
};

#endif

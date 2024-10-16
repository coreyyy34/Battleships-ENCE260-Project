#ifndef PREDEFINED_BOARDS_H
#define PREDEFINED_BOARDS_H

#include "tinygl.h"

const tinygl_pixel_value_t BOARD_1[LEDMAT_ROWS_NUM][LEDMAT_COLS_NUM] = 
{
    {0, 0, 0, 0, 0},  // Row 1
    {0, 1, 0, 0, 0},  // Row 2
    {0, 1, 0, 0, 0},  // Row 3
    {0, 1, 0, 0, 0},  // Row 4
    {0, 0, 0, 0, 0},  // Row 5
    {0, 0, 1, 1, 0},  // Row 6
    {0, 0, 0, 0, 0}   // Row 7
};

const uint8_t NUM_BOARDS = 1;
const tinygl_pixel_value_t* BOARDS[] = {
    (const tinygl_pixel_value_t*) BOARD_1
};

#endif
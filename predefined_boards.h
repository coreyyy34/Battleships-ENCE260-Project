#ifndef PREDEFINED_BOARDS_H
#define PREDEFINED_BOARDS_H

#include "tinygl.h"
#include "board.h"
#include <stdbool.h>

typedef struct {
    PredefinedBoard_t board;
    uint8_t required_hits;
    uint8_t opponent_hits;
    uint8_t player_hits;
}  PredefinedBoardWithHits_t;

static bool check_player_hits(PredefinedBoardWithHits_t* board)
{
    board->player_hits++;
    if (board->player_hits >= board->total_hits)
    {
        return true
    }
    return false
}

const PredefinedBoardWithHits_t BOARD_1 = {
    {{0, 0, 1, 1, 0},
    {1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0}},
    .total_hits = 12
    .player_hits = 0
    .opponent_hits = 0
};

const PredefinedBoardWithHits_t BOARD_2 = {
    {{1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0},
    {0, 0, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 1},
    {0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0}},
    .total_hits = 12
    .player_hits = 0
    .opponent_hits = 0
};

const PredefinedBoardWithHits_t BOARD_3 = {
    {{0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0},
    {0, 0, 0, 1, 1},
    {0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0}},
    .total_hits = 12
    .player_hits = 0
    .opponent_hits = 0
};

const PredefinedBoardWithHits_t BOARD_4 = {
    {{0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1},
    {0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0}},
    .total_hits = 12
    .player_hits = 0
    .opponent_hits = 0
};

const PredefinedBoardWithHits_t BOARD_5 = {
    {{1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 1, 1},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1}},
    .total_hits = 12
    .player_hits = 0
    .opponent_hits = 0
};

const PredefinedBoardWithHits_t BOARD_5 = {
    {{1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 1, 1},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1}},
    .total_hits = 12
    .player_hits = 0
    .opponent_hits = 0
};

const PredefinedBoardWithHits_t BOARD_6 = {
    {{1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}},
    .total_hits = 2
    .player_hits = 0
    .opponent_hits = 0
};

const uint8_t NUM_BOARDS = 6;

const PredefinedBoardWithHits_t* PREDEFINED_BOARDS[] = {
    &BOARD_1,
    &BOARD_2,
    &BOARD_3,
    &BOARD_4,
    &BOARD_5,
    &BOARD_6
};

#endif

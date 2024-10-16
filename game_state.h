#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef enum {
    GAME_STATE_TITLE_SCREEN,
    GAME_STATE_SELECT_PLAYER,
    GAME_STATE_CHOOSE_BOARD,
    GAME_STATE_AWAIT_BOARD_EXCHANGE,
    GAME_STATE_SELECT_SHOOT_POSITION,
    GAME_STATE_SHOOT_HIT_MESSAGE,
    GAME_STATE_SHOOT_MISS_MESSAGE,
    GAME_STATE_OUR_TURN,
    GAME_STATE_THEIR_TURN,
} GameState_t;

#endif
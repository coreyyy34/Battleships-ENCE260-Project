/**
 * @file   game.h
 * @brief  Header of the Battleship containing state management.
 * @date   17/10/2024
 * @author Corey Hines
 */

#ifndef GAME_H
#define GAME_H

#include "game_state.h"
#include <stdint.h>
#include <stdbool.h>

#define PACER_RATE 500  /**< Defines the pacer tick rate (ticks per second). */

/**
 * @brief Set the current game state.
 * @param new_game_state The new game state to be set.
 */
void set_game_state(GameState_t new_game_state);

/** 
 * @brief Flag indicating if the other player's board has been received. 
 */
extern bool received_their_board;

/** 
 * @brief Flag indicating if our board has been sent to the other player. 
 */
extern bool sent_our_board;

/** 
 * @brief The player number (1 or 2) of the player using this board.
 */
extern uint8_t player_number;

#endif /* GAME_H */
/** @file   game.h
 *  @author Corey Hines
 *  @date   17/10/2024
 */

#ifndef GAME_H
#define GAME_H

#include "game_state.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Set the current game state.
 * @param new_game_state The new game state to be set.
 */
void set_game_state(GameState_t new_game_state);

/**
 * @brief Sets the scrolling message to be displayed.
 * @param text The message to be displayed.
 * @param The state to switch to once the message has finished scrolling.
 */
void set_scrolling_message(char* text, GameState_t finish_state);

/** 
 * @brief Flag indicating if the other player's board has been received. 
 */
extern bool received_their_board;

/** 
 * @brief Flag indicating if our board has been sent to the other player. 
 */
extern bool sent_our_board;

/** 
 * @brief The player number (1 or 2) of the current player.
 */
extern uint8_t player_number;

#endif /* GAME_H */
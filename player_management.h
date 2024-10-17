/** @file   player_management.h
 *  @author Corey Hines
 *  @date   17/10/2024
 */

#ifndef PLAYER_MANAGEMENT_H
#define PLAYER_MANAGEMENT_H

/**
 * @brief Update the player selection process.
 *
 * This function handles the logic for selecting the player 
 * (player 1 or player 2) during the game setup phase.
 */
void update_select_player(void);

/**
 * @brief Updates to check if the other player has sent their board.
 * 
 * If the board has been received, the next phase of the game will 
 * begin, if not we will keep waiting.
 */
void update_receive_their_board(void);

#endif /* PLAYER_MANAGEMENT_H */
/** 
 * @file   board_manager.h
 * @brief  Header of board management functions for the Battleship game.
 * @author Corey Hines
 * @date   17/10/2024
 */

#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H

/**
 * @brief Updates to check if the other player has sent their
 * turn.
 * 
 * If the turn has been received, the next phase of the game will
 * begin, if not we will keep waiting.
 */
void update_receive_their_turn(void);

/**
 * @brief Updates the cell selection process where the user
 * selects a cell to send a shot.
 */
void update_select_shoot_position(void);

#endif /* BOARD_MANAGER_H */
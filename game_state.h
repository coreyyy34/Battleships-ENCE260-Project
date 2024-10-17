#ifndef GAME_STATE_H
#define GAME_STATE_H

/**
 * @enum  GameState_t
 * @brief Represents the various states of the game.
 */
typedef enum {
    GAME_STATE_TITLE_SCREEN,           /**< The game is at the title screen, where players can start or access settings. */
    GAME_STATE_SELECT_PLAYER,          /**< The state where players select their characters or profiles. */
    GAME_STATE_CHOOSE_BOARD,           /**< The state where players choose the game board configuration. */
    GAME_STATE_AWAIT_BOARD_EXCHANGE,   /**< The state where players exchange their selected boards with each other. */
    GAME_STATE_SELECT_SHOOT_POSITION,  /**< The state where a player selects a position to shoot on the opponent's board. */
    GAME_STATE_THEIR_TURN,             /**< The state indicating that it is the opponent's turn to play. */
    GAME_STATE_SHOWING_MESSAGE,        /**< The state for displaying messages or notifications to the players. */
    GAME_STATE_END,                    /**< The final state of the game, indicating that the game has ended. */
} GameState_t;

#endif /* GAME_STATE_H */
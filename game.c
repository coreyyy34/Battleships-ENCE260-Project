/**
 * @file   game.c
 * @brief  Implementation of the Battleship game logic and state management.
 *
 * This file contains the main game loop and the implementation of functions
 * for managing and updating the game state in the Battleship game. It handles
 * initializing the system, managing game states, and updating the display and
 * communication with the other player's board.
 *
 * @date   17/10/2024
 * @author Corey Hines
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "game.h"              /** Header for game */
#include "system.h"            /** UCFK - system.h */
#include "button.h"            /** UCFK - button.h */
#include "pacer.h"             /** UCFK - pacer.h */
#include "led.h"               /** UCFK - led.h */
#include "ir.h"                /** Wrapper for ir_uart.h */
#include "screen.h"            /** Wrapper for tinygl.h */
#include "setup_manager.h"     /** Handles game states SELECT_PLAYER, CHOOSE_BOARD, AWAIT_BOARD_EXCHANGE */
#include "board_manager.h"     /** Handles game states THEIR_TURN, SELECT_SHOOT_POSITION,  */

/** @brief The current game state. */
static GameState_t game_state;

/** @brief Flag indicating if the other player's board has been received. */
bool received_their_board;

/** @brief Flag indicating if our board has been sent to the other player. */
bool sent_our_board;

/** @brief The player number (1 or 2) of the player using this board. */
uint8_t player_number;

/**
 * @brief Set the current game state.
 *
 * This function updates the game state to the specified new state and clears
 * the screen. It also updates the LED to indicate if it is the other player's turn.
 *
 * @param new_game_state The new game state to be set.
 */
void set_game_state(GameState_t new_game_state)
{
    game_state = new_game_state;

    // turn LED on when its the other players turn
    // set it only when game state changes instead of every tick
    led_set(LED1, game_state == GAME_STATE_THEIR_TURN);
    screen_clear();

    // when the game ends, free the boards where were dynamically allocated.
    if (game_state == GAME_STATE_END)
    {
        delete_boards();
    }
}

/**
 * @brief Main function to initialize the game and run the game loop.
 *
 * This function initializes the system, sets up the initial game state, and
 * runs the main game loop. The game loop updates the screen and checks the
 * current game state to perform the appropriate actions.
 */
int main(void)
{
    // initialise system and components of UCFK4
    system_init();
    pacer_init(PACER_RATE);
    button_init();
    screen_init();
    ir_uart_init();
    led_init();

    // initialise states
    game_state = GAME_STATE_TITLE_SCREEN;
    received_their_board = false;
    sent_our_board = false;

    // game loop
    while (1)
    {
        pacer_wait();
        screen_update(); // every state uses the screen so update every tick

        // check if a scrolling message is active
        // if it is, update it then skip game state checking
        if (screen_scrolling_message_active())
        {
            screen_scrolling_message_update();
            continue;
        }

        switch (game_state) 
        {
            case GAME_STATE_TITLE_SCREEN:
                set_game_state(GAME_STATE_SELECT_PLAYER);
                screen_set_scrolling_text(" BATTLESHIPS ");
                break;
            case GAME_STATE_SELECT_PLAYER:
                update_receive_their_board();
                update_select_player();
                break;
            case GAME_STATE_CHOOSE_BOARD:
                update_receive_their_board();
                update_choose_board();
                break;
            case GAME_STATE_AWAIT_BOARD_EXCHANGE:
                update_receive_their_board();
                break;
            case GAME_STATE_SELECT_SHOOT_POSITION:
                update_select_shoot_position();
                break;
            case GAME_STATE_THEIR_TURN:
                update_receive_their_turn();
                break;
            case GAME_STATE_END:
                break;
            default: 
                break;
        }

    }
}
/** @file   game.c
 *  @author Corey Hines
 *  @date   17/10/2024
 */

#include <string.h>
#include "game.h"              /** Header for game */
#include "system.h"            /** UCFK - system.h */
#include "button.h"            /** UCFK - button.h */
#include "pacer.h"             /** UCFK - pacer.h */
#include "led.h"               /** UCFK - led.h */
#include "navigation_switch.h" /** Wrapper for navswitch.h */
#include "ir.h"                /** Wrapper for ir_uart.h */
#include "screen.h"            /** Wrapper for tinygl.h */
#include "setup_manager.h"     /** Handles game states SELECT_PLAYER, CHOOSE_BOARD, AWAIT_BOARD_EXCHANGE */
#include "board_manager.h"     /** Handles game states THEIR_TURN, SELECT_SHOOT_POSITION,  */

static GameState_t prev_game_state;
static GameState_t game_state;

bool received_their_board;
bool sent_our_board;
uint8_t player_number;

void set_game_state(GameState_t new_game_state)
{
    prev_game_state = game_state;
    game_state = new_game_state;
    screen_clear();
}

int main(void)
{
    system_init();
    pacer_init(PACER_RATE);
    button_init();
    screen_init();
    ir_uart_init();
    led_init();
    led_set(LED1, 0);

    prev_game_state = GAME_STATE_TITLE_SCREEN;
    game_state = GAME_STATE_TITLE_SCREEN;

    received_their_board = false;
    sent_our_board = false;

    while (1)
    {
        pacer_wait();
        screen_update();

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
                led_set(LED1, 0); /* turn the led off when its our turn */
                update_select_shoot_position();
                break;
            case GAME_STATE_THEIR_TURN:
                led_set(LED1, 1); /* turn the led on when its their turn to indicate they need to wait */
                update_receive_their_turn();
                break;
            // case GAME_STATE_SHOWING_MESSAGE: unused
            //     update_scrolling_message();
            //     break;
            default: 
                break;
        }

    }
}
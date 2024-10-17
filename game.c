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
#include "message.h"           /** Wrapper for tinygl.h */

#include "setup_manager.h"
#include "board_manager.h"
#include "game_state.h"

#define PACER_RATE 500  // pacer ticks per second

static GameState_t prev_game_state;
static GameState_t game_state;
static char* scrolling_text;
static GameState_t scrolling_finish_state;

bool received_their_board;
bool sent_our_board;
uint8_t player_number;

void set_game_state(GameState_t new_game_state)
{
    prev_game_state = game_state;
    game_state = new_game_state;
    message_clear();
}

void set_scrolling_message(char* text, GameState_t finish_state)
{
    scrolling_text = text;
    scrolling_finish_state = finish_state;
    set_game_state(GAME_STATE_SHOWING_MESSAGE);
}


static void update_scrolling_message(void)
{
    static uint32_t ticks = 0;
    static uint32_t total_ticks = 0;
    static bool initialised = false;

    if (!initialised) 
    {
        initialised = true;
        ticks = 0;
        total_ticks = message_calculate_scrolling_message_ticks(scrolling_text);
        message_scrolling_message(scrolling_text);
    }

    if (ticks++ >= total_ticks)
    {
        pacer_wait();
        set_game_state(scrolling_finish_state); 
        ticks = 0;
        total_ticks = 0;
        initialised = false;
        scrolling_text = NULL;
    }
}

int main(void)
{
    system_init();
    pacer_init(PACER_RATE);
    button_init ();
    message_init();
    ir_uart_init();
    led_init();
    led_set(LED1, 0);
    
    prev_game_state = GAME_STATE_TITLE_SCREEN;
    game_state = GAME_STATE_TITLE_SCREEN;
    scrolling_text = NULL;
    scrolling_finish_state = GAME_STATE_TITLE_SCREEN;
    received_their_board = false;
    sent_our_board = false;

    while (1)
    {
        pacer_wait();
        message_update();
        switch (game_state) 
        {
            case GAME_STATE_TITLE_SCREEN:
                set_scrolling_message(" BATTLESHIPS ", GAME_STATE_SELECT_PLAYER);
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
                // update_exchange_board();
                break;
            case GAME_STATE_SELECT_SHOOT_POSITION:
                led_set(LED1, 0); /* turn the led off when its our turn */
                update_select_shoot_position();
                break;
            case GAME_STATE_THEIR_TURN:
                led_set(LED1, 1); /* turn the led on when its their turn to indicate they need to wait */
                update_receive_their_turn();
                break;
            case GAME_STATE_SHOWING_MESSAGE:
                update_scrolling_message();
                break;
            default: 
                break;
        }

    }
}
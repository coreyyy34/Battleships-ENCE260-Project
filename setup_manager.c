/** @file   setup_manager.c
 *  @author Corey Hines
 *  @date   17/10/2024
 */

#include "setup_manager.h"
#include <stdbool.h>
#include "navigation_switch.h"
#include "screen.h"
#include "button.h" /* todo - turn this into our own module*/
#include "ir.h"
#include "game_state.h"
#include "board.h"
#include "predefined_boards.h"
#include "game.h"

void update_select_player(void)
{
    static bool initialised = false;
    static bool player = 0;

    if (!initialised)
    {
        initialised = true;
        player = 0;
        screen_set_char(player ? '2' : '1');
    }

    button_update();
    
    switch (navigation_switch_get())
    {
        case DIR_EAST:
        case DIR_WEST:
            // there are only 2 players so we can just switch a boolean
            // true is player 2, false is player 1
            player = !player;
            screen_set_char(player ? '2' : '1');
            break;
        default:
            break;
    }
    if (button_push_event_p (0))
    {
        set_game_state(GAME_STATE_CHOOSE_BOARD);
        initialised = false;
        player_number = player ? 2 : 1;
    }
}

void update_receive_their_board(void)
{
    if (!received_their_board)
    {
        if (ir_get_their_predefined_board_id(&their_predefined_board_id))
        {
            received_their_board = true;
            their_board = create_board(PREDEFINED_BOARDS[their_predefined_board_id]);
        }
    } else if (sent_our_board) {
        // player 1 starts by sending a shot (selecting a shoot position initially)
        // player 2 starts by waiting for player 1's shot
        set_game_state(player_number == 1 ? GAME_STATE_SELECT_SHOOT_POSITION : GAME_STATE_THEIR_TURN);
    }
}

void update_choose_board(void)
{
static bool initialised = false;
    static uint8_t board_num = 0;

    if (!initialised)
    {
        screen_set_predefined_board(PREDEFINED_BOARDS[board_num]);
        initialised = true;
    }

    button_update();

    switch (navigation_switch_get())
    {
        case DIR_EAST:
            board_num = board_num == 0 ? NUM_BOARDS - 1 : board_num - 1;
            screen_set_predefined_board(PREDEFINED_BOARDS[board_num]);
            break;
        case DIR_WEST:
            board_num = board_num == NUM_BOARDS - 1 ? 0 : board_num + 1;
            screen_set_predefined_board(PREDEFINED_BOARDS[board_num]);
            break;
        default:
            break;
    }

    if (button_push_event_p (0))
    {
        // setup our board and send the predefined board to the other board
        our_board = create_board(PREDEFINED_BOARDS[board_num]);
        our_predefined_board_id = board_num;
        set_game_state(GAME_STATE_AWAIT_BOARD_EXCHANGE);

        ir_send_our_predefined_board_id(our_predefined_board_id);
        
        sent_our_board = true;
        initialised = false;
    }
}
/** @file   player_management.c
 *  @author Corey Hines
 *  @date   17/10/2024
 */

#include "player_management.h"
#include <stdbool.h>
#include "navigation_switch.h"
#include "message.h"
#include "button.h" /* todo - turn this into our own module*/
#include "game_state.h"
#include "game.h"

void update_select_player(void)
{
    static bool initialised = false;
    static bool player = 0;

    if (!initialised)
    {
        message_char(player ? '2' : '1');
        initialised = true;
    }

    button_update();
    
    switch (navigation_switch_get())
    {
        case DIR_EAST:
        case DIR_WEST:
            // there are only 2 players so we can just switch a boolean
            // true is player 2, false is player 1
            player = !player;
            message_char(player ? '2' : '1');
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
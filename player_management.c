#include <stdbool.h>
#include "player_management.h"

static void update_select_player(void)
{
    static bool initialised = false;
    static bool player = 0;

    if (!initialised)
    {
        message_char(player ? '2' : '1');
        initialised = true;
    }

    navswitch_update();
    button_update();
    
    if (navswitch_push_event_p(NAVSWITCH_EAST) || navswitch_push_event_p(NAVSWITCH_WEST))
    {
        player = !player;
        message_char(player ? '2' : '1');
    }
    if (button_push_event_p (0))
    {
        set_game_state(GAME_STATE_CHOOSE_BOARD);
        initialised = false;
        player_number = player ? 2 : 1;
    }
}
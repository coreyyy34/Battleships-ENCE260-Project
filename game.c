#include <string.h>
#include "system.h"
#include "button.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "game_state.h"
#include "message.h"
#include "predefined_boards.h"

#define PACER_RATE 500  // pacer ticks per second
#define TITLE_SCREEN_TEXT " BATTLESHIPS "

static GameState_t game_state = GAME_STATE_TITLE_SCREEN;

static void update_title_screen(void)
{
    static uint32_t ticks = 0;
    static uint32_t total_ticks = 0;
    static bool initialised = false;

    if (!initialised) 
    {
        // setup the title screen
        initialised = true;
        total_ticks = message_calculate_scrolling_message_ticks(TITLE_SCREEN_TEXT);
        message_scrolling_message(TITLE_SCREEN_TEXT);
    }

    if (ticks++ >= total_ticks)
    {
        game_state = GAME_STATE_SELECT_PLAYER;
        ticks = 0;
        total_ticks = 0;
        initialised = false;
    }
}

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
        game_state = GAME_STATE_CHOOSE_BOARD;
    }
}

static void update_choose_board(void)
{
    static bool initialised = false;
    static uint8_t board_num = 0;

    if (!initialised)
    {
        message_display_board(BOARDS[board_num]);
    }
}


int main(void)
{
    system_init();
    pacer_init(PACER_RATE);
    button_init ();
    message_init();

    while (1)
    {
        pacer_wait();
        tinygl_update();
        switch (game_state) 
        {
            case GAME_STATE_TITLE_SCREEN:
                update_title_screen();
                break;
            case GAME_STATE_SELECT_PLAYER:
                update_select_player();
                break;
            case GAME_STATE_CHOOSE_BOARD:
                update_choose_board();
                break;
            default: 
                break;
        }

    }
}
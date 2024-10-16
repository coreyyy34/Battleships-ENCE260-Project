#include <string.h>
#include "system.h"
#include "button.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "led.h"
#include "game_state.h"
#include "message.h"
#include "board.h"
#include "predefined_boards.h"
#include "ir.h"
#include "util.h"

#define PACER_RATE 500  // pacer ticks per second

static GameState_t prev_game_state = GAME_STATE_TITLE_SCREEN;
static GameState_t game_state = GAME_STATE_TITLE_SCREEN;

static char* scrolling_text = NULL;
static GameState_t scrolling_finish_state = GAME_STATE_TITLE_SCREEN;

static bool received_their_board = false;
static bool sent_our_board = false;
static uint8_t player_number;

static void set_game_state(GameState_t new_game_state)
{
    prev_game_state = game_state;
    game_state = new_game_state;
    message_clear();
}

static void set_scrolling_message(char* text, GameState_t finish_state)
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

static void update_choose_board(void)
{
    static bool initialised = false;
    static uint8_t board_num = 0;

    if (!initialised)
    {
        message_display_pre_defined_board(PREDEFINED_BOARDS[board_num]);
        initialised = true;
    }

    navswitch_update();
    button_update();

    if (navswitch_push_event_p(NAVSWITCH_EAST))
    {
        board_num = board_num == 0 ? NUM_BOARDS - 1 : board_num - 1;
        message_display_pre_defined_board(PREDEFINED_BOARDS[board_num]);
    }
    if (navswitch_push_event_p(NAVSWITCH_WEST))
    {
        board_num = board_num == NUM_BOARDS - 1 ? 0 : board_num + 1;
        message_display_pre_defined_board(PREDEFINED_BOARDS[board_num]);
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

static void update_receive_their_board(void)
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

static void update_select_shoot_position(void)
{
    static bool initialised = false;
    static uint8_t col = 2;
    static uint8_t row = 3;
    static int16_t ticks = 0;
    static bool explored_on = false;
    static bool previous_shot = false;
    static uint8_t player_hits = 0;

    // Initialize the starting position if not done already
    if (!initialised)
    {
        message_display_pixel(col, row, PIXEL_ON);
        initialised = true;
        previous_shot = false;
        ticks = 0;
    }

    navswitch_update();

    uint8_t prev_row = row;
    uint8_t prev_col = col;
    int8_t row_offset = 0;
    int8_t col_offset = 0;

    if (navswitch_push_event_p(NAVSWITCH_NORTH))        /* up */
        row_offset = -1;
    else if (navswitch_push_event_p(NAVSWITCH_SOUTH))   /* down */
        row_offset = 1;

    if (navswitch_push_event_p(NAVSWITCH_WEST))         /* left */
        col_offset = -1;
    else if (navswitch_push_event_p(NAVSWITCH_EAST))    /* right */
        col_offset = 1;

    // boundary checks
    row = (row + row_offset < LEDMAT_ROWS_NUM) ? (row + row_offset >= 0 ? row + row_offset : 0) : LEDMAT_ROWS_NUM - 1;
    col = (col + col_offset < LEDMAT_COLS_NUM) ? (col + col_offset >= 0 ? col + col_offset : 0) : LEDMAT_COLS_NUM - 1;

    // only update when a row or col has changed
    if (row != prev_row || col != prev_col)
    {
        // turn off previous only if it wasnt previously hit
        if (!previous_shot)
        {
            message_display_pixel(prev_col, prev_row, PIXEL_OFF);
        } 
        else 
        {
            previous_shot = false;
        }
    }
    

    if (navswitch_push_event_p(NAVSWITCH_PUSH))
    {
        BoardResponse_t response = board_check_our_shot_their_board(row, col);
        if (response == HIT) 
        {   
            player_hits++;
            if player_hits <= 12
            {
                set_game_state(GAME_STATE_VICTORY_MESSAGE)
            }   else    {

            
            ir_send_our_turn_state(HIT);
            set_scrolling_message(MESSAGE_HIT, GAME_STATE_THEIR_TURN);
            initialised = false;
            previous_shot = true;
            }
        }
        if (response == MISS)
        {
            ir_send_our_turn_state(MISS);
            set_scrolling_message(MESSAGE_MISS, GAME_STATE_THEIR_TURN);
            initialised = true;
            previous_shot = true;
        }
    }

    if (ticks++ == 100)
    {
        explored_on = !explored_on;
        message_display_pixel(prev_col, prev_row, explored_on);
        ticks = 0;
    }

    for (uint8_t cell_row = 0; cell_row < BOARD_ROWS_NUM; cell_row++)
    {
        for (uint8_t cell_col = 0; cell_col < BOARD_COLS_NUM; cell_col++)
        {
            // dont prevent it from flashing if we are on this current row, col
            if (cell_row != row || cell_col != col)
            {
                BoardCellState_t cell_state = (*their_board)[cell_row][cell_col];
                if (cell_state == SHIP_EXPLORED || cell_state == EMPTY_EXPLORED)
                {
                    message_display_pixel(cell_col, cell_row, PIXEL_ON);
                }
            }
        }
    }
}

static void update_receive_their_turn(void)
{
    static uint8_t opponent_hits = 0;
    BoardResponse_t response;
    if (ir_get_their_turn_state(&response)) 
    {
        if (response == HIT)
        {
            opponent_hits++;
            if (opponent_hits <= 12)
            {
                set_game_state(GAME_STATE_LOSS_MESSAGE);
            }   else    {

            set_scrolling_message(MESSAGE_HIT, GAME_STATE_SELECT_SHOOT_POSITION);
            }
        }
        else if (response == MISS)
        {
            set_scrolling_message(MESSAGE_MISS, GAME_STATE_SELECT_SHOOT_POSITION);
        }
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

    while (1)
    {
        pacer_wait();
        tinygl_update();
        switch (game_state) 
        {
            case GAME_STATE_TITLE_SCREEN:
                // skip the title screen and go straight to choose player state for quick launch
                // set_scrolling_message(" BATTLESHIPS ", GAME_STATE_SELECT_PLAYER);
                set_game_state(GAME_STATE_SELECT_PLAYER);
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
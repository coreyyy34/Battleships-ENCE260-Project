#include "board_manager.h"
#include "board.h"
#include "message.h"
#include "game_state.h"
#include "game.h"
#include "ir.h"
#include "navigation_switch.h"
#include <stdint.h>
#include <stdbool.h>

static void update_showing_explored_cells(uint8_t row, uint8_t col)
{
    static bool initialised;
    static uint8_t explored_ticks = 0;
    static bool explored_on = false;

    if (!initialised)
    {
        explored_ticks = 0;
        explored_on = false;
        initialised = true;
    }

    if (explored_ticks++ == 10)
    {
        explored_on = !explored_on;
        for (uint8_t cell_row = 0; cell_row < BOARD_ROWS_NUM; cell_row++)
        {
            for (uint8_t cell_col = 0; cell_col < BOARD_COLS_NUM; cell_col++)
            {
                // dont prevent it from flashing if we are on this current row, col
                if (cell_row != row || cell_col != col)
                {
                    BoardCellState_t cell_state = (*their_board)[cell_row][cell_col];
                    if (cell_state == SHIP_EXPLORED)
                    {
                        message_display_pixel(cell_col, cell_row, explored_on);
                    }
                    else if (cell_state == EMPTY_EXPLORED)
                    {
                        message_display_pixel(cell_col, cell_row, PIXEL_ON);
                    }
                }
            }
        }
        explored_ticks = 0;
    }
}

static void update_showing_cursor(uint8_t row, uint8_t col)
{
    static bool initialised;
    static uint8_t cursor_ticks = 0;
    static bool cursor_on = false;

    if (!initialised)
    {
        cursor_ticks = 0;
        cursor_on = false;
        initialised = true;
    }

    if (cursor_ticks++ == 100)
    {
        cursor_on = !cursor_on;
        message_display_pixel(col, row, cursor_on);
        cursor_ticks = 0;
    }
}

void update_receive_their_turn(void)
{
    static uint8_t ticks = 0;
    static bool initialise = false;

    if (!initialise)
    {
        ticks = 0;
        initialise = true;
    }

    // wait 250 ticks (~0.5 seconds) before trying to receive their response
    // as there are troubles with receiving our own signal
    if (ticks != 250) {
        ticks++;
        return;
    }
    BoardResponse_t response;
    if (ir_get_their_turn_state(&response)) 
    {
        if (response == HIT)
        {
            set_scrolling_message(MESSAGE_HIT, GAME_STATE_SELECT_SHOOT_POSITION);
            initialise = false;
        }
        else if (response == MISS)
        {
            set_scrolling_message(MESSAGE_MISS, GAME_STATE_SELECT_SHOOT_POSITION);
            initialise = false;
        }
        else if (response == WINNER)
        {
            // if they won we lost :(
            set_scrolling_message(MESSAGE_LOSER, GAME_STATE_END);
            initialise = false;
        }
    }
}

void update_select_shoot_position(void)
{
    static bool initialised = false;
    static uint8_t col = 2;
    static uint8_t row = 3;
    static bool previous_shot = false;

    // Initialize the starting position if not done already
    if (!initialised)
    {
        message_display_pixel(col, row, PIXEL_ON);
        initialised = true;
        previous_shot = false;
    }


    uint8_t prev_row = row;
    uint8_t prev_col = col;
    int8_t row_offset = 0;
    int8_t col_offset = 0;

    switch (navigation_switch_get())
    {
        case DIR_NORTH:
            row_offset = -1;
            break;
        case DIR_SOUTH:
            row_offset = 1;
            break;
        case DIR_WEST:
            col_offset = -1;
            break;
        case DIR_EAST:
            col_offset = 1;
            break;
        case DIR_PUSHED: {
            BoardResponse_t response = board_check_our_shot_their_board(row, col);
            if (response == HIT) 
            {   
                ir_send_our_turn_state(HIT);
                set_scrolling_message(MESSAGE_HIT, GAME_STATE_THEIR_TURN);
                previous_shot = true;
                initialised = false;
            }
            else if (response == MISS)
            {
                ir_send_our_turn_state(MISS);
                set_scrolling_message(MESSAGE_MISS, GAME_STATE_THEIR_TURN);
                initialised = false;
                previous_shot = true;
            }
            else if (response == WINNER)
            {
                // other board will interpret receiving WINNER as we won and they lost
                ir_send_our_turn_state(WINNER);
                set_scrolling_message(MESSAGE_WINNER, GAME_STATE_END);
                initialised = false;
            }
            break;
        }
        default:
            break;
    }

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
   
    update_showing_explored_cells(row, col);
    update_showing_cursor(row, col);
}
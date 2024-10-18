/** 
 * @file   ir.c
 * @brief  Implementation of IR communication functions for the Battleship game.
 *
 * This file contains the implementation of functions for handling IR communication
 * in the Battleship game. It includes functions for sending and receiving predefined
 * board IDs and turn states via IR communication, using specific prefixes to identify
 * the type of data being transmitted.
 *
 * @date   17/10/2024
 * @author Corey Hines
 */

#include <stdint.h>
#include "ir_uart.h"
#include "ir.h"

/**
 * @brief Retrieves the opponent's predefined board ID via IR communication.
 *
 * This function checks if there is data ready to be read from the IR receiver.
 * If the data has the correct prefix, it extracts the predefined board ID and
 * stores it in the provided pointer.
 *
 * @param id Pointer to store the received predefined board ID.
 * @return true if a valid board ID was received, false otherwise.
 */
bool ir_get_their_predefined_board_id(uint8_t* id)
{
    if (ir_uart_read_ready_p()) {
        uint8_t received = (uint8_t) ir_uart_getc();
        if ((received & 0xF0) == BOARD_ID_PREFIX) { 
            *id = GET_BOARD_ID(received);
            return true;
        }
    }
    return false;
}

/**
 * @brief Sends our predefined board ID via IR communication.
 *
 * This function sends our predefined board ID to the opponent via IR communication.
 * The board ID is prefixed with a specific identifier to indicate its type.
 *
 * @param id The predefined board ID to send.
 */
void ir_send_our_predefined_board_id(uint8_t id)
{
    char prefixed_id = BOARD_ID_PREFIX | (id & 0x0F);
    ir_uart_putc(prefixed_id);
}

/**
 * @brief Retrieves the opponent's turn state via IR communication.
 *
 * This function checks if there is data ready to be read from the IR receiver.
 * If the data has the correct prefix, it extracts the turn state and stores it
 * in the provided pointer.
 *
 * @param response Pointer to store the received turn state.
 * @return true if a valid response was received, false otherwise.
 */
bool ir_get_their_turn_state(BoardResponse_t* response)
{
    if (ir_uart_read_ready_p()) {
        uint8_t received = (uint8_t) ir_uart_getc();
        if ((received & 0xF0) == BOARD_RESPONSE_PREFIX) { 
            *response = (BoardResponse_t) GET_BOARD_RESPONSE(received);
            return true;
        }
    }
    return false;
}

/**
 * @brief Sends our turn state via IR communication.
 *
 * This function sends our turn state to the opponent via IR communication.
 * The turn state is prefixed with a specific identifier to indicate its type.
 *
 * @param response The board response to send.
 */
void ir_send_our_turn_state(BoardResponse_t response)
{
    char prefixed_response = BOARD_RESPONSE_PREFIX | (response & 0x0F);
    ir_uart_putc(prefixed_response);
}
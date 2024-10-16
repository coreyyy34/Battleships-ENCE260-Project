#include <stdint.h>
#include "ir_uart.h"
#include "ir.h"

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

void ir_send_our_predefined_board_id(uint8_t id)
{
    char prefixed_id = BOARD_ID_PREFIX | (id & 0x0F);
    ir_uart_putc(prefixed_id);
}

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

void ir_send_our_turn_state(BoardResponse_t response)
{
    char prefixed_response = BOARD_RESPONSE_PREFIX | (response & 0x0F);
    ir_uart_putc(prefixed_response);
}
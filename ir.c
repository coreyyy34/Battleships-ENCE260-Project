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

void ir_send_our_shot(uint8_t col, uint8_t row)
{
    char encoded_col_row = ENCODE_COL_ROW(col, row);
    ir_uart_putc(encoded_col_row);
}

bool ir_get_their_shot(uint8_t* col, uint8_t* row)
{
    if (ir_uart_read_ready_p()) {
        char encoded = ir_uart_getc();
        *col = (uint8_t) DECODE_COL(encoded);
        *col = (uint8_t) DECODE_ROW(encoded);
        return true;
    }
    return false;
}

bool ir_get_their_ack(IR_Status_t* status)
{
    if (ir_uart_read_ready_p()) {
        *status = (IR_Status_t) ir_uart_getc();
        return true;
    }
    return false;
}

void send_ack(IR_Status_t status)
{
    ir_uart_putc((char) status);
}

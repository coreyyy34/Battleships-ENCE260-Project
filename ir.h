#ifndef IR_H
#define IR_H

#include <stdint.h>
#include "ir_uart.h"
#include "board.h"

#define BOARD_ID_PREFIX 0xA0
#define BOARD_RESPONSE_PREFIX 0xB0
#define GET_BOARD_ID(data) ((data) & 0x0F)
#define GET_BOARD_RESPONSE(data) ((data) & 0x0F)
#define ENCODE_COL_ROW(col, row) (col << 3 | row)
#define DECODE_COL(encoded) (encoded >> 3)
#define DECODE_ROW(encoded) (encoded & 0x7)

typedef enum {
    NO_RESPONSE = 0x40,
    RECEIVED_BOARD = 0x41,
} IR_Status_t;

bool ir_get_their_predefined_board_id(uint8_t* id);
void ir_send_our_predefined_board_id(uint8_t id);

bool ir_get_their_turn_state(BoardResponse_t* response);
void ir_send_our_turn_state(BoardResponse_t response);

#endif

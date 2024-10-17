#ifndef IR_H
#define IR_H

#include <stdint.h>
#include "ir_uart.h"
#include "board.h"

/**
 * @brief Prefix for sending predefined board IDs over IR communication.
 */
#define BOARD_ID_PREFIX 0xA0

/**
 * @brief Prefix for sending board response states over IR communication.
 */
#define BOARD_RESPONSE_PREFIX 0xB0

/**
 * @brief Macro to extract the predefined board ID from received data.
 * @param data The data received over IR communication.
 * @return The predefined board ID (last 4 bits of the data).
 */
#define GET_BOARD_ID(data) ((data) & 0x0F)

/**
 * @brief Macro to extract the board response from received data.
 * @param data The data received over IR communication.
 * @return The board response (last 4 bits of the data).
 */
#define GET_BOARD_RESPONSE(data) ((data) & 0x0F)

/**
 * @brief Retrieves the opponent's predefined board ID via IR communication.
 * @param id Pointer to store the received predefined board ID.
 * @return true if a valid board ID was received, false otherwise.
 */
bool ir_get_their_predefined_board_id(uint8_t* id);

/**
 * @brief Sends our predefined board ID via IR communication.
 * @param id The predefined board ID to send.
 */
void ir_send_our_predefined_board_id(uint8_t id);

/**
 * @brief Retrieves the opponent's turn state via IR communication.
 * @param response Pointer to store the received turn state.
 * @return true if a valid response was received, false otherwise.
 */
bool ir_get_their_turn_state(BoardResponse_t* response);

/**
 * @brief Sends our turn state via IR communication.
 * @param response The board response to send.
 */
void ir_send_our_turn_state(BoardResponse_t response);

#endif /* IR_H */

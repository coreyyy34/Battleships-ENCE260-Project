#ifndef PREDEFINED_BOARDS_H
#define PREDEFINED_BOARDS_H

#include <stdint.h>

const PredefinedBoard_t BOARD_0 = {
    0b0000000, 
    0b0000000, 
    0b0000000, 
    // 0b0001010,
    0b0000100,      /* temp only have 1 point in center so testing is easy */
    0b0000000, 
    0b0000000, 
    0b0000000};
const PredefinedBoard_t BOARD_1 = {
    0b00011000, 
    0b11000000, 
    0b00000001, 
    0b00000001, 
    0b11110001, 
    0b00000000, 
    0b01100000};
const PredefinedBoard_t BOARD_2 = {
    0b00011101, 
    0b00010000, 
    0b00110000, 
    0b00001000, 
    0b00010100, 
    0b00001000, 
    0b00000000};
const PredefinedBoard_t BOARD_3 = {
    0b00000001, 
    0b00010001, 
    0b00010101, 
    0b00010101, 
    0b00000011, 
    0b00000000, 
    0b11000000};
const PredefinedBoard_t BOARD_4 = {
    0b00010100, 
    0b00010100, 
    0b00000100, 
    0b00011000, 
    0b00011100, 
    0b00000000, 
    0b11000000};
const PredefinedBoard_t BOARD_5 = {
    0b00100001, 
    0b00100001, 
    0b00000001, 
    0b00000011, 
    0b00111000, 
    0b00000000, 
    0b00111000};


const uint8_t NUM_BOARDS = 6;

const PredefinedBoard_t* PREDEFINED_BOARDS[] = {
    &BOARD_0,
    &BOARD_1,
    &BOARD_2,
    &BOARD_3,
    &BOARD_4,
    &BOARD_5
};

#endif
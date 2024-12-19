/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 15.03.2024 00:17:17
 Libraries   :
 Author      :
 Description :
******************************************************************/

#include <Arduino.h>
#include "IO.h"
#include "INIT.h"

// bresenham.h
#ifndef REDIRECTION_H
#define REDIRECTION_H

void Redirection(uint8_t matrix[][NBR_COL_MATRIX], uint16_t countInterCycle);

inline void FillColumn0(uint8_t matrix[][NBR_COL_MATRIX], uint8_t col, uint8_t bit);
inline void FillColumn1(uint8_t matrix[][NBR_COL_MATRIX], uint8_t col, uint8_t bit);
inline void FillColumnBrenham(uint8_t matrix[][NBR_COL_MATRIX], uint8_t motorIndex, uint8_t col, uint8_t bit, uint16_t countInterCycle);

#endif // BRESENHAM_H


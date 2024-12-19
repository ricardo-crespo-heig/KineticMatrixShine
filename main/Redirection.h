 /************************************************************************************
 * @file        Redirection.h
 * @project     KineticMatrixShine
 * @author      Ricardo Crespo
 * @date        19.12.2024
 * @brief       Header of redirection functions
 ************************************************************************************/

#ifndef REDIRECTION_H
#define REDIRECTION_H

void Redirection(uint8_t matrix[][NBR_COL_MATRIX], uint16_t countInterCycle);

inline void FillColumn0(uint8_t matrix[][NBR_COL_MATRIX], uint8_t col, uint8_t bit);
inline void FillColumn1(uint8_t matrix[][NBR_COL_MATRIX], uint8_t col, uint8_t bit);
inline void FillColumnBrenham(uint8_t matrix[][NBR_COL_MATRIX], uint8_t motorIndex, uint8_t col, uint8_t bit, uint16_t countInterCycle);

#endif

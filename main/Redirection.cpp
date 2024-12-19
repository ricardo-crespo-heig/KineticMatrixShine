/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 15.03.2024 00:17:00
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/

#include <Arduino.h>
#include "INIT.h"
#include "IO.h"
#include "REDIRECTION.h"
#include "BRESENHAM.h"
#include "SEQUENCE.h"

Bresenham bresenham(BUFFER_SIZE);

void Redirection(uint8_t matrix[][NBR_COL_MATRIX], uint16_t countInterCycle)
{
    uint8_t dirCW = false;

    if((tbSteps[countInterCycle][0]) > 0)
    {
      dirCW = true;
    }
    else
    {
      dirCW = false;
    }

    // SLEEPA2
    (tbSteps[countInterCycle]) ? FillColumn1(matrix, 0, 0) : FillColumn0(matrix, 0, 0);

    /// MOTOR 1
    // SLEEPA1
    (tbSteps[countInterCycle]) ? FillColumn1(matrix, 6, 0) : FillColumn0(matrix, 6, 0);
    // STEPA1
    FillColumnBrenham(matrix, 6, 6, countInterCycle);
    // SLEEPA1
    (dirCW) ? FillColumn1(matrix, 6, 0) : FillColumn0(matrix, 6, 0);
}

// Fonction inline pour remplir une colonne
inline void FillColumn0(uint8_t matrix[][NBR_COL_MATRIX], uint8_t col, uint8_t bit) 
{
    for (uint16_t i = 0; i < BUFFER_SIZE; i++) 
    {
        matrix[i][col] &= ~(1 << bit); // Désactive le bit spécifié
    }
}

// Fonction inline pour remplir une colonne
inline void FillColumn1(uint8_t matrix[][NBR_COL_MATRIX], uint8_t col, uint8_t bit) 
{
    for (uint16_t i = 0; i < BUFFER_SIZE; i++) 
    {
        matrix[i][col] |= (1 << bit);  // Active le bit spécifié
    }
}

inline void FillColumnBrenham(uint8_t matrix[][NBR_COL_MATRIX], uint8_t col, uint8_t bit, uint16_t countInterCycle)
{
    bresenham.init(tbSteps[countInterCycle][0]);

    for (int i = 0; i < BUFFER_SIZE; i++) 
    {
        matrix[i][col] = (matrix[i][col] & ~(1 << bit)) | (bresenham.calculatePoint() << bit);
    }
}


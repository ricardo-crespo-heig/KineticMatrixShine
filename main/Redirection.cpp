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

//Bresenham bresenham(BUFFER_SIZE);
Bresenham bresenham(BUFFER_SIZE, NBR_MOTORS);

void Redirection(uint8_t matrix[][NBR_COL_MATRIX], uint16_t countInterCycle)
{
    //bool dirCW = false;
    bool tbDirCW[NBR_MOTORS]; 
    uint8_t actualMotor = 0;
    /*if((tbSteps[countInterCycle][0]) > 0)
    {
      dirCW = true;
    }
    else
    {
      dirCW = false;
    }*/

    for (uint8_t motorIndex = 0; motorIndex < NBR_MOTORS; motorIndex++) {
        if (tbSteps[countInterCycle][motorIndex] > 0) {
            tbDirCW[motorIndex] = true; // Moteur tourne dans le sens CW
        } else {
            tbDirCW[motorIndex] = false; // Moteur tourne dans le sens CCW
        }
    }


    // MOTOR 0
    actualMotor = 0;
    // SLEEPA1
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTH, BIT0) : FillColumn0(matrix, MPORTH, BIT0);
    // STEPA1
    FillColumnBrenham(matrix, actualMotor, MPORTH, BIT6, countInterCycle);
    // DIRA1
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTD, BIT3) : FillColumn0(matrix, MPORTD, BIT3);

    // MOTOR 1
    actualMotor = 1;
    // SLEEPA2
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTA, BIT0) : FillColumn0(matrix, MPORTA, BIT0);
    // STEPA2
    FillColumnBrenham(matrix, actualMotor, MPORTH, BIT5, countInterCycle);
    // DIRA2
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTH, BIT1) : FillColumn0(matrix, MPORTH, BIT1);

    // MOTOR 2
    actualMotor = 2;
    // SLEEPA3
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTA, BIT2) : FillColumn0(matrix, MPORTA, BIT2);
    // STEPA3
    FillColumnBrenham(matrix, actualMotor, MPORTH, BIT4, countInterCycle);
    // DIRA3
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTA, BIT1) : FillColumn0(matrix, MPORTA, BIT1);

    // MOTOR 3
    actualMotor = 3;
    // SLEEPA4
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTA, BIT4) : FillColumn0(matrix, MPORTA, BIT4);
    // STEPA4
    FillColumnBrenham(matrix, actualMotor, MPORTH, BIT3, countInterCycle);
    // DIRA4
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTA, BIT3) : FillColumn0(matrix, MPORTA, BIT3);

    /*Serial.println("DIR " + String(tbDirCW[0]));
    Serial.println("DIR " + String(tbDirCW[1]));
    Serial.println("CountInterCycle " + String(countInterCycle));
    Serial.println("tbSteps[countInterCycle][0] " + String(tbSteps[countInterCycle][0]));

    // Parcourir et afficher le tableau
    for (int i = 0; i < BUFFER_SIZE; i++) {
        for (int j = 0; j < NBR_COL_MATRIX; j++) {
            Serial.print(matrix[i][j]);
            Serial.print("\t"); // Tabulation entre les colonnes
        }
        Serial.println(); // Saut de ligne après chaque ligne
        Serial.println(); // Saut de ligne après chaque ligne
    }*/
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

inline void FillColumnBrenham(uint8_t matrix[][NBR_COL_MATRIX], uint8_t motorIndex, uint8_t col, uint8_t bit, uint16_t countInterCycle)
{
    //bresenham.init(tbSteps[countInterCycle][0]);
    bresenham.init(tbSteps[countInterCycle][motorIndex], motorIndex);


    for (int i = 0; i < BUFFER_SIZE; i++) 
    {
        //matrix[i][col] = (matrix[i][col] & ~(1 << bit)) | (bresenham.calculatePoint() << bit);
        matrix[i][col] = (matrix[i][col] & ~(1 << bit)) | (bresenham.calculatePoint(motorIndex) << bit);
    }
}


 /************************************************************************************
 * @file        Redirection.cpp
 * @project     KineticMatrixShine
 * @author      Ricardo Crespo
 * @date        19.12.2024
 * @brief       Redirection functions
 ************************************************************************************/

#include <Arduino.h>
#include "INIT.h"
#include "IO.h"
#include "REDIRECTION.h"
#include "BRESENHAM.h"
#include "SEQUENCE.h"

Bresenham motors[NBR_MOTORS] = 
{
    Bresenham(BUFFER_SIZE),
    Bresenham(BUFFER_SIZE),
    Bresenham(BUFFER_SIZE),
    Bresenham(BUFFER_SIZE),
    Bresenham(BUFFER_SIZE),
    Bresenham(BUFFER_SIZE),
    Bresenham(BUFFER_SIZE),
    Bresenham(BUFFER_SIZE),
    Bresenham(BUFFER_SIZE),
    Bresenham(BUFFER_SIZE),
    Bresenham(BUFFER_SIZE),
    Bresenham(BUFFER_SIZE),
    Bresenham(BUFFER_SIZE),
    Bresenham(BUFFER_SIZE),
    Bresenham(BUFFER_SIZE),
    Bresenham(BUFFER_SIZE)
};

void Redirection(uint8_t matrix[][NBR_COL_MATRIX], uint16_t countInterCycle)
{
    bool tbDirCW[NBR_MOTORS]; 
    uint8_t actualMotor = 0;

    for (uint8_t motorIndex = 0; motorIndex < NBR_MOTORS; motorIndex++) {
        if (tbSteps[countInterCycle][motorIndex] > 0) {
            tbDirCW[motorIndex] = true; // Moteur tourne dans le sens CW
        } else {
            tbDirCW[motorIndex] = false; // Moteur tourne dans le sens CCW
        }
    }

    // MOTOR 0
    actualMotor = MOT0;
    // SLEEPA1
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTH, BIT0) : FillColumn0(matrix, MPORTH, BIT0);
    //(true) ? FillColumn1(matrix, MPORTH, BIT0) : FillColumn0(matrix, MPORTH, BIT0);
    // STEPA1
    FillColumnBrenham(matrix, actualMotor, MPORTH, BIT6, countInterCycle);
    // DIRA1
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTD, BIT3) : FillColumn0(matrix, MPORTD, BIT3);

    // MOTOR 1
    actualMotor = MOT1;
    // SLEEPA2
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTA, BIT0) : FillColumn0(matrix, MPORTA, BIT0);
    //(true) ? FillColumn1(matrix, MPORTA, BIT0) : FillColumn0(matrix, MPORTA, BIT0);
    // STEPA2
    FillColumnBrenham(matrix, actualMotor, MPORTH, BIT5, countInterCycle);
    // DIRA2
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTH, BIT1) : FillColumn0(matrix, MPORTH, BIT1);

    // MOTOR 2
    actualMotor = MOT2;
    // SLEEPA3
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTA, BIT2) : FillColumn0(matrix, MPORTA, BIT2);
    //(true) ? FillColumn1(matrix, MPORTA, BIT2) : FillColumn0(matrix, MPORTA, BIT2);
    // STEPA3
    FillColumnBrenham(matrix, actualMotor, MPORTH, BIT4, countInterCycle);
    // DIRA3
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTA, BIT1) : FillColumn0(matrix, MPORTA, BIT1);

    // MOTOR 3
    actualMotor = MOT3;
    // SLEEPA4
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTA, BIT4) : FillColumn0(matrix, MPORTA, BIT4);
    //(true) ? FillColumn1(matrix, MPORTA, BIT4) : FillColumn0(matrix, MPORTA, BIT4);
    // STEPA4
    FillColumnBrenham(matrix, actualMotor, MPORTH, BIT3, countInterCycle);
    // DIRA4
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTA, BIT3) : FillColumn0(matrix, MPORTA, BIT3);


    // MOTOR 4
    actualMotor = MOT4;
    // SLEEPB1
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTG, BIT1) : FillColumn0(matrix, MPORTG, BIT1);
    // STEPB1
    FillColumnBrenham(matrix, actualMotor, MPORTB, BIT7, countInterCycle);
    // DIRB1
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTG, BIT0) : FillColumn0(matrix, MPORTG, BIT0);

    // MOTOR 5
    actualMotor = MOT5;
    // SLEEPB2
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTD, BIT7) : FillColumn0(matrix, MPORTD, BIT7);
    // STEPB2
    FillColumnBrenham(matrix, actualMotor, MPORTB, BIT6, countInterCycle);
    // DIRB2
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTG, BIT2) : FillColumn0(matrix, MPORTG, BIT2);

    // MOTOR 6
    actualMotor = MOT6;
    // SLEEPB3
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTC, BIT1) : FillColumn0(matrix, MPORTC, BIT1);
    // STEPB3
    FillColumnBrenham(matrix, actualMotor, MPORTB, BIT5, countInterCycle);
    // DIRB3
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTC, BIT0) : FillColumn0(matrix, MPORTC, BIT0);

    // MOTOR 7
    actualMotor = MOT7;
    // SLEEPB4
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTC, BIT3) : FillColumn0(matrix, MPORTC, BIT3);
    // STEPB4
    FillColumnBrenham(matrix, actualMotor, MPORTB, BIT4, countInterCycle);
    // DIRB4
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTC, BIT2) : FillColumn0(matrix, MPORTC, BIT2);


    // MOTOR 8
    actualMotor = MOT8;
    // SLEEPC1
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTA, BIT6) : FillColumn0(matrix, MPORTA, BIT6);
    // STEPC1
    FillColumnBrenham(matrix, actualMotor, MPORTE, BIT1, countInterCycle);
    // DIRC1
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTA, BIT5) : FillColumn0(matrix, MPORTA, BIT5);

    // MOTOR 9
    actualMotor = MOT9;
    // SLEEPC2
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTC, BIT7) : FillColumn0(matrix, MPORTC, BIT7);
    // STEPC2
    FillColumnBrenham(matrix, actualMotor, MPORTL, BIT5, countInterCycle);
    // DIRC2
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTA, BIT7) : FillColumn0(matrix, MPORTA, BIT7);

    // MOTOR 10
    actualMotor = MOT10;
    // SLEEPC3
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTC, BIT5) : FillColumn0(matrix, MPORTC, BIT5);
    // STEPC3
    FillColumnBrenham(matrix, actualMotor, MPORTL, BIT4, countInterCycle);
    // DIRC3
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTC, BIT6) : FillColumn0(matrix, MPORTC, BIT6);

    // MOTOR 11
    actualMotor = MOT11;
    // SLEEPC4
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTL, BIT6) : FillColumn0(matrix, MPORTL, BIT6);
    // STEPC4
    FillColumnBrenham(matrix, actualMotor, MPORTL, BIT3, countInterCycle);
    // DIRC4
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTC, BIT4) : FillColumn0(matrix, MPORTC, BIT4);


    // MOTOR 12
    actualMotor = MOT12;
    // SLEEPD1
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTB, BIT1) : FillColumn0(matrix, MPORTB, BIT1);
    // STEPD1
    FillColumnBrenham(matrix, actualMotor, MPORTE, BIT3, countInterCycle);
    // DIRD1
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTB, BIT0) : FillColumn0(matrix, MPORTB, BIT0);

    // MOTOR 13
    actualMotor = MOT13;
    // SLEEPD2
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTB, BIT3) : FillColumn0(matrix, MPORTB, BIT3);
    // STEPD2
    FillColumnBrenham(matrix, actualMotor, MPORTG, BIT5, countInterCycle);
    // DIRD2
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTB, BIT2) : FillColumn0(matrix, MPORTB, BIT2);

    // MOTOR 14
    actualMotor = MOT14;
    // SLEEPD3
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTL, BIT1) : FillColumn0(matrix, MPORTL, BIT1);
    // STEPD3
    FillColumnBrenham(matrix, actualMotor, MPORTE, BIT5, countInterCycle);
    // DIRD3
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTL, BIT0) : FillColumn0(matrix, MPORTL, BIT0);

    // MOTOR 15
    actualMotor = MOT15;
    // SLEEPD4
    (tbSteps[countInterCycle][actualMotor]) ? FillColumn1(matrix, MPORTL, BIT7) : FillColumn0(matrix, MPORTL, BIT7);
    // STEPD4
    FillColumnBrenham(matrix, actualMotor, MPORTE, BIT4, countInterCycle);
    // DIRD4
    (tbDirCW[actualMotor]) ? FillColumn1(matrix, MPORTL, BIT2) : FillColumn0(matrix, MPORTL, BIT2);

    // DEBUG
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
    motors[motorIndex].SetTarget(tbSteps[countInterCycle][motorIndex]); 

    for (int i = 0; i < BUFFER_SIZE; i++) 
    {
        matrix[i][col] = (matrix[i][col] & ~(1 << bit)) | (motors[motorIndex].CalNextPoint() << bit);
    }
}

 /************************************************************************************
 * @file        IO.cpp
 * @project     KineticMatrixShine
 * @author      Ricardo Crespo
 * @date        02.11.2024
 * @brief       IO functions
 ************************************************************************************/

#include <Arduino.h>
#include "IO.h"

void InitIO()
{
    //pinMode(CMDU,INPUT);
    pinMode(STEPA1,OUTPUT); 
    pinMode(STEPA2,OUTPUT); 
    pinMode(STEPA3,OUTPUT); 
    pinMode(STEPA4,OUTPUT); 

 
    pinMode(DIRA1,OUTPUT);
    pinMode(DIRA2,OUTPUT);
    pinMode(DIRA3,OUTPUT);
    pinMode(DIRA4,OUTPUT);


    pinMode(SLEEPA1, OUTPUT);
    pinMode(SLEEPA2, OUTPUT);
    pinMode(SLEEPA3, OUTPUT);
    pinMode(SLEEPA4, OUTPUT);

}

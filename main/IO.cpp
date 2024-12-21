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
    pinMode(STEPA1,OUTPUT); 
    pinMode(STEPA2,OUTPUT); 
    pinMode(STEPA3,OUTPUT); 
    pinMode(STEPA4,OUTPUT); 

    pinMode(STEPB1,OUTPUT); 
    pinMode(STEPB2,OUTPUT); 
    pinMode(STEPB3,OUTPUT); 
    pinMode(STEPB4,OUTPUT); 

    pinMode(STEPC1,OUTPUT); 
    pinMode(STEPC2,OUTPUT); 
    pinMode(STEPC3,OUTPUT); 
    pinMode(STEPC4,OUTPUT); 

    pinMode(STEPD1,OUTPUT); 
    pinMode(STEPD2,OUTPUT); 
    pinMode(STEPD3,OUTPUT); 
    pinMode(STEPD4,OUTPUT); 
 

    pinMode(DIRA1,OUTPUT);
    pinMode(DIRA2,OUTPUT);
    pinMode(DIRA3,OUTPUT);
    pinMode(DIRA4,OUTPUT);

    pinMode(DIRB1,OUTPUT);
    pinMode(DIRB2,OUTPUT);
    pinMode(DIRB3,OUTPUT);
    pinMode(DIRB4,OUTPUT);

    pinMode(DIRC1,OUTPUT);
    pinMode(DIRC2,OUTPUT);
    pinMode(DIRC3,OUTPUT);
    pinMode(DIRC4,OUTPUT);

    pinMode(DIRD1,OUTPUT);
    pinMode(DIRD2,OUTPUT);
    pinMode(DIRD3,OUTPUT);
    pinMode(DIRD4,OUTPUT);


    pinMode(SLEEPA1, OUTPUT);
    pinMode(SLEEPA2, OUTPUT);
    pinMode(SLEEPA3, OUTPUT);
    pinMode(SLEEPA4, OUTPUT);

    pinMode(SLEEPB1, OUTPUT);
    pinMode(SLEEPB2, OUTPUT);
    pinMode(SLEEPB3, OUTPUT);
    pinMode(SLEEPB4, OUTPUT);

    pinMode(SLEEPC1, OUTPUT);
    pinMode(SLEEPC2, OUTPUT);
    pinMode(SLEEPC3, OUTPUT);
    pinMode(SLEEPC4, OUTPUT);

    pinMode(SLEEPD1, OUTPUT);
    pinMode(SLEEPD2, OUTPUT);
    pinMode(SLEEPD3, OUTPUT);
    pinMode(SLEEPD4, OUTPUT);

}

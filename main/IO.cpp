/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 14.03.2024 23:54:45
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/

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

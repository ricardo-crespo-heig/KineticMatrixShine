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
    pinMode(CMDU,INPUT);
    pinMode(STEP1,OUTPUT); 
    pinMode(STEP2,OUTPUT); 
    pinMode(STEP3,OUTPUT); 
    pinMode(STEP4,OUTPUT); 
    pinMode(STEPU,OUTPUT); 
    pinMode(DIR1,OUTPUT);
    pinMode(DIR2,OUTPUT);
    pinMode(DIR3,OUTPUT);
    pinMode(DIR4,OUTPUT);
    pinMode(DIRU,OUTPUT);
    pinMode(SLEEP1, OUTPUT);
    pinMode(SLEEP2, OUTPUT);
    pinMode(SLEEP3, OUTPUT);
    pinMode(SLEEP4, OUTPUT);
    pinMode(SLEEPU, OUTPUT);
}

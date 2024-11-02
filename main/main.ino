/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 14.03.2024 23:45:26
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/

#include <Arduino.h>
#include "IO.h"
#include "TESTMOTORS.h"
 
// defines pins numbers

 
void setup() 
{
    InitIO();
}

void loop() 
{
 
    //TestMotors();
    //CalibDriver();
    
    if(digitalRead(CMDU))
    {
        TestMotorsU();
    }
    else
    {
        CalibDriverU();
    }


}
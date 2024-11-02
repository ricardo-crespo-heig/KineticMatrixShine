/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 15.03.2024 00:17:00
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/

#include <Arduino.h>
#include "TESTMOTORS.h"
#include "IO.h"

//#define PULSES  12800
#define PULSES  6400
#define DELAY   1

void TestMotors()
{
    digitalWrite(DIRA1,HIGH); // Enables the motor to move in a particular direction
    digitalWrite(DIRA2,HIGH);
    digitalWrite(DIRA3,HIGH);
    digitalWrite(DIRA4,HIGH);
    digitalWrite(SLEEPA1, HIGH);
    digitalWrite(SLEEPA2, HIGH);
    digitalWrite(SLEEPA3, HIGH);
    digitalWrite(SLEEPA4, HIGH);
    // Makes 200 pulses for making one full cycle rotation
    for(int x = 0; x < PULSES; x++) {
        //digitalWrite(stepPin,HIGH); 
        //analogWrite(STEP1, 500);
        //analogWrite(STEP2, 500);
        //analogWrite(STEP3, 500);
        //analogWrite(STEP4, 500);
        //delayMicroseconds(500); 
        //digitalWrite(stepPin,LOW); 
        //analogWrite(STEP1, 0);
        //analogWrite(STEP2, 0);
        //analogWrite(STEP3, 0);
        //analogWrite(STEP4, 0);
        //delayMicroseconds(500); 
        digitalWrite(STEPA1,HIGH);
        digitalWrite(STEPA2,HIGH);
        digitalWrite(STEPA3,HIGH);
        digitalWrite(STEPA4,HIGH);
        delayMicroseconds(DELAY);
        digitalWrite(STEPA1,LOW);
        digitalWrite(STEPA2,LOW);
        digitalWrite(STEPA3,LOW);
        digitalWrite(STEPA4,LOW);
        delayMicroseconds(DELAY);
    }
    digitalWrite(SLEEPA1, LOW);
    digitalWrite(SLEEPA2, LOW);
    digitalWrite(SLEEPA3, LOW);
    digitalWrite(SLEEPA4, LOW);
    
    delay(2000); // One second delay

    digitalWrite(DIRA1,LOW); // Enables the motor to move in a particular direction
    digitalWrite(DIRA2,LOW);
    digitalWrite(DIRA3,LOW);
    digitalWrite(DIRA4,LOW);
    digitalWrite(SLEEPA1, HIGH);
    digitalWrite(SLEEPA2, HIGH);
    digitalWrite(SLEEPA3, HIGH);
    digitalWrite(SLEEPA4, HIGH);
    // Makes 400 pulses for making two full cycle rotation
    for(int x = 0; x < PULSES; x++) {
        digitalWrite(STEPA1,HIGH);
        digitalWrite(STEPA2,HIGH);
        digitalWrite(STEPA3,HIGH);
        digitalWrite(STEPA4,HIGH);
        delayMicroseconds(DELAY);
        digitalWrite(STEPA1,LOW);
        digitalWrite(STEPA2,LOW);
        digitalWrite(STEPA3,LOW);
        digitalWrite(STEPA4,LOW);
        delayMicroseconds(DELAY);
    }
    digitalWrite(SLEEPA1, LOW);
    digitalWrite(SLEEPA2, LOW);
    digitalWrite(SLEEPA3, LOW);
    digitalWrite(SLEEPA4, LOW);
    delay(2000);
}

/*void TestMotorsU()
{
    digitalWrite(DIRU,HIGH); // Enables the motor to move in a particular direction
    digitalWrite(SLEEPU, HIGH);
    // Makes 200 pulses for making one full cycle rotation
    for(int x = 0; x < 400; x++) {
        digitalWrite(STEPU,HIGH);
        delayMicroseconds(500);
        digitalWrite(STEPU,LOW);
        delayMicroseconds(500);
    }
    digitalWrite(SLEEPU, LOW);
    
    delay(2000); // One second delay

    digitalWrite(DIRU,LOW); // Enables the motor to move in a particular direction
    digitalWrite(SLEEPU, HIGH);
    // Makes 400 pulses for making two full cycle rotation
    for(int x = 0; x < 400; x++) {
        digitalWrite(STEPU,HIGH);
        delayMicroseconds(500);
        digitalWrite(STEPU,LOW);
        delayMicroseconds(500);
    }
    digitalWrite(SLEEPU, LOW);
    delay(2000);
}*/

void CalibDriver()
{
    digitalWrite(SLEEPA1, HIGH);
    digitalWrite(SLEEPA2, HIGH);
    digitalWrite(SLEEPA3, HIGH);
    digitalWrite(SLEEPA4, HIGH);
}

/*void CalibDriverU()
{
    digitalWrite(SLEEPU, HIGH);
}*/

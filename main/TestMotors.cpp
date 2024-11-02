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

void TestMotors()
{
    digitalWrite(DIR1,HIGH); // Enables the motor to move in a particular direction
    digitalWrite(DIR2,HIGH);
    digitalWrite(DIR3,HIGH);
    digitalWrite(DIR4,HIGH);
    digitalWrite(SLEEP1, HIGH);
    digitalWrite(SLEEP2, HIGH);
    digitalWrite(SLEEP3, HIGH);
    digitalWrite(SLEEP4, HIGH);
    // Makes 200 pulses for making one full cycle rotation
    for(int x = 0; x < 400; x++) {
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
        digitalWrite(STEP1,HIGH);
        digitalWrite(STEP2,HIGH);
        digitalWrite(STEP3,HIGH);
        digitalWrite(STEP4,HIGH);
        delayMicroseconds(500);
        digitalWrite(STEP1,LOW);
        digitalWrite(STEP2,LOW);
        digitalWrite(STEP3,LOW);
        digitalWrite(STEP4,LOW);
        delayMicroseconds(500);
    }
    digitalWrite(SLEEP1, LOW);
    digitalWrite(SLEEP2, LOW);
    digitalWrite(SLEEP3, LOW);
    digitalWrite(SLEEP4, LOW);
    
    delay(2000); // One second delay

    digitalWrite(DIR1,LOW); // Enables the motor to move in a particular direction
    digitalWrite(DIR2,LOW);
    digitalWrite(DIR3,LOW);
    digitalWrite(DIR4,LOW);
    digitalWrite(SLEEP1, HIGH);
    digitalWrite(SLEEP2, HIGH);
    digitalWrite(SLEEP3, HIGH);
    digitalWrite(SLEEP4, HIGH);
    // Makes 400 pulses for making two full cycle rotation
    for(int x = 0; x < 400; x++) {
        digitalWrite(STEP1,HIGH);
        digitalWrite(STEP2,HIGH);
        digitalWrite(STEP3,HIGH);
        digitalWrite(STEP4,HIGH);
        delayMicroseconds(500);
        digitalWrite(STEP1,LOW);
        digitalWrite(STEP2,LOW);
        digitalWrite(STEP3,LOW);
        digitalWrite(STEP4,LOW);
        delayMicroseconds(500);
    }
    digitalWrite(SLEEP1, LOW);
    digitalWrite(SLEEP2, LOW);
    digitalWrite(SLEEP3, LOW);
    digitalWrite(SLEEP4, LOW);
    delay(2000);
}

void TestMotorsU()
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
}

void CalibDriver()
{
    digitalWrite(SLEEP1, HIGH);
    digitalWrite(SLEEP2, HIGH);
    digitalWrite(SLEEP3, HIGH);
    digitalWrite(SLEEP4, HIGH);
}

void CalibDriverU()
{
    digitalWrite(SLEEPU, HIGH);
}

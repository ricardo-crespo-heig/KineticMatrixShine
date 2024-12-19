/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 15.03.2024 00:17:00
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/

#include <Arduino.h>
#include "IO.h"
#include "INIT.h"


void InitTimer1(void)
{
    // TIMER 1 for interrupt frequency 40000 Hz:
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    TCNT1  = 0; // initialize counter value to 0
    // set compare match register for 40000 Hz increments
    OCR1A = 399; // = 16000000 / (1 * 40000) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS12, CS11 and CS10 bits for 1 prescaler
    TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
}

void DisableSleep(void)
{
    digitalWrite(SLEEPA1, HIGH);
    digitalWrite(SLEEPA2, HIGH);
    digitalWrite(SLEEPA3, HIGH);
    digitalWrite(SLEEPA4, HIGH);
}
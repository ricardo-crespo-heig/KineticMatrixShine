 /************************************************************************************
 * @file        Init.cpp
 * @project     KineticMatrixShine
 * @author      Ricardo Crespo
 * @date        19.12.2024
 * @brief       Init functions
 ************************************************************************************/

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

/*void InitTimer1(void)
{
    // TIMER 1 for interrupt frequency 2000 Hz:
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    TCNT1  = 0; // initialize counter value to 0
    // set compare match register for 2000 Hz increments
    // Formula: OCR1A = (16,000,000 / (Prescaler * Target Frequency)) - 1
    // Using a prescaler of 8:
    // OCR1A = (16,000,000 / (8 * 2000)) - 1 = 999
    OCR1A = 999;
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS12, CS11 and CS10 bits for prescaler of 8
    TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
}*/


void DisableSleep(void)
{
    digitalWrite(SLEEPA1, HIGH);
    digitalWrite(SLEEPA2, HIGH);
    digitalWrite(SLEEPA3, HIGH);
    digitalWrite(SLEEPA4, HIGH);
    digitalWrite(SLEEPB1, HIGH);
    digitalWrite(SLEEPB2, HIGH);
    digitalWrite(SLEEPB3, HIGH);
    digitalWrite(SLEEPB4, HIGH);
    digitalWrite(SLEEPC1, HIGH);
    digitalWrite(SLEEPC2, HIGH);
    digitalWrite(SLEEPC3, HIGH);
    digitalWrite(SLEEPC4, HIGH);
    digitalWrite(SLEEPD1, HIGH);
    digitalWrite(SLEEPD2, HIGH);
    digitalWrite(SLEEPD3, HIGH);
    digitalWrite(SLEEPD4, HIGH);
}

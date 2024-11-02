/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 14.03.2024 23:45:26
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/

/*#include <Arduino.h>
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
    
    //if(digitalRead(CMDU))
    //{
    //    TestMotorsU();
    //}
    //else
    //{
    //    CalibDriverU();
    //}


}*/

#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "IO.h"
#include "TESTMOTORS.h"

/*void setup() {

    InitIO();
      
    // Configuration de Timer1 pour une interruption toutes les 1 µs
    cli();  // Désactive les interruptions globales
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;  // Réinitialise le compteur
    OCR1A = 15;  // Valeur pour 1 µs (à 16 MHz avec un prédiviseur de 1)
    TCCR1B |= (1 << WGM12);  // Mode CTC (Clear Timer on Compare Match)
    TCCR1B |= (1 << CS10);   // Prédivision par 13
    TIMSK1 |= (1 << OCIE1A);  // Active l'interruption pour Timer1

    // Configuration de Timer2 pour une interruption toutes les 100 ms
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;  // Réinitialise le compteur
    OCR2A = 249;  // Valeur pour 100 ms avec un prédiviseur de 1024
    TCCR2A |= (1 << WGM21);  // Mode CTC pour Timer2
    TCCR2B |= (1 << CS22);// | (1 << CS21) | (1 << CS20);  // Prédivision par 1024
    TIMSK2 |= (1 << OCIE2A);  // Active l'interruption pour Timer2

    sei();  // Active les interruptions globales
}

// Interruption pour Timer1 (1 µs)
ISR(TIMER1_COMPA_vect) 
{
    //digitalWrite(STEPB1,!digitalRead(STEPB1));
    // Code à exécuter toutes les 1 µs
}

// Interruption pour Timer2 (100 ms)
ISR(TIMER2_COMPA_vect) 
{
    digitalWrite(STEPA1,!digitalRead(STEPA1));
    // Code à exécuter toutes les 100 ms
}

void loop() {
    // Code principal, qui sera exécuté entre les interruptions
}

*/

#define NUM_CYCLE     10
#define NUM_PULSES    6400

volatile int cycleCount = NUM_CYCLE;
volatile int pulseCount = 0;
volatile bool direction = LOW;
volatile bool stepState = LOW;

void setup() {

    InitIO();
      
    cli();  // Désactive les interruptions globales
    
    // Configuration de Timer3 pour une interruption toutes les 100 ms
    TCCR3A = 0;
    TCCR3B = 0;
    TCNT3 = 0;  // Réinitialise le compteur
    OCR3A = 24999;  // Valeur pour 100 ms (à 16 MHz avec un prédiviseur de 64)
    TCCR3B |= (1 << WGM32);  // Mode CTC (Clear Timer on Compare Match)
    TCCR3B |= (1 << CS31) | (1 << CS30);  // Prédivision par 64
    TIMSK3 |= (1 << OCIE3A);  // Active l'interruption pour Timer3

    // Configuration de Timer1 pour une interruption toutes les 10 µs
    /*TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;  // Réinitialise le compteur
    OCR1A = 159;  // Valeur pour 10 µs (à 16 MHz avec un prédiviseur de 8)
    TCCR1B |= (1 << WGM12);  // Mode CTC (Clear Timer on Compare Match)
    TCCR1B |= (1 << CS11);   // Prédivision par 8
    TIMSK1 |= (1 << OCIE1A);  // Active l'interruption pour Timer1*/

    // TIMER 1 for interrupt frequency 100000 Hz:
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    TCNT1  = 0; // initialize counter value to 0
    // set compare match register for 100000 Hz increments
    OCR1A = 799; // = 16000000 / (1 * 20000) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS12, CS11 and CS10 bits for 1 prescaler
    TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);


    sei();  // Active les interruptions globales

    digitalWrite(SLEEPA1, HIGH);
    digitalWrite(SLEEPA2, HIGH);
    digitalWrite(SLEEPA3, HIGH);
    digitalWrite(SLEEPA4, HIGH);
}

// Interruption pour Timer3 (100 ms)
ISR(TIMER3_COMPA_vect) 
{
    // Code à exécuter toutes les 100 ms
    //digitalWrite(STEPA4,!digitalRead(STEPA4));
    // Si le nombre de pulses est atteint, change la direction
    if (cycleCount >= NUM_CYCLE) 
    {
        cycleCount = 0;
        pulseCount = 0;
        // Inverse la direction
        direction = !direction;
        digitalWrite(DIRA1, direction);
        digitalWrite(DIRA2, direction);
        digitalWrite(DIRA3, direction);
        digitalWrite(DIRA4, direction);

        // Réinitialise le compteur de pulses pour la prochaine rotation
        cycleCount = 0;
    }
    else
    {
        cycleCount++;
    }
}

// Interruption pour Timer1 (50 µs)
ISR(TIMER1_COMPA_vect) 
{

    // Code à exécuter toutes les 50 µs
    //digitalWrite(STEPA1,!digitalRead(STEPA1));
    if(pulseCount < (NUM_PULSES * 2))
    {
        // Alterne l'état du step
        stepState = !stepState;
        
        // Applique cet état sur les broches de step
        digitalWrite(STEPA1, stepState);
        digitalWrite(STEPA2, stepState);
        digitalWrite(STEPA3, stepState);
        digitalWrite(STEPA4, stepState);
    }

    pulseCount++;
}

void loop() {
    // Code principal, qui sera exécuté entre les interruptions
}

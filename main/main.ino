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

#define ROWS          10
#define NBR_MOTORS    1

#define BUFFER_SIZE   2000

volatile int cycleCount = NUM_CYCLE;
volatile int pulseCount = 0;
volatile bool direction = LOW;
volatile bool stepState = LOW;
volatile bool flagInter = false;

int currentIndex = 0;
int error = 0;
int delta = 0;
int threshold = BUFFER_SIZE;

uint8_t buffer[BUFFER_SIZE];

const int tbSteps[ROWS][NBR_MOTORS] =
{
  {320},
  {640},
  {320},
  {640},
  {320},
  {640},
  {320},
  {640},
  {320},
  {640}  
};

/*const int tbSteps[ROWS][NBR_MOTORS] =
{
  {640},
  {640},
  {640},
  {640},
  {640},
  {640},
  {640},
  {640},
  {640},
  {640}  
};*/

void setup() {

    //Serial.begin(9600); // Initialiser la communication série
    InitIO();
      
    cli();  // Désactive les interruptions globales
    
    // Configuration de Timer3 pour une interruption toutes les 100 ms
    /*TCCR3A = 0;
    TCCR3B = 0;
    TCNT3 = 0;  // Réinitialise le compteur
    OCR3A = 24999;  // Valeur pour 100 ms (à 16 MHz avec un prédiviseur de 64)
    TCCR3B |= (1 << WGM32);  // Mode CTC (Clear Timer on Compare Match)
    TCCR3B |= (1 << CS31) | (1 << CS30);  // Prédivision par 64
    TIMSK3 |= (1 << OCIE3A);  // Active l'interruption pour Timer3*/

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



    digitalWrite(SLEEPA1, HIGH);
    digitalWrite(SLEEPA2, HIGH);
    digitalWrite(SLEEPA3, HIGH);
    digitalWrite(SLEEPA4, HIGH);

    pulseCount = tbSteps[0][0]*2;
    initBresenham(tbSteps[0][0]*2);

    // Optionnel : réinitialiser le buffer
    for (int i = 0; i < BUFFER_SIZE; i++) 
    {
        buffer[i] = 0;
    }
    
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        calculateBresenhamPoint(buffer);
    }


    sei();  // Active les interruptions globales
    
    // Envoyer le tableau calculé sur la console
    //Serial.println("Buffer Calculated:");
    //for (int i = 0; i < BUFFER_SIZE; i++) {
    //    Serial.print(buffer[i]);
    //    Serial.print((i % 50 == 49) ? '\n' : ' '); // Sauter une ligne toutes les 50 cases
    //}
}

// Interruption pour Timer1 (50 µs)
ISR(TIMER1_COMPA_vect) 
{
    static uint16_t countInter = 0;
    
    /*// Code à exécuter toutes les 50 µs
    //digitalWrite(STEPA1,!digitalRead(STEPA1));
    if(pulseCount > 0)
    {
        // Alterne l'état du step
        stepState = !stepState;
        
        // Applique cet état sur les broches de step
        digitalWrite(STEPA1, stepState);
        digitalWrite(STEPA2, stepState);
        digitalWrite(STEPA3, stepState);
        digitalWrite(STEPA4, stepState);
    }
    
    // 2000 * 50 µs = 100 ms
    if (countInter >= 2000) 
    {  
        countInter = 0;       // Réinitialise le compteur
        flagInter != flagInter;           // Signale que 100 ms sont écoulées

        // Si le nombre de pulses est atteint, change la direction
        if (cycleCount >= NUM_CYCLE) 
        {
            cycleCount = 0;
    
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
            pulseCount = tbSteps[cycleCount][0]*2;
        }
    }

    pulseCount--;*/
    
    //digitalWrite(STEPA1, stepState);
    //stepState = !stepState;
    //Serial.print(buffer[countInter]);
    if(buffer[countInter] == 1)
    {
        //Serial.print("Y\n");
        // Alterne l'état du step
        stepState = !stepState;
        
        // Applique cet état sur les broches de step
        digitalWrite(STEPA1, stepState);
        //digitalWrite(STEPA2, stepState);
        //digitalWrite(STEPA3, stepState);
        //digitalWrite(STEPA4, stepState);
    }
    else
    {
          //Serial.print("N\n");
    }
    
    countInter++;
    
    if(countInter >= (BUFFER_SIZE))
    {
        countInter = 0;
        // Inverse la direction
        //direction = !direction;
        //digitalWrite(DIRA1, direction);
        //digitalWrite(DIRA2, direction);
        //digitalWrite(DIRA3, direction);
        //digitalWrite(DIRA4, direction);
    }
}

void initBresenham(int totalSteps) 
{
    currentIndex = 0;
    error = 0;
    delta = totalSteps;
    threshold = BUFFER_SIZE;
}

bool calculateBresenhamPoint(uint8_t* buffer) {
    if (currentIndex < BUFFER_SIZE) {
        error += delta;
        if (error >= threshold) {
            buffer[currentIndex] = 1;
            error -= threshold;
        } else {
            buffer[currentIndex] = 0;
        }

        currentIndex++;

        // Retourne `false` si le calcul n'est pas terminé
        return false;
    }

    // Retourne `true` une fois terminé
    return true;
}

void loop() {
    // Code principal, qui sera exécuté entre les interruptions

}

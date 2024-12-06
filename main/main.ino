/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 14.03.2024 23:45:26
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/

#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "IO.h"
#include "TESTMOTORS.h"


#define NUM_PULSES    6400

#define ROWS          40
#define NBR_MOTORS    1

#define BUFFER_SIZE   2000

volatile int cycleCount = ROWS;
volatile int pulseCount = 0;
volatile bool direction = LOW;
volatile bool stepState = LOW;
volatile bool flagInter = true;
volatile bool oneTime = true;
volatile bool dirCW = true;
uint16_t countInterCycle = 0;
    
int currentIndex = 0;
int error = 0;
int delta = 0;
int threshold = BUFFER_SIZE;

uint8_t *readBuffer;
uint8_t buffer[BUFFER_SIZE];
uint8_t buffer1[BUFFER_SIZE];

/*const int tbSteps[ROWS][NBR_MOTORS] =
{
  {50},
  {50},
  {50},
  {50},
  {-1000},
  {-1000},
  {50},
  {50},
  {50},
  {50}  
};*/

const int tbSteps[ROWS][NBR_MOTORS] =
{
  {50},
  {50},
  {50},
  {50},
  {1000},
  {1000},
  {50},
  {50},
  {50},
  {50},  
  {50},
  {50},
  {50},
  {1000},
  {1000},
  {50},
  {50},
  {50},
  {50},
  {50},  
  {50},
  {50},
  {50},
  {50},
  {-1000},
  {-1000},
  {-50},
  {-50},
  {-50},
  {-50},  
  {-50},
  {-50},
  {-1000},
  {-1000},
  {-50},
  {-50},
  {-50},
  {-50},
  {-50},
  {-50}  
};


void setup() {

    //Serial.begin(250000); // Initialiser la communication série
    InitIO();
      
    cli();  // Désactive les interruptions globales

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
    initBresenham(abs(tbSteps[0][0]*2));

    // Optionnel : réinitialiser le buffer
    for (int i = 0; i < BUFFER_SIZE; i++) 
    {
        buffer[i] = 0;
    }
    
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        calculateBresenhamPoint(buffer);
    }

    if((tbSteps[1][0]*2) > 0)
    {
      dirCW = true;
    }
    else
    {
      dirCW = false;
    }

    //direction = !direction;
    //digitalWrite(DIRA1, direction);

    if (dirCW) {
        PORTD |= (1 << DIRA1_BIT);  // Mettre à HIGH
    } else {
        PORTD &= ~(1 << DIRA1_BIT); // Mettre à LOW
    }
    
    initBresenham(abs(tbSteps[1][0]*2));

    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        calculateBresenhamPoint(buffer1);
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
    
    //digitalWrite(STEPA1, stepState);
    //stepState = !stepState;
    //Serial.print(buffer[countInter]);
    //if(buffer[countInter] == 1)
    if(readBuffer[countInter * NBR_MOTORS + 0] == 1)
    {
        //Serial.print("Y\n");
        // Alterne l'état du step
        stepState = !stepState;

        
        // Applique cet état sur les broches de step
        PORTH = (PORTH & ~(1 << 6)) | (stepState << 6);

        /*if (stepState) {
            PORTH |= (1 << STEPA1_BIT);  // Mettre à HIGH
        } else {
            PORTH &= ~(1 << STEPA1_BIT); // Mettre à LOW
        }*/

        
        //digitalWrite(STEPA1, stepState);
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
        countInterCycle++;
        // Inverse la direction
        //direction = !direction;
        //digitalWrite(DIRA1, direction);
        //digitalWrite(DIRA2, direction);
        //digitalWrite(DIRA3, direction);
        //digitalWrite(DIRA4, direction);
        oneTime = true;
        flagInter = !flagInter;           // Signale que 100 ms sont écoulées
        
        if (flagInter) {
            readBuffer = buffer1; // Pointe sur le second buffer
        } else {
            readBuffer = buffer;  // Pointe sur le premier buffer
        }

        /*if(dirCW)
        {
          direction = true;
        }
        else
        {
          direction = false;
        }*/
        //direction = !direction;
        //digitalWrite(DIRA1, direction);

        //Serial.println("Buffer Calculated : " + String(dirCW));

        if (dirCW) {
            PORTD |= (1 << DIRA1_BIT);  // Mettre à HIGH
        } else {
            PORTD &= ~(1 << DIRA1_BIT); // Mettre à LOW
        }
        
        // Envoyer le tableau calculé sur la console
        /*Serial.println("FLAG " + String(flagInter));
        Serial.println("Buffer Calculated " + String(countInterCycle) + " : ");
        Serial.println("Buffer Calculated POINTEUR :");
        for (int i = 0; i < BUFFER_SIZE; i++) {
            Serial.print(readBuffer[i]);
            Serial.print((i % 50 == 49) ? '\n' : ' '); // Sauter une ligne toutes les 50 cases
        }
        Serial.println("Buffer Calculated BUFFER :");
        for (int i = 0; i < BUFFER_SIZE; i++) {
            Serial.print(buffer[i]);
            Serial.print((i % 50 == 49) ? '\n' : ' '); // Sauter une ligne toutes les 50 cases
        }
        Serial.println("Buffer Calculated BUFFER1 :");
        for (int i = 0; i < BUFFER_SIZE; i++) {
            Serial.print(buffer1[i]);
            Serial.print((i % 50 == 49) ? '\n' : ' '); // Sauter une ligne toutes les 50 cases
        }*/
    }

    if(countInterCycle >= ROWS)
    {
        countInterCycle = 0;

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

    if (oneTime) 
    {
        oneTime = false;
        uint8_t* activeBuffer = flagInter ? buffer : buffer1;

        if((tbSteps[countInterCycle][0] * 2) > 0)
        {
          dirCW = true;
        }
        else
        {
          dirCW = false;
        }
        
        initBresenham(abs(tbSteps[countInterCycle][0] * 2));

        for (int i = 0; i < BUFFER_SIZE; i++) {
            calculateBresenhamPoint(activeBuffer);
        }

        // Affichage
        //Serial.println("Buffer Calculated " + String(countInterCycle) + " : ");
        //Serial.println("Val " + String(tbSteps[countInterCycle][0] * 2));
        //for (int i = 0; i < BUFFER_SIZE; i++) {
        //    Serial.print(activeBuffer[i]);
        //    Serial.print((i % 50 == 49) ? '\n' : ' ');
        //}
    }



}

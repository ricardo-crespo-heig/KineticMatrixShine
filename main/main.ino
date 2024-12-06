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
volatile bool direction = LOW;
//volatile bool stepState = LOW;
volatile bool flagInter = true;
volatile bool oneTime = true;
//volatile bool dirCW = true;
uint16_t countInterCycle = 0;
    
/*int currentIndex = 0;
int error = 0;
int delta = 0;
int threshold = BUFFER_SIZE;

uint8_t *readBuffer;
uint8_t buffer[BUFFER_SIZE];
uint8_t buffer1[BUFFER_SIZE];*/

uint8_t buffer[BUFFER_SIZE][NBR_MOTORS];  // Buffer principal
uint8_t buffer1[BUFFER_SIZE][NBR_MOTORS]; // Buffer secondaire
uint8_t (*readBuffer)[NBR_MOTORS];        // Pointeur vers le buffer actif


// Variables pour le calcul Bresenham par moteur
int currentIndex[NBR_MOTORS];
int error[NBR_MOTORS];
int delta[NBR_MOTORS];
int threshold[NBR_MOTORS];


bool dirCW[NBR_MOTORS]; // Direction des moteurs

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

/*const int16_t tbSteps[ROWS][NBR_MOTORS] =
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
};*/

const int16_t tbSteps[ROWS][4] =
{
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {1000, 1000, 1000, 1000},
  {1000, 1000, 1000, 1000},
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {1000, 1000, 1000, 1000},
  {1000, 1000, 1000, 1000},
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {50, 50, 50, 50},
  {-1000, -1000, -1000, -1000},
  {-1000, -1000, -1000, -1000},
  {-50, -50, -50, -50},
  {-50, -50, -50, -50},
  {-50, -50, -50, -50},
  {-50, -50, -50, -50},
  {-50, -50, -50, -50},
  {-50, -50, -50, -50},
  {-1000, -1000, -1000, -1000},
  {-1000, -1000, -1000, -1000},
  {-50, -50, -50, -50},
  {-50, -50, -50, -50},
  {-50, -50, -50, -50},
  {-50, -50, -50, -50},
  {-50, -50, -50, -50},
  {-50, -50, -50, -50}
};


void setup() {

    Serial.begin(250000); // Initialiser la communication série
    Serial.println("Serial begin");
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

    for (int motor = 0; motor < NBR_MOTORS; motor++) {
        // Déterminer la direction pour chaque moteur
        dirCW[motor] = (tbSteps[countInterCycle][motor] > 0);

        // Initialiser Bresenham pour chaque moteur avec un seuil spécifique
        int motorThreshold = BUFFER_SIZE; // Exemple : même seuil pour tous
        initBresenham(tbSteps[countInterCycle][motor] * 2, motor);

        // Calculer les pulses pour chaque moteur
        for (int i = 0; i < BUFFER_SIZE; i++) {
            calculateBresenhamPoint(buffer[i], motor);
        }
    }
        
    //initBresenham(abs(tbSteps[0][0]*2));
    //initBresenham(tbSteps[countInterCycle][motor] * 2, motor);

    // Optionnel : réinitialiser le buffer
    /*for (int i = 0; i < BUFFER_SIZE; i++) 
    {
        buffer[i] = 0;
    }
    
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        calculateBresenhamPoint(buffer);
    }*/

    /*if((tbSteps[1][0]*2) > 0)
    {
      dirCW = true;
    }
    else
    {
      dirCW = false;
    }*/

    if (dirCW[0]) {
        PORTD |= (1 << DIRA1_BIT);  // Mettre à HIGH
    } else {
        PORTD &= ~(1 << DIRA1_BIT); // Mettre à LOW
    }
    
    //initBresenham(abs(tbSteps[1][0]*2));
    
    //for(int i = 0; i < BUFFER_SIZE; i++)
    //{
    //    calculateBresenhamPoint(buffer1);
    //}

    sei();  // Active les interruptions globales
    
    // Envoyer le tableau calculé sur la console
    Serial.println("Buffer Calculated:");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        Serial.print(buffer[i][0]); // Affiche les pulses du moteur 0
        Serial.print((i % 50 == 49) ? '\n' : ' '); // Sauter une ligne toutes les 50 cases
    }
}

// Interruption pour Timer1 (50 µs)
ISR(TIMER1_COMPA_vect) 
{
    static uint16_t countInter = 0;
    static bool stepState[NBR_MOTORS];

    //temp
    static uint8_t motorTemp = 0;
    
    //digitalWrite(STEPA1, stepState);
    //stepState = !stepState;
    //Serial.print(buffer[countInter]);

    //Serial.println("Readbuffer");

    //if(readBuffer[countInter * NBR_MOTORS + 0] == 1)
    if (readBuffer[countInter][motorTemp] == 1) 
    {
        Serial.print("Y\n");
        // Alterne l'état du step pour le moteur actuel
        stepState[motorTemp] = !stepState[motorTemp];

        
        // Applique cet état sur les broches de step
        PORTH = (PORTH & ~(1 << 6)) | (stepState[motorTemp] << 6);

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
          Serial.print("N\n");
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

        if (dirCW[0]) {
            PORTD |= (1 << DIRA1_BIT);  // Mettre à HIGH
        } else {
            PORTD &= ~(1 << DIRA1_BIT); // Mettre à LOW
        }
        
        // Envoyer le tableau calculé sur la console
        //Serial.println("FLAG " + String(flagInter));
        //Serial.println("Buffer Calculated " + String(countInterCycle) + " : ");
        /*Serial.println("Buffer Calculated POINTEUR :");
        for (int i = 0; i < BUFFER_SIZE; i++) {
            Serial.print(readBuffer[i][0]);
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
        Serial.println("Reset");
        countInterCycle = 0;

    }
}

/*void initBresenham(int totalSteps) 
{
    currentIndex = 0;
    error = 0;
    delta = totalSteps;
    threshold = BUFFER_SIZE;
}*/

void initBresenham(int16_t totalSteps, uint8_t motorIndex) 
{
    currentIndex[motorIndex] = 0;
    error[motorIndex] = 0;
    delta[motorIndex] = abs(totalSteps);
    threshold[motorIndex] = BUFFER_SIZE; // Initialiser le seuil pour ce moteur
}


/*bool calculateBresenhamPoint(uint8_t* buffer) {
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
}*/


bool calculateBresenhamPoint(uint8_t* buffer, int motorIndex) {
    if (currentIndex[motorIndex] < BUFFER_SIZE) {
        error[motorIndex] += delta[motorIndex];
        if (error[motorIndex] >= threshold[motorIndex]) {
            buffer[currentIndex[motorIndex]] = 1; // Ajoute un pulse
            error[motorIndex] -= threshold[motorIndex];
        } else {
            buffer[currentIndex[motorIndex]] = 0; // Pas de pulse
        }

        currentIndex[motorIndex]++;
        return false; // Calcul en cours
    }

    return true; // Calcul terminé
}



void loop() {
    // Code principal, qui sera exécuté entre les interruptions

    /*if (oneTime) 
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
    }*/

    if (oneTime) 
    {
        oneTime = false;
        uint8_t (*activeBuffer)[NBR_MOTORS] = flagInter ? buffer1 : buffer;

        for (int motor = 0; motor < NBR_MOTORS; motor++) {
            // Déterminer la direction pour chaque moteur
            dirCW[motor] = (tbSteps[countInterCycle][motor] > 0);

            // Initialiser Bresenham pour chaque moteur avec un seuil spécifique
            int motorThreshold = BUFFER_SIZE; // Exemple : même seuil pour tous
            initBresenham(tbSteps[countInterCycle][motor] * 2, motor);

            // Calculer les pulses pour chaque moteur
            for (int i = 0; i < BUFFER_SIZE; i++) {
                calculateBresenhamPoint(activeBuffer[i], motor);
            }
        }
        
        Serial.println("FLAG " + String(flagInter));
        Serial.println("Buffer Calculated " + String(countInterCycle) + " : ");
        // Debug : Afficher les pulses du moteur 0
        //Serial.println("Buffer Calculated " + String(countInterCycle) + " : ");
        //Serial.println("Val " + String(tbSteps[countInterCycle][0] * 2));
        //for (int i = 0; i < BUFFER_SIZE; i++) {
        //    Serial.print(activeBuffer[i][0]); // Affiche les pulses du moteur 0
        //    Serial.print((i % 50 == 49) ? '\n' : ' ');
        //}
    }


}

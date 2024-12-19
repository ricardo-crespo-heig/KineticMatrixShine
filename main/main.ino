/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 14.03.2024 23:45:26
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/

#include "INIT.h"
#include "IO.h"
#include "SEQUENCE.h"
#include "BRESENHAM.h"
#include "REDIRECTION.h"

volatile bool flagInter = true;
volatile bool oneTime = true;
uint16_t countInterCycle = 0;

uint8_t matrix0[BUFFER_SIZE][NBR_COL_MATRIX];
uint8_t matrix1[BUFFER_SIZE][NBR_COL_MATRIX];

void setup() {

    //Serial.begin(250000); // Initialiser la communication série
    InitIO();
      
    cli();  // Désactive les interruptions globales

    InitTimer1();

    Redirection(matrix0, countInterCycle);

    Redirection(matrix1, countInterCycle);

    DisableSleep();

    sei();  // Active les interruptions globales
}

// Interruption pour Timer1 (50 µs)
ISR(TIMER1_COMPA_vect) 
{
    static uint16_t countInter = 0;
    
    static bool flipFlop = true;

    // Pointeur vers le tableau actif
    uint8_t (*activeBuffer)[NBR_COL_MATRIX] = flagInter ? matrix0 : matrix1;

    if(flipFlop)
    {
      flipFlop = false;
      // Applique cet état sur les broches de step
      PORTH &= ~(1 << BIT6);
      PORTH &= ~(1 << BIT5);
      PORTH &= ~(1 << BIT4);
      PORTH &= ~(1 << BIT3);
      
      //PORTH = 0;
    }
    else
    {
      flipFlop = true;

      // Écrire directement sur les ports de la ligne actuelle
      /*PORTA = *(p++); // Colonne 0 (Port A)
      PORTB = *(p++); // Colonne 1 (Port B)
      PORTC = *(p++); // Colonne 2 (Port C)
      PORTD = *(p++); // Colonne 3 (Port D)
      PORTE = *(p++); // Colonne 4 (Port E)
      PORTG = *(p++); // Colonne 5 (Port G)
      PORTH = *(p++); // Colonne 6 (Port H)
      PORTL = *(p++); // Colonne 7 (Port L)*/

      PORTA = activeBuffer[countInter][0];
      PORTB = activeBuffer[countInter][1];
      PORTC = activeBuffer[countInter][2];
      PORTD = activeBuffer[countInter][3];
      PORTE = activeBuffer[countInter][4];
      PORTG = activeBuffer[countInter][5];
      PORTH = activeBuffer[countInter][6];
      PORTL = activeBuffer[countInter][7];
      
      countInter++;
    }

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

        //Serial.println("Buffer Calculated : " + String(dirCW));
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

    if(countInterCycle >= SEQUENCE_ROWS)
    {
        countInterCycle = 0;
    }
}

void loop() {
    // Code principal, qui sera exécuté entre les interruptions

    if (oneTime) 
    {
        oneTime = false;
        // Affichage
        //Serial.println("Buffer Calculated " + String(countInterCycle) + " : ");
        //Serial.println("Val " + String(tbSteps[countInterCycle][0] * 2));
        //for (int i = 0; i < BUFFER_SIZE; i++) {
        //    Serial.print(activeBuffer[i]);
        //    Serial.print((i % 50 == 49) ? '\n' : ' ');
        //}

        Redirection(flagInter ? matrix0 : matrix1, countInterCycle);
    }
}

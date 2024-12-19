/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 14.03.2024 23:45:26
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/

#include <Arduino.h>
//#include <avr/io.h>
#include <avr/interrupt.h>
#include "INIT.h"
#include "IO.h"
#include "SEQUENCE.h"
#include "BRESENHAM.h"
#include "REDIRECTION.h"

volatile int cycleCount = SEQUENCE_ROWS;
volatile bool flagInter = true;
volatile bool oneTime = true;
uint16_t countInterCycle = 0;

volatile uint32_t interruptCount = 0;

uint8_t matrix0[BUFFER_SIZE][NBR_COL_MATRIX];
uint8_t matrix1[BUFFER_SIZE][NBR_COL_MATRIX];

void setup() {


    Serial.begin(250000); // Initialiser la communication série
    InitIO();
    
    
    //cli();  // Désactive les interruptions globales
    __disable_irq();  // Désactive les interruptions globales


    //InitTimer1();
    InitTimer1_Due();

    Redirection(matrix0, countInterCycle);

    // Parcourir et afficher le tableau
    /*for (int i = 0; i < BUFFER_SIZE; i++) {
        for (int j = 0; j < NBR_COL_MATRIX; j++) {
            Serial.print(matrix0[i][j]);
            Serial.print("\t"); // Tabulation entre les colonnes
        }
        Serial.println(); // Saut de ligne après chaque ligne
    }*/


    Redirection(matrix1, countInterCycle);

    digitalWrite(SLEEPA1, HIGH);
    digitalWrite(SLEEPA2, HIGH);
    digitalWrite(SLEEPA3, HIGH);
    digitalWrite(SLEEPA4, HIGH);

    __enable_irq();  // Réactive les interruptions globales

    pmc_enable_periph_clk(ID_PIOC); // Active l'horloge pour le Port C


    Serial.println("Communication série démarrée !");

    //sei();  // Active les interruptions globales
    
    // Envoyer le tableau calculé sur la console
    //Serial.println("Buffer Calculated:");
    //for (int i = 0; i < BUFFER_SIZE; i++) {
    //    Serial.print(buffer[i]);
    //    Serial.print((i % 50 == 49) ? '\n' : ' '); // Sauter une ligne toutes les 50 cases
    //}
}

// Interrupt Service Routine for Timer Counter 0
void TC0_Handler() {
    Tc *tc = TC0; // Access Timer Counter 0
    uint32_t status = tc->TC_CHANNEL[0].TC_SR; // Read the status register to clear the interrupt

    if (status & TC_SR_CPCS) {
        // Your interrupt code here
        interruptCount++;
        digitalWrite(13, !digitalRead(13)); // Inverse l'état de la LED

    //}
    // Interruption pour Timer1 (50 µs)
    //ISR(TIMER1_COMPA_vect) 
    //{
        static uint16_t countInter = 0;
        
        static bool flipFlop = true;

        // Pointeur vers le tableau actif
        uint8_t (*activeBuffer)[NBR_COL_MATRIX] = flagInter ? matrix0 : matrix1;


        
        //digitalWrite(STEPA1, stepState);
        //stepState = !stepState;
        //Serial.print(buffer[countInter]);
        //if(buffer[countInter] == 1)

        if(flipFlop)
        {
          flipFlop = false;
          // Applique cet état sur les broches de step
          //PORTH = (PORTH & ~(1 << 6)) | (0 << 6);
          //PORTC = (PORTC & ~(1 << 21)) | (0 << 21);
          digitalWrite(STEPA1, LOW);
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

          /*if(activeBuffer[countInter][3] & (1 << 3))
          {
              PORTD |= activeBuffer[countInter][3] << 3;
          }
          else
          {
              PORTD &= ~activeBuffer[countInter][3] << 3;
          }*/

          // DIRA1
          uint8_t bit3 = (activeBuffer[countInter][3] >> 3) & 0x01; // Extraction du bit 4
          digitalWrite(DIRA1, bit3);
          /*if (bit3) {
              PORTA |= (1 << 11); // Met le bit 2 à 1 dans le port
          } else {
              PORTA &= ~(1 << 11); // Met le bit 2 à 0 dans le port
          }*/

          // SLEEPA1
          uint8_t bit0 = (activeBuffer[countInter][6] >> 0) & 0x01; // Extraction du bit 4
          digitalWrite(SLEEPA1, bit0);
          /*if (bit0) {
              PORTA |= (1 << 12); // Met le bit 2 à 1 dans le port
          } else {
              PORTA &= ~(1 << 12); // Met le bit 2 à 0 dans le port
          }*/

          // STEPA1
          uint8_t bit6 = (activeBuffer[countInter][6] >> 6) & 0x01; // Extraction du bit 4
          digitalWrite(STEPA1, bit6);
          /*if (bit6) {
              PORTC |= (1 << 21); // Met le bit 2 à 1 dans le port
          } else {
              PORTC &= ~(1 << 21); // Met le bit 2 à 0 dans le port
          }*/

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
}

void loop() {
    // Code principal, qui sera exécuté entre les interruptions
    // Afficher le nombre d'interruptions toutes les 500 ms
    
    //Serial.print("Interrupt Count: ");
    //Serial.println(interruptCount);
    //delay(500);

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

        //Redirection(flagInter ? matrix0 : matrix1, countInterCycle);
    }
}

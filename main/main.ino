 /************************************************************************************
 * @file        main.ino
 * @project     KineticMatrixShine
 * @author      Ricardo Crespo
 * @date        02.11.2024
 * @brief       Main program
 ************************************************************************************/

#include "INIT.h"
#include "IO.h"
#include "SEQUENCE.h"
#include "BRESENHAM.h"
#include "REDIRECTION.h"

volatile bool flagInter = true;

volatile uint8_t matrix0[BUFFER_SIZE][NBR_COL_MATRIX];
volatile uint8_t matrix1[BUFFER_SIZE][NBR_COL_MATRIX];

void setup() {

    //Serial.begin(250000); // Initialiser la communication série
    
    InitIO();
      
    cli();  // Désactive les interruptions globales

    InitTimer1();

    Redirection(matrix0, 0);

    DisableSleep();

    sei();  // Active les interruptions globales
}

// Interruption pour Timer1 (50 µs)
ISR(TIMER1_COMPA_vect) 
{
    static uint16_t countInter = 0;
    
    static bool flipFlop = false;

    // Pointeur vers le tableau actif
    uint8_t (*activeBuffer)[NBR_COL_MATRIX] = flagInter ? matrix0 : matrix1;
    uint8_t* p = activeBuffer[countInter];

    if(flipFlop)
    {
      flipFlop = false;

      // Applique un état bas sur toutes les pins step
      PORTB &= ~STEP_PORTB;
      PORTE &= ~STEP_PORTE;
      PORTG &= ~STEP_PORTG;
      PORTH &= ~STEP_PORTH;
      PORTL &= ~STEP_PORTL;

    }
    else
    {
      flipFlop = true;

      // Écrire directement sur les ports de la ligne actuelle
      PORTA = *(p++); // Colonne 0 (Port A)
      PORTB = *(p++); // Colonne 1 (Port B)
      PORTC = *(p++); // Colonne 2 (Port C)
      PORTD = *(p++); // Colonne 3 (Port D)
      PORTE = *(p++); // Colonne 4 (Port E)
      PORTG = *(p++); // Colonne 5 (Port G)
      PORTH = *(p++); // Colonne 6 (Port H)
      PORTL = *(p++); // Colonne 7 (Port L)

      countInter++;
    }

    if(countInter >= (BUFFER_SIZE))
    {
        countInter = 0;
        flagInter = !flagInter;           // Signale que 10 ms sont écoulées
    }
}

void loop() 
{
    static bool oldFlagInter = false;
    static uint16_t countInterCycle = 1;

    if (flagInter != oldFlagInter) 
    {
        oldFlagInter = flagInter;

        countInterCycle++;

        if(countInterCycle >= SEQUENCE_ROWS)
        {
            countInterCycle = 0;
        }

        Redirection(!flagInter ? matrix0 : matrix1, countInterCycle);
    }
}

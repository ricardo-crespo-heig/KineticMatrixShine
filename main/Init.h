/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 15.03.2024 00:17:17
 Libraries   :
 Author      :
 Description :
******************************************************************/

//#include <Arduino.h>
//#include "IO.h"

// bresenham.h
#ifndef INIT_H
#define INIT_H

#define NBR_COL_MATRIX    8
//#define BUFFER_SIZE   2000
#define BUFFER_SIZE   400

#define SEQUENCE_ROWS 40
#define NBR_MOTORS    4

void InitTimer1(void);

void DisableSleep(void);

#endif // BRESENHAM_H


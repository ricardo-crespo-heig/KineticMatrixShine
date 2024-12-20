 /************************************************************************************
 * @file        IO.h
 * @project     KineticMatrixShine
 * @author      Ricardo Crespo
 * @date        02.11.2024
 * @brief       Header of IO functions
 ************************************************************************************/

#ifndef IO
#define IO

#define MPORTA 0
#define MPORTB 1
#define MPORTC 2
#define MPORTD 3
#define MPORTE 4
#define MPORTG 5
#define MPORTH 6
#define MPORTL 7

#define BIT0  0
#define BIT1  1
#define BIT2  2
#define BIT3  3
#define BIT4  4
#define BIT5  5
#define BIT6  6
#define BIT7  7

#define MOT0  0
#define MOT1  1
#define MOT2  2
#define MOT3  3
#define MOT4  4
#define MOT5  5
#define MOT6  6
#define MOT7  7
#define MOT8  8
#define MOT9  9
#define MOT10  10
#define MOT11  11
#define MOT12  12
#define MOT13  13
#define MOT14  14
#define MOT15  15

#define STEPA1 9  
#define STEPA2 8  
#define STEPA3 7  
#define STEPA4 6  

#define STEPB1 13  
#define STEPB2 12  
#define STEPB3 11  
#define STEPB4 10  

#define STEPC1 1   
#define STEPC2 44  
#define STEPC3 45  
#define STEPC4 46  

#define STEPD1 5  
#define STEPD2 4  
#define STEPD3 3  
#define STEPD4 2  

#define DIRA1 18
#define DIRA2 16
#define DIRA3 23
#define DIRA4 25

#define DIRB1 41
#define DIRB2 39
#define DIRB3 37
#define DIRB4 35

#define DIRC1 27
#define DIRC2 29
#define DIRC3 31
#define DIRC4 33

#define DIRD1 53
#define DIRD2 51
#define DIRD3 49
#define DIRD4 47

#define SLEEPA1 17
#define SLEEPA2 22
#define SLEEPA3 24
#define SLEEPA4 26

#define SLEEPB1 40
#define SLEEPB2 38
#define SLEEPB3 36
#define SLEEPB4 34

#define SLEEPC1 28
#define SLEEPC2 30
#define SLEEPC3 32
#define SLEEPC4 43

#define SLEEPD1 52
#define SLEEPD2 50
#define SLEEPD3 48
#define SLEEPD4 42

#define STEP_PORTB 0xF0
#define STEP_PORTE 0x2A
#define STEP_PORTG 0x20
#define STEP_PORTH 0x78
#define STEP_PORTL 0x38

extern void InitIO(void);

#endif

/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 15.03.2024 00:17:00
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/

#include <Arduino.h>
#include "IO.h"
#include "INIT.h"


/*void InitTimer1(void)
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
}*/

void InitTimer1_Due() {
    // Enable the clock for Timer Counter 0, Channel 0
    pmc_set_writeprotect(false); // Disable write protection on the Power Management Controller
    pmc_enable_periph_clk(ID_TC0); // Enable peripheral clock for TC0 (Timer Counter 0)

    // Configure the Timer Counter
    Tc *tc = TC0; // Access Timer Counter 0
    uint32_t channel = 0; // Use Channel 0
    uint32_t frequency = 40000; // Desired interrupt frequency
    uint32_t clkDiv = VARIANT_MCK / 2; // Master clock / 2 (Prescaler)
    uint32_t rc = clkDiv / frequency; // Calculate the RC value for the desired frequency

    // Configure the channel
    tc->TC_CHANNEL[channel].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1 // Use TCLK1 (MCK/2)
                                  | TC_CMR_WAVE                // Waveform mode
                                  | TC_CMR_WAVSEL_UP_RC;       // Counter resets on RC compare
    tc->TC_CHANNEL[channel].TC_RC = rc; // Set the RC compare value

    // Enable the interrupt for RC compare
    tc->TC_CHANNEL[channel].TC_IER = TC_IER_CPCS; // Interrupt on RC compare
    tc->TC_CHANNEL[channel].TC_IDR = ~TC_IER_CPCS; // Disable all other interrupts

    NVIC_SetPriority(TC0_IRQn, 3); // 0 = plus haute priorité, 3 = priorité plus basse
    NVIC_EnableIRQ(TC0_IRQn); // Enable Timer Counter 0 interrupt in the NVIC

    // Start the timer
    tc->TC_CHANNEL[channel].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG; // Enable and start the timer
}
/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 15.03.2024 00:17:00
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/

#include <Arduino.h>
#include "IO.h"
#include "BRESENHAM.h"

/*// Constructeur
Bresenham::Bresenham(uint16_t bufferSize)
    : bufferSize(bufferSize), currentIndex(0), error(0), delta(0), threshold(bufferSize) {}

// Initialise les variables pour un nouveau calcul
void Bresenham::init(int16_t totalSteps) {
    currentIndex = 0;
    error = 0;
    delta = abs(totalSteps);
    threshold = bufferSize;
}

// Calcule la valeur suivante
uint8_t Bresenham::calculatePoint() {
    if (currentIndex < bufferSize) {
        error += delta;
        currentIndex++;
        if (error >= threshold) 
        {
            error -= threshold;
            return 1; // Retourne un pulse
        } 
        else 
        {
            return 0; // Pas de pulse
        }
    }

    return 0; // Si le buffer est dépassé
}*/




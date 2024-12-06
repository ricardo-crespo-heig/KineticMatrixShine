/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 15.03.2024 00:17:17
 Libraries   :
 Author      :
 Description :
******************************************************************/


// bresenham.h
/*#ifndef BRESENHAM_H
#define BRESENHAM_H

#include <stdint.h>

class Bresenham {
private:
    uint16_t currentIndex;
    int error;
    int delta;
    int threshold;
    const uint16_t bufferSize;

public:
    // Constructeur
    Bresenham(uint16_t bufferSize);

    // Initialise les variables pour un nouveau calcul
    void init(int16_t totalSteps);

    // Calcule un point
    uint8_t calculatePoint();
};

#endif // */

#include <Arduino.h>
#include "IO.h"

// bresenham.h
#ifndef BRESENHAM_H
#define BRESENHAM_H

class Bresenham {
private:
    uint16_t currentIndex;
    int error;
    int delta;
    int threshold;
    const uint16_t bufferSize;

public:
    // Constructeur inline
    inline Bresenham(uint16_t bufferSize)
        : bufferSize(bufferSize), currentIndex(0), error(0), delta(0), threshold(bufferSize) {}

    // Initialise les variables pour un nouveau calcul inline
    inline void init(int16_t totalSteps) {
        currentIndex = 0;
        error = 0;
        delta = abs(totalSteps);
        threshold = bufferSize;
    }

    // Calcule la valeur suivante inline
    inline uint8_t calculatePoint() {
        if (currentIndex < bufferSize) {
            error += delta;
            currentIndex++;
            if (error >= threshold) {
                error -= threshold;
                return 1; // Retourne un pulse
            } else {
                return 0; // Pas de pulse
            }
        }
        return 0; // Si le buffer est dépassé
    }
};

#endif // BRESENHAM_H


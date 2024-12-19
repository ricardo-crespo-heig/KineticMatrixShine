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

/*#include <Arduino.h>
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

#endif // BRESENHAM_H*/

#ifndef BRESENHAM_H
#define BRESENHAM_H

#include <Arduino.h>
#include <stdint.h>
#include <stdlib.h>

struct MotorData {
    uint16_t currentIndex;
    int error;
    int delta;
    int threshold;
};

class Bresenham {
private:
    MotorData* motors;        // Tableau de structures pour chaque moteur
    const uint16_t bufferSize;
    const uint8_t numMotors;  // Nombre de moteurs

public:
    // Constructeur inline
    inline Bresenham(uint16_t bufferSize, uint8_t numMotors)
        : bufferSize(bufferSize), numMotors(numMotors) {
        motors = new MotorData[numMotors]; // Alloue la mémoire pour chaque moteur
        for (uint8_t i = 0; i < numMotors; i++) {
            motors[i] = {0, 0, 0, static_cast<int>(bufferSize)}; // Initialisation par défaut
        }
    }

    // Initialise les variables pour un moteur donné
    inline void init(int16_t totalSteps, uint8_t motorIndex) {
        if (motorIndex >= numMotors) return; // Vérifie que l'index est valide
        motors[motorIndex].currentIndex = 0;
        motors[motorIndex].error = 0;
        motors[motorIndex].delta = abs(totalSteps);
        motors[motorIndex].threshold = bufferSize;
    }

    // Calcule un point pour un moteur donné
    inline uint8_t calculatePoint(uint8_t motorIndex) {
        if (motorIndex >= numMotors) return 0; // Vérifie que l'index est valide
        MotorData& motor = motors[motorIndex]; // Raccourci pour accéder au moteur

        if (motor.currentIndex < bufferSize) {
            motor.error += motor.delta;
            motor.currentIndex++;
            if (motor.error >= motor.threshold) {
                motor.error -= motor.threshold;
                return 1; // Retourne un pulse
            } else {
                return 0; // Pas de pulse
            }
        }
        return 0; // Si le buffer est dépassé
    }

    // Destructeur inline
    inline ~Bresenham() {
        delete[] motors; // Libère la mémoire allouée
    }
};

#endif // BRESENHAM_H

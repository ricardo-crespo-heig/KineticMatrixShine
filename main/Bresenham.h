 /************************************************************************************
 * @file        Bresenham.h
 * @project     KineticMatrixShine
 * @author      Ricardo Crespo
 * @date        06.12.2024
 * @brief       Bresenham Class
 ************************************************************************************/

#ifndef BRESENHAM_H
#define BRESENHAM_H

class Bresenham {
private:
    uint16_t currentIndex;
    int error;
    int delta;
    const uint16_t bufferSize;
    const int threshold;

public:
    // Constructeur inline
    inline Bresenham(uint16_t bufferSize)
        : bufferSize(bufferSize), threshold(bufferSize), currentIndex(0), error(0), delta(0) {}

    // Initialise les variables pour un nouveau calcul
    inline void SetTarget(int16_t totalSteps) {
        currentIndex = 0;
        error = 0;
        delta = abs(totalSteps);
    }

    // Calcule la valeur suivante
    inline uint8_t CalNextPoint() {
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

#endif

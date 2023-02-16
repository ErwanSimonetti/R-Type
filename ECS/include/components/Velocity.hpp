/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Velocity
*/

#include <ostream>

struct Velocity {
    Velocity() = default;
    void set_component(const int16_t &velocityX, const int16_t &velocityY) {
        _vX = velocityX;
        _vY = velocityY;

        int16_t avVX = 0;
        int16_t avVY = 0;

        if (velocityX < 0)
            avVX = velocityX * -1;
        if (velocityY < 0)
            avVY = velocityY * -1;
        _speedX = velocityX == 0 ? _speedX : velocityX;
        _speedY = velocityY == 0 ? _speedY : velocityY;
    }

    uint16_t _vX;
    uint16_t _vY;
    uint16_t _speedX;
    uint16_t _speedY;

    friend std::ostream &operator<<(std::ostream &output, const Velocity &D) {
        output << "velocity x = " << D._vX << "velocity y = " <<  D._vY <<
        "speed x = " << D._speedX << "speed y = " << D._speedY << std::endl;
        return output;
    }
};
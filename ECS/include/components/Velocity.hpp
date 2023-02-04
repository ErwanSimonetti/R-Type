/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Velocity
*/

#include <ostream>

struct Velocity {
    Velocity() = default;
<<<<<<< HEAD
    void set_component(const uint16_t &velocityX, const uint16_t &velocityY, const uint16_t &speedX, const uint16_t &speedY) {
        _vX = velocityX;
        _vY = velocityY;
        _speedX = speedX;
        _speedY = speedY;
    }
    uint16_t _vX;
    uint16_t _vY;
    uint16_t _speedX;
    uint16_t _speedY;

    friend std::ostream &operator<<(std::ostream &output, const Velocity &D) {
        output << "velocity x = " << D._vX << "velocity y = " <<  D._vY <<
        "speed x = " << D._speedX << "speed y = " << D._speedY << std::endl;
=======
    void build_component(const int16_t &vx, const int16_t &vy) {
        _vx = vx;
        _vy = vy;
    }
    int16_t _vx;
    int16_t _vy;

    friend std::ostream &operator<<(std::ostream &output, const Velocity &D) {
        output << "x = " << D._vx << " y = " <<  D._vy << std::endl;
>>>>>>> b364e23 (feat: Refactored everything)
        return output;
    }
};
/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Velocity
*/

#include <ostream>

struct Velocity {
    Velocity() = default;
    void build_component(const uint16_t &velocityX, const uint16_t &velocityY, const uint16_t &speedX, const uint16_t &speedY) {
        _v_x = velocityX;
        _v_y = velocityY;
        _speed_x = speedX;
        _speed_y = speedY;
    }
    uint16_t _v_x;
    uint16_t _v_y;
    uint16_t _speed_x;
    uint16_t _speed_y;

    friend std::ostream &operator<<(std::ostream &output, const Velocity &D) {
        output << "velocity x = " << D._v_x << "velocity y = " <<  D._v_y <<
        "speed x = " << D._speed_x << "speed y = " << D._speed_y << std::endl;
        return output;
    }
};
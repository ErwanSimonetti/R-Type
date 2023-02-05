/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Velocity
*/

#include <ostream>

struct Velocity {
    Velocity() = default;
    void set_component(const int16_t &vx, const int16_t &vy) {
        _vx = vx;
        _vy = vy;
    }
    int16_t _vx;
    int16_t _vy;

    friend std::ostream &operator<<(std::ostream &output, const Velocity &D) {
        output << "x = " << D._vx << " y = " <<  D._vy << std::endl;
        return output;
    }
};
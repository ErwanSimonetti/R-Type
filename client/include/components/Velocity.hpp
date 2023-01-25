/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Velocity
*/

#include <ostream>

struct Velocity {
    Velocity() = default;
    void build_component(const uint16_t &vx, const uint16_t &vy) {
        _vx = vx;
        _vy = vy;
    }
    uint16_t _vx;
    uint16_t _vy;

    friend std::ostream &operator<<(std::ostream &output, const Velocity &D) {
        output << "x = " << D._vx << " y = " <<  D._vy << std::endl;
        return output;
    }
};
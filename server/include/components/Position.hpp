/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Position
*/

#include <ostream>

struct Position {
    Position() = default;
    void build_component(const uint16_t &x, const uint16_t &y) {
        _x = x;
        _y = y;
    }
    friend std::ostream &operator<<(std::ostream &output, const Position &D) {
        output << "x = " << D._x << " y = " <<  D._y << std::endl;
        return output;
    }
    uint16_t _x;
    uint16_t _y;
};

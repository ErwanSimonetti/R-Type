/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Position
*/

#include <ostream>

struct Position {
    Position() = default;
    void set_component(const int16_t &x, const int16_t &y) {
        _x = x;
        _y = y;
    }
    friend std::ostream &operator<<(std::ostream &output, const Position &D) {
        output << "x = " << D._x << " y = " <<  D._y << std::endl;
        return output;
    }
    int16_t _x;
    int16_t _y;
};

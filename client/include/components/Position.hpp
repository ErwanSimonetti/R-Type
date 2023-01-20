/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Position
*/

#include <ostream>

struct Position {
    Position() = default;
    void build_component(const int &x, const int &y) {
        _x = x;
        _y = y;
    }
    friend std::ostream &operator<<(std::ostream &output, const Position &D) {
        output << "x = " << D._x << " y = " <<  D._y << std::endl;
        return output;
    }
    int _x;
    int _y;
};

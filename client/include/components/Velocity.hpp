/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Velocity
*/

#include <ostream>

struct Velocity {
    Velocity() = default;
    void build_component(const int &vx, const int& vy) {
        _vx = vx;
        _vy = vy;
    }
    int _vx;
    int _vy;

    friend std::ostream &operator<<(std::ostream &output, const Velocity &D) {
        output << "x = " << D._vx << " y = " <<  D._vy << std::endl;
        return output;
    }
};
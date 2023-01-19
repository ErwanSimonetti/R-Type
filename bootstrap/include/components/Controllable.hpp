/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Controllable
*/

#include <ostream>

enum KEY {
    NONE = 0,
    UP = 1,
    LEFT = 2,
    RIGHT = 3,
    DOWN = 4
};

struct Controllable {
    Controllable() = default;
    void build_component() {
        _current_action = KEY::NONE;
    }
    friend std::ostream &operator<<(std::ostream &output, const Controllable &D) {
        output << " current action = " << D._current_action << std::endl;
        return output;
    }
    int _current_action;
};

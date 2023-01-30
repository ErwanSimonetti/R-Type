/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Controllable
*/

#include <ostream>
#include "SFML_utils.hpp"

struct Controllable {
    Controllable() = default;
    void build_component() {
        _current_action = KEYBOARD::NONE;
    }
    friend std::ostream &operator<<(std::ostream &output, const Controllable &D) {
        output << " current action = " << D._current_action << std::endl;
        return output;
    }
    int _current_action;
};

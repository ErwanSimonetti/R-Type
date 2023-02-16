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
    void set_component() {
        _currentAction = KEYBOARD::NONE;
    }
    friend std::ostream &operator<<(std::ostream &output, const Controllable &D) {
        output << " current action = " << D._currentAction << std::endl;
        return output;
    }
    int _currentAction;
};

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
<<<<<<< HEAD
    void set_component() {
=======
    void build_component() {
>>>>>>> b364e23 (feat: Refactored everything)
        _current_action = KEYBOARD::NONE;
    }
    friend std::ostream &operator<<(std::ostream &output, const Controllable &D) {
        output << " current action = " << D._current_action << std::endl;
        return output;
    }
    int _current_action;
};

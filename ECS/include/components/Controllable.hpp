/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Controllable
*/

#include <ostream>
#include "SFML_utils.hpp"

/**
 * @brief components for the ECS, set the entity's Controllable
 * 
 */
struct Controllable {
    Controllable() = default;

    /**
     * @brief Set the component object, with his current action set to None for control of the entity.
     * 
     */
    void set_component() {
        _currentAction = KEYBOARD::NONE;
    }

    /**
     * @brief overload << operator
     * 
     * @param output, variable to fill for print the result of the function.
     * @param D class with the field to print.
     * @return std::ostream&, output.
     */
    friend std::ostream &operator<<(std::ostream &output, const Controllable &D) {
        output << " current action = " << D._currentAction << std::endl;
        return output;
    }
    int _currentAction;
};

/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Gravity
*/

#ifndef GRAVITY_HPP_
#define GRAVITY_HPP_

#include <ostream>

/**
 * @brief components for the ECS, represents the entity Gravity
 */
struct Gravity {
    Gravity() = default;

    /**
     * @brief Set the gravity values
     * 
     * @param force the force of the gravity
     */
    void set_component(const int16_t &force) {
        _force = force;
    }

    /**
     * @brief overload << operator
     * 
     * @param output, variable to fill for print the result of the function.
     * @param D class with the field to print.
     * @return std::ostream&, output.
     */
    friend std::ostream &operator<<(std::ostream &output, const Gravity &D) {
        output << "force = " << D._force  << std::endl;
        return output;
    }
    int16_t _force;
};

#endif /* !GRAVITY_HPP_ */

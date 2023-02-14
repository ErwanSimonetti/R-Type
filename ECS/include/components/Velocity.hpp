/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Velocity
*/

#include <ostream>

/**
 * @brief components for the ECS, set the entity's velocity
 * 
 */
struct Velocity {
    Velocity() = default;

    /**
     * @brief Set the component object with velocity and speed
     * 
     * @param velocityX x axes
     * @param velocityY y axes
     * @param speedX x axes
     * @param speedY y axes
     */
    void set_component(const uint16_t &velocityX, const uint16_t &velocityY, const uint16_t &speedX, const uint16_t &speedY) {
        _vX = velocityX;
        _vY = velocityY;
        _speedX = speedX;
        _speedY = speedY;
    }
    uint16_t _vX;
    uint16_t _vY;
    uint16_t _speedX;
    uint16_t _speedY;

    /**
     * @brief overload << operator
     * 
     * @param output, variable to fill for print the result of the function.
     * @param D class with the field to print.
     * @return std::ostream&, output.
     */
    friend std::ostream &operator<<(std::ostream &output, const Velocity &D) {
        output << "velocity x = " << D._vX << "velocity y = " <<  D._vY <<
        "speed x = " << D._speedX << "speed y = " << D._speedY << std::endl;
        return output;
    }
};
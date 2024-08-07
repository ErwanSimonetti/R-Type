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
     */
    void set_component(const int16_t &velocityX, const int16_t &velocityY) {
        _vX = velocityX;
        _vY = velocityY;

        int16_t avVX = velocityX;
        int16_t avVY = velocityY;

        if (velocityX < 0)
            avVX = velocityX * -1;
        if (velocityY < 0)
            avVY = velocityY * -1;
        _speedX = velocityX == 0 ? _speedX : avVX;
        _speedY = velocityY == 0 ? _speedY : avVY;
    }

    int16_t _vX;
    int16_t _vY;
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

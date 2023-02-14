/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Position
*/

#include <ostream>

/**
 * @brief components for the ECS, set the entity's Position
 * 
 */
struct Position {
    Position() = default;

    /**
     * @brief Set the component object position with his position
     * 
     * @param x axes
     * @param y axes
     */
    void set_component(const int16_t &x, const int16_t &y) {
        _x = x;
        _y = y;
    }

    /**
     * @brief overload << operator
     * 
     * @param output, variable to fill for print the result of the function.
     * @param D class with the field to print.
     * @return std::ostream&, output.
     */
    friend std::ostream &operator<<(std::ostream &output, const Position &D) {
        output << "x = " << D._x << " y = " <<  D._y << std::endl;
        return output;
    }
    int16_t _x;
    int16_t _y;
};

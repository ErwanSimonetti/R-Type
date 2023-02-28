/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Stats
*/

#include <ostream>
#include "SFML_utils.hpp"

/**
 * @brief components for the ECS, set the entity's Stats
 * 
 */
struct Stats {
    Stats() = default;

    /**
     * @brief Set the component object, with his current health and score
     * 
     */
    void set_component(int health, int16_t score) {
        _health = health;
        *_score = score;
    }

    /**
     * @brief overload << operator
     * 
     * @param output, variable to fill for print the result of the function.
     * @param D class with the field to print.
     * @return std::ostream&, output.
     */
    friend std::ostream &operator<<(std::ostream &output, const Stats &D) {
        output << " current action = " << D._score << std::endl;
        return output;
    }
    int16_t _health;
    int16_t *_score = new int16_t(0);
};

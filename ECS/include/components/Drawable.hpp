/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Drawable
*/

#include <SFML/Graphics.hpp>

/**
 * @brief components for the ECS, set the entity's Drawable
 * 
 */
struct Drawable {
    Drawable() = default;

    /**
     * @brief Set the component object
     * 
     * @param radius 
     * @param color 
     */
    void set_component(const std::uint16_t &radius, const sf::Color &color) {
        _sprite = *new sf::CircleShape(radius);
        _sprite.setFillColor(color);
    }
    sf::CircleShape _sprite;
};

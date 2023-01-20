/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Drawable
*/

#include <SFML/Graphics.hpp>

struct Drawable {
    Drawable() = default;
    void build_component(const std::uint16_t &radius, const sf::Color &color) {
        _sprite = *new sf::CircleShape(radius);
        _sprite.setFillColor(color);
    }
    sf::CircleShape _sprite;
};

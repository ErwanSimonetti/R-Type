/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** components
*/

#pragma once

#include <string>
#include <SFML/Graphics.hpp>

struct position {
    position() = default;
    void build_component(const int &x, const int &y) {
        _x = x;
        _y = y;
    }
    int _x;
    int _y;
};

struct velocity {
    velocity() = default;
    // velocity(int speed) : _speed(speed) {}
    void build_component(const int &vx, const int& vy) {
        _vx = vx;
        _vy = vy;
    }
    int _vx;
    int _vy;
};

struct drawable {
    drawable() = default;
    void build_component(const std::uint16_t &radius, const sf::Color &color) {
        _sprite = *new sf::CircleShape(radius);
        _sprite.setFillColor(color);
    }

    sf::CircleShape _sprite;
};

struct controllable {
    controllable() = default;
    void build_component(position pos) {
        _position = pos;
    }
    position _position;
    int _current_action = -1;
};

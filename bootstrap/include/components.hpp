/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** components
*/

#pragma once

#include <string>
#include <iostream>
#include <ostream>
#include <SFML/Graphics.hpp>

enum KEY {
    NONE = 0,
    UP = 1,
    LEFT = 2,
    RIGHT = 3,
    DOWN = 4
};

struct position {
    position() = default;
    void build_component(const int &x, const int &y) {
        _x = x;
        _y = y;
    }
    friend std::ostream &operator<<(std::ostream &output, const position &D) {
        output << "x = " << D._x << " y = " <<  D._y << std::endl;
        return output;
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

    friend std::ostream &operator<<(std::ostream &output, const velocity &D) {
        output << "x = " << D._vx << " y = " <<  D._vy << std::endl;
        return output;
    }

} velocity_t;

struct drawable {
    drawable() = default;
    void build_component(const std::uint16_t &radius, const sf::Color &color) {
        _sprite = *new sf::CircleShape(radius);
        _sprite.setFillColor(color);
    }
    // friend std::ostream &operator<<(std::ostream &output, const drawable &D) {
    //     output << "h = " << D._height << " w = " <<  D._width << " s = " << D._sprite << std::endl;
    //     return output;
    // }
    sf::CircleShape _sprite;
};

struct controllable {
    controllable() = default;
    void build_component() {
        _current_action = KEY::NONE;
    }
    friend std::ostream &operator<<(std::ostream &output, const controllable &D) {
        output << " current action = " << D._current_action << std::endl;
        return output;
    }
    int _current_action;
};

/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** components
*/

#pragma once

#include <string>

typedef struct position {
    position() = default;
    void build_component(const int &x, const int &y) {
        _x = x;
        _y = y;
    }
    int _x;
    int _y;
} position_t;

typedef struct velocity {
    velocity() = default;
    // velocity(int speed) : _speed(speed) {}
    void build_component(const int &vx, const int& vy) {
        _vx = vx;
        _vy = vy;
    }
    int _vx;
    int _vy;
} velocity_t;

typedef struct drawable {
    drawable() = default;
    void build_component(int height, int width, std::string sprite) {
        _height = height;
        _width = width;
        _sprite = sprite;
    }
    void draw(){}

    std::string _sprite;
    int _height;
    int _width;
} drawable_t;

typedef struct controllable {
    controllable() = default;
    void build_component(position_t pos) {
        _position = pos;
    }
    position_t _position;
    int _current_action = -1;
} controllable_t;

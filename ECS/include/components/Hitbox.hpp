/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Hitbox
*/

#pragma once

#include <cstring>

#include "../entity.hpp"

struct Hitbox {
    Hitbox() = default;
 
    void set_component(uint16_t width, uint16_t height, int16_t type) {
        _width = width;
        _height = height;
        _type = type;
        _active = true;
        _obstacle = -1;
    }

    uint16_t _width;
    uint16_t _height;
    int16_t _type;
    int16_t _obstacle;
    bool _active;
};

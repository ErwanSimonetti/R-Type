/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Hitbox
*/

#pragma once

#include <cstring>

#include "ECS_Utils.hpp"
#include "../entity.hpp"

struct Hitbox {
    Hitbox() = default;
 
    void set_component(uint16_t width, uint16_t height, OBJECT type) {
        _width = width;
        _height = height;
        _type = type;
        _active = true;
    }

    uint16_t _width;
    uint16_t _height;
    OBJECT _type;
    bool _active;
};

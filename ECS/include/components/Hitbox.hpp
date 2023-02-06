/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Hitbox
*/

#pragma once

#include "../entity.hpp"
#include <SFML/Graphics.hpp>

struct Hitbox {
    Hitbox() = default;

    void set_component(uint16_t width, uint16_t height) {
        _width = width;
        _height = height;
    }

    uint16_t _width;
    uint16_t _height;
};

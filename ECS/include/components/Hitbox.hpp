/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Hitbox
*/

#pragma once

#include "../entity.hpp"
#include <SFML/Graphics.hpp>

enum TYPE {
    PLAYER,
    ENEMY,
    PROJECTILE
};

struct Hitbox {
    Hitbox() = default;

    void set_component(uint16_t width, uint16_t height, TYPE type) {
        _width = width;
        _height = height;
        _type = type;
        _active = true;
    }

    uint16_t _width;
    uint16_t _height;
    TYPE _type;
    bool _active;

};

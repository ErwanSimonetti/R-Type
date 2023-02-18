/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Drawable
*/

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include "ECS_Utils.hpp"

#pragma once

struct spriteRect {
    int16_t left;
    int16_t top;
    int16_t width;
    int16_t height;
};

struct Drawable {

    Drawable() = default;
    void set_component(const OBJECT &obj) {
        _type = obj;
        _rect = {-1, -1, -1, -1};
    }

    OBJECT _type;
    spriteRect _rect;
};

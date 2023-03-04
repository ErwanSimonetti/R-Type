/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Drawable
*/

#include <unordered_map>
#include <memory>
#include "ECS_Utils.hpp"

#pragma once

struct spriteRect {
    int left;
    int top;
    int width;
    int height;
};

struct rotation {
    float agnleX;
    float angleY;
    float angleZ;
};

struct Drawable {

    Drawable() = default;
    void set_component(const uint16_t &obj, const float &scale = 1, const rotation &rotation = {0.0f, 0.0f, 0.0f}) {
        _type = obj;
        _rect = nullptr;
        _scale = scale;
        _rotation = rotation;
    }

    uint16_t _type;
    float _scale;
    rotation _rotation;
    std::shared_ptr<spriteRect> _rect;
};

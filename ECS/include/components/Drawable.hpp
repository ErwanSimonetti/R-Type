/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Drawable
*/

#include <unordered_map>
#include <memory>

#pragma once

struct spriteRect {
    int left;
    int top;
    int width;
    int height;
};

struct Drawable {

    Drawable() = default;
    void set_component(const uint16_t &obj) {
        _type = obj;
        _rect = nullptr;
    }

    uint16_t _type;
    std::shared_ptr<spriteRect> _rect;
};

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
    int left;
    int top;
    int width;
    int height;
};

struct Drawable {

    Drawable() = default;
    void set_component(const OBJECT &obj) {
        _type = obj;
        _rect = nullptr;
    }

    OBJECT _type;
    std::shared_ptr<spriteRect> _rect;
};

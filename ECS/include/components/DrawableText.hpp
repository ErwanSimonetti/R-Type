/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DrawableText
*/

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include "ECS_Utils.hpp"

#pragma once

struct DrawableText {

    DrawableText() = default;

    void set_component(std::shared_ptr<int16_t>score) {
        _score = score;
    }
    std::shared_ptr<int16_t> _score;
};

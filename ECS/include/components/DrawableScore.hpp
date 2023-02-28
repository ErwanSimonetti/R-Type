/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DrawableScore
*/

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include "ECS_Utils.hpp"

#pragma once

struct DrawableScore {

    DrawableScore() = default;

    void set_component(int16_t *score) {
        _score = score;
    }
    int16_t *_score;
};

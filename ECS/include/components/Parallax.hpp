/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Animatable
*/


#pragma once
#include <SFML/Graphics.hpp>

struct Parallax {
    Parallax() = default;

    void set_component(const int16_t &endPos, const int16_t &startPos) {
        _endPos = endPos;
        _startPos = startPos;
    }
    int16_t _endPos;
    int16_t _startPos;
};
/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DrawableText
*/

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>

#pragma once

struct DrawableText {

    DrawableText() = default;

    void set_component(std::string text) {
        _text = text;
    }
    std::string _text;
};

/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DrawableText
*/

#pragma once

struct DrawableText {

    DrawableText() = default;

    void set_component(std::string text) {
        _text = text;
    }
    std::string _text;
};
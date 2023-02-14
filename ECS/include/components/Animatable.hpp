/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Animatable
*/


#pragma once

#include <SFML/Graphics.hpp>

struct Animatable {

    Animatable() = default;

    void set_component(const uint16_t &speed) {
        _speed = speed;
        _clock.restart();
    }

    uint16_t _speed;
    sf::Clock _clock;
};

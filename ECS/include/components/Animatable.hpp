/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Animatable
*/


#pragma once

#include <chrono>
#include <SFML/Graphics.hpp>

struct Animatable {

    Animatable() = default;

    void set_component(const uint16_t &speed) {
        _speed = speed;
        _clock = std::chrono::high_resolution_clock::now();
        
    }

    uint16_t _speed;
    std::chrono::time_point<std::chrono::high_resolution_clock> _clock;
};

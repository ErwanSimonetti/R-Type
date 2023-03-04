/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Animatable
*/


#pragma once

#include <chrono>

struct Animatable {

    Animatable() = default;

    void set_component(const uint16_t &speed, uint16_t animationIndex = 0) {
        _speed = speed;
        _clock = std::chrono::high_resolution_clock::now();
        _refreshPoint = nullptr;    
        _animationIndex = animationIndex;
    }

    uint16_t _speed;
    uint16_t _animationIndex;
    std::chrono::time_point<std::chrono::high_resolution_clock> _clock;
    std::shared_ptr<int> _refreshPoint;
};

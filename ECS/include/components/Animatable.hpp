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

    void set_component(const uint16_t &speed) {
        _speed = speed;
        _clock = std::chrono::high_resolution_clock::now();
        _refreshPoint = nullptr;      
    }

    uint16_t _speed;
    std::chrono::time_point<std::chrono::high_resolution_clock> _clock;
    std::shared_ptr<int> _refreshPoint;
};

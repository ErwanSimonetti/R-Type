/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Shootable
*/

#pragma once

struct Shootable {
    Shootable() = default;

    void set_component() {
        _clock = std::chrono::high_resolution_clock::now();
        _canShoot = true;
    }
    bool _canShoot;
    std::chrono::time_point<std::chrono::high_resolution_clock> _clock;
};
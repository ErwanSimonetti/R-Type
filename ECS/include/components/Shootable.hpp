/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Shootable
*/

#pragma once

// #include "../entity.hpp"
#include <SFML/Graphics.hpp>

struct Shootable {
    Shootable() = default;

    void set_component() {
        _clock.restart();
        _canShoot = true;
    }
    bool _canShoot;
    sf::Clock _clock;
};
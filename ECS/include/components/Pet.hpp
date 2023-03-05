/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Pet
*/

#pragma once

#include "../entity.hpp"

struct Pet {
    Pet() = default;

    void set_component(int16_t ent) {
        _ent = ent;
    }
    int16_t _ent;
};

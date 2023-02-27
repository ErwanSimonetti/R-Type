/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Pet
*/

#pragma once

#include "../entity.hpp"

struct Pet {
    Pet() : _ent(0) {};

    void set_component(entity ent) {
        _ent = ent;
    }
    entity _ent;
};

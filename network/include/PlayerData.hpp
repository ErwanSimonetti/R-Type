/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PlayerData
*/

#pragma once

#include <stdint.h>

struct PlayerData {
    int16_t entity;
    uint16_t posX;
    uint16_t posY;
    uint16_t inputs[10];
};

/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Enigne_utils
*/

#ifndef ENIGNE_UTILS_HPP_
#define ENIGNE_UTILS_HPP_

#include <stdint.h>
#include <vector>
#include "Graphic_utils.hpp"

enum GAME_EVENT {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    SHOOT,
    WINDOW_CLOSE = -1
};

struct EntityEvent {
    std::vector<KEYBOARD> events;
};



#endif /* !ENIGNE_UTILS_HPP_ */

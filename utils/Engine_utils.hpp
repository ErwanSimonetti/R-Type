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

#include "keyboard.hpp"

enum GAME_EVENT {
    WINDOW_CLOSE = -1
};

struct Events {
    std::vector<GAME_EVENT> gameEvents;
    std::vector<KEYBOARD> inputs;
};



#endif /* !ENIGNE_UTILS_HPP_ */

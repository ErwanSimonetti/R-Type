/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Enigne_utils
*/

#ifndef GAME_EVENTS_HPP_
#define GAME_EVENTS_HPP_

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

#endif /* !GAME_EVENTS_HPP_ */
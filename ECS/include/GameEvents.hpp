/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GameEvents
*/

#ifndef GAME_EVENTS_HPP_
#define GAME_EVENTS_HPP_

#include <stdint.h>
#include <vector>

enum GAME_EVENT {
    SHOOT = 1,
    WINDOW_CLOSE = -1
};

struct EntityEvent {
    int16_t entity;
    std::vector<GAME_EVENT> events;
    int16_t xVelocity;
    int16_t yVelocity;
};



#endif /* !GAME_EVENTS_HPP_ */

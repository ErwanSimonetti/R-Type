/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Enigne_utils
*/

#ifndef ENIGNE_UTILS_HPP_
#define ENIGNE_UTILS_HPP_

enum GAME_EVENT {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    SHOOT,
    WINDOW_CLOSE = -1
};

struct EntityEvent {
    int16_t entity;
    std::vector<GAME_EVENT> events;
};



#endif /* !ENIGNE_UTILS_HPP_ */

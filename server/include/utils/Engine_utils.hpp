/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Enigne_utils
*/

#ifndef ENIGNE_UTILS_HPP_
#define ENIGNE_UTILS_HPP_

enum GAME_EVENT {
<<<<<<< HEAD
    LEFT = 1,
    RIGHT = 2,
    UP = 3,
    DOWN = 4,
    SHOOT = 5,
=======
    LEFT,
    RIGHT,
    UP,
    DOWN,
    SHOOT,
>>>>>>> 6be9af8 (feat(hierarchy) split the project in two section: client & server)
    WINDOW_CLOSE = -1
};

struct EntityEvent {
    int16_t entity;
    std::vector<GAME_EVENT> events;
};



#endif /* !ENIGNE_UTILS_HPP_ */

/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Cliquable
*/

#ifndef CLIQUABLE_HPP_
#define CLIQUABLE_HPP_

#include <memory>

struct Cliquable {

    Cliquable() = default;
    void set_component(const uint16_t &event) {
        _play = false;
        _event = event;
    }

    uint16_t _event;
    bool _play;
};

#endif /* !CLIQUABLE_HPP_ */

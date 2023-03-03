/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Particulable
*/

#ifndef PARTICULABLE_HPP_
#define PARTICULABLE_HPP_

struct Particulable {

    Particulable() = default;
    void set_component(bool play) {
        _play = play;
    }
    bool _play;
};

#endif /* !PARTICULABLE_HPP_ */

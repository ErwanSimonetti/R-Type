/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

struct SoundEffect {

    SoundEffect() = default;
    void set_component(uint16_t type) {
        _type = type;
    }
    uint16_t _type;
    bool _play;
};

#endif /* !SOUND_HPP_ */

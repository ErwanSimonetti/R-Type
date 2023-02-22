/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Raylib_utils
*/

#ifndef Raylib_utils_HPP_
#define Raylib_utils_HPP_

#include "raylib.h"
#include <map>
#include "Graphic_utils.hpp"

static std::map<KeyboardKey, KEYBOARD> KeyboardMap = {
    {KeyboardKey::KEY_UP, KEYBOARD::ARROW_UP},
    {KeyboardKey::KEY_DOWN, KEYBOARD::ARROW_DOWN},
    {KeyboardKey::KEY_LEFT, KEYBOARD::ARROW_LEFT},
    {KeyboardKey::KEY_RIGHT, KEYBOARD::ARROW_RIGHT},
    {KeyboardKey::KEY_A, KEYBOARD::A},
    {KeyboardKey::KEY_B, KEYBOARD::B},
    {KeyboardKey::KEY_C, KEYBOARD::C},
    {KeyboardKey::KEY_D, KEYBOARD::D},
    {KeyboardKey::KEY_E, KEYBOARD::E},
    {KeyboardKey::KEY_F, KEYBOARD::F},
    {KeyboardKey::KEY_G, KEYBOARD::G},
    {KeyboardKey::KEY_H, KEYBOARD::H},
    {KeyboardKey::KEY_I, KEYBOARD::I},
    {KeyboardKey::KEY_J, KEYBOARD::J},
    {KeyboardKey::KEY_K, KEYBOARD::K},
    {KeyboardKey::KEY_L, KEYBOARD::L},
    {KeyboardKey::KEY_M, KEYBOARD::M},
    {KeyboardKey::KEY_N, KEYBOARD::N},
    {KeyboardKey::KEY_O, KEYBOARD::O},
    {KeyboardKey::KEY_P, KEYBOARD::P},
    {KeyboardKey::KEY_Q, KEYBOARD::Q},
    {KeyboardKey::KEY_R, KEYBOARD::R},
    {KeyboardKey::KEY_S, KEYBOARD::S},
    {KeyboardKey::KEY_T, KEYBOARD::T},
    {KeyboardKey::KEY_U, KEYBOARD::U},
    {KeyboardKey::KEY_V, KEYBOARD::V},
    {KeyboardKey::KEY_W, KEYBOARD::W},
    {KeyboardKey::KEY_X, KEYBOARD::X},
    {KeyboardKey::KEY_Y, KEYBOARD::Y},
    {KeyboardKey::KEY_Z, KEYBOARD::Z},
    {KeyboardKey::KEY_ZERO, KEYBOARD::NUM_0},
    {KeyboardKey::KEY_ONE, KEYBOARD::NUM_1},
    {KeyboardKey::KEY_TWO, KEYBOARD::NUM_2},
    {KeyboardKey::KEY_THREE, KEYBOARD::NUM_3},
    {KeyboardKey::KEY_FOUR, KEYBOARD::NUM_4},
    {KeyboardKey::KEY_FIVE, KEYBOARD::NUM_5},
    {KeyboardKey::KEY_SIX, KEYBOARD::NUM_6},
    {KeyboardKey::KEY_SEVEN, KEYBOARD::NUM_7},
    {KeyboardKey::KEY_EIGHT, KEYBOARD::NUM_8},
    {KeyboardKey::KEY_NINE, KEYBOARD::NUM_9}
};

#endif
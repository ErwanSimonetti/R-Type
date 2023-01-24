/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SFML_utils
*/

#ifndef SFML_UTILS_HPP_
#define SFML_UTILS_HPP_

#include <SFML/Graphics.hpp>
#include <map>
#include <Controllable.hpp>

static std::map<sf::Keyboard::Key, KEYBOARD> KeyboardMap = {
    {sf::Keyboard::Up, KEYBOARD::ARROW_UP},
    {sf::Keyboard::Down, KEYBOARD::ARROW_DOWN},
    {sf::Keyboard::Left, KEYBOARD::ARROW_LEFT},
    {sf::Keyboard::Right, KEYBOARD::ARROW_RIGHT},
    {sf::Keyboard::A, KEYBOARD::A},
    {sf::Keyboard::B, KEYBOARD::B},
    {sf::Keyboard::C, KEYBOARD::C},
    {sf::Keyboard::D, KEYBOARD::D},
    {sf::Keyboard::E, KEYBOARD::E},
    {sf::Keyboard::F, KEYBOARD::F},
    {sf::Keyboard::G, KEYBOARD::G},
    {sf::Keyboard::H, KEYBOARD::H},
    {sf::Keyboard::I, KEYBOARD::I},
    {sf::Keyboard::J, KEYBOARD::J},
    {sf::Keyboard::K, KEYBOARD::K},
    {sf::Keyboard::L, KEYBOARD::L},
    {sf::Keyboard::M, KEYBOARD::M},
    {sf::Keyboard::N, KEYBOARD::N},
    {sf::Keyboard::O, KEYBOARD::O},
    {sf::Keyboard::P, KEYBOARD::P},
    {sf::Keyboard::Q, KEYBOARD::Q},
    {sf::Keyboard::R, KEYBOARD::R},
    {sf::Keyboard::S, KEYBOARD::S},
    {sf::Keyboard::T, KEYBOARD::T},
    {sf::Keyboard::U, KEYBOARD::U},
    {sf::Keyboard::V, KEYBOARD::V},
    {sf::Keyboard::W, KEYBOARD::W},
    {sf::Keyboard::X, KEYBOARD::X},
    {sf::Keyboard::Y, KEYBOARD::Y},
    {sf::Keyboard::Z, KEYBOARD::Z},
    {sf::Keyboard::Num0, KEYBOARD::NUM_0},
    {sf::Keyboard::Num1, KEYBOARD::NUM_1},
    {sf::Keyboard::Num2, KEYBOARD::NUM_2},
    {sf::Keyboard::Num3, KEYBOARD::NUM_3},
    {sf::Keyboard::Num4, KEYBOARD::NUM_4},
    {sf::Keyboard::Num5, KEYBOARD::NUM_5},
    {sf::Keyboard::Num6, KEYBOARD::NUM_6},
    {sf::Keyboard::Num7, KEYBOARD::NUM_7},
    {sf::Keyboard::Num8, KEYBOARD::NUM_8},
    {sf::Keyboard::Num9, KEYBOARD::NUM_9},
    {sf::Keyboard::Semicolon, KEYBOARD::SEMICOLON},
    {sf::Keyboard::Comma, KEYBOARD::COMMA},
    {sf::Keyboard::Period, KEYBOARD::PERIOD},
    {sf::Keyboard::Quote, KEYBOARD::QUOTE},
    {sf::Keyboard::Slash, KEYBOARD::SLASH},
    {sf::Keyboard::BackSlash, KEYBOARD::BACKSLASH},
    {sf::Keyboard::Tilde, KEYBOARD::TILDE},
    {sf::Keyboard::Equal, KEYBOARD::EQUAL},
    {sf::Keyboard::Hyphen, KEYBOARD::HYPHEN},
    {sf::Keyboard::Tab, KEYBOARD::TAB},
    {sf::Keyboard::Space, KEYBOARD::SPACE},
    {sf::Keyboard::LControl, KEYBOARD::LCONTROL},
    {sf::Keyboard::LShift, KEYBOARD::LSHIFT},
    {sf::Keyboard::Return, KEYBOARD::RETURN},
    {sf::Keyboard::BackSpace, KEYBOARD::BACKSPACE},
};

#endif /* !SFML_UTILS_HPP_ */

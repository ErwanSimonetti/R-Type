/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RenderGame
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "registry.hpp"
#include "System.hpp"
#include "Drawable.hpp"
#include "Position.hpp"
#include "SFML_utils.hpp"

class RenderGame {

    public:
        RenderGame(const uint16_t &width, const uint16_t &height) {
            _window = new sf::RenderWindow(sf::VideoMode(width, height), "R-TYPE");
            _window->setFramerateLimit(30);
        }

        sf::RenderWindow &getWindow() {
            return *_window;
        }

        void draw_system(sparse_array<Position> const& positions, sparse_array<Drawable> &drawables) {
            for (size_t i = 0; i < drawables.size() && i < positions.size(); ++ i) {
                if (drawables[i] && positions[i]) {
                    drawables[i].value()._sprite.setPosition(positions[i].value()._x, positions[i].value()._y);
                    _window->draw(drawables[i].value()._sprite);
                }
            }
        }

        void getEvent(registry &reg) {
            sf::Event event;
            control_system(reg, KEY::NONE);
            while (_window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _window->close();
                }

                if (event.type == sf::Event::EventType::KeyPressed){
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up:
                        control_system(reg, KeyboardMap.at(event.key.code));
                        break;
                    case sf::Keyboard::Left:
                        control_system(reg, KeyboardMap.at(event.key.code));
                        break;
                    case sf::Keyboard::Right:
                        control_system(reg, KeyboardMap.at(event.key.code));
                        break;
                    case sf::Keyboard::Down:
                        control_system(reg, KeyboardMap.at(event.key.code));
                        break;
                    }
                } else {
                    control_system(reg, KEYBOARD::NONE);
                }
            }
        }

        void gameLoop(registry &reg) {
            while (_window->isOpen()) {
            getEvent(reg);
            reg.run_systems();
            _window->display();
            _window->clear();
            }
        }
        
    private:
        sf::RenderWindow *_window;
};
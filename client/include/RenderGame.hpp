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
#include "SFML_utils.hpp"
#include "Engine_utils.hpp"

class RenderGame {

    public:
        RenderGame(const uint16_t &width, const uint16_t &height) {
            // _window = new sf::RenderWindow(sf::VideoMode(width, height), "R-TYPE");
            // _window->setFramerateLimit(30);
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

        EntityEvent handleEvents(registry &reg) {
            std::vector<int> inputs;
            sf::Event event;
            EntityEvent entityEvent;
            entityEvent.entity = -1;
            while (_window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    _window->close();
                for (std::map<sf::Keyboard::Key, KEYBOARD>::iterator it = KeyboardMap.begin(); it != KeyboardMap.end(); it++)
                    if (sf::Keyboard::isKeyPressed(it->first))
                        inputs.emplace_back(it->second);
                return control_system(reg, inputs, reg.get_components<Position>(), reg.get_components<Controllable>(), reg.get_components<Velocity>());
            }
            return entityEvent;
        }

        EntityEvent gameLoop(registry &reg) {
            _window->isOpen();
            reg.run_systems();
            _window->display();
            _window->clear();
            return handleEvents(reg);
        }

    private:
        // Engine _eng;
        sf::RenderWindow *_window;
};
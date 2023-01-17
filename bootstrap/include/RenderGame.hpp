/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RenderGame
*/

#include <SFML/Graphics.hpp>
#include "registry.hpp"
#include "../src/System.cpp"

class RenderGame {

    public:
        RenderGame(const uint16_t &width, const uint16_t &height) {
            _window = new sf::RenderWindow(sf::VideoMode(width, height), "SFML works!");
        }

        sf::RenderWindow &getWindow() {
            return *_window;
        }

        void gameLoop(registry &reg) {
            while (_window->isOpen()) {
            sf::Event event;
            while (_window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    _window->close();
            }
            render_system(reg, *_window);
            position_system(reg);
        }
    }
        
    private:
        sf::RenderWindow *_window;
};
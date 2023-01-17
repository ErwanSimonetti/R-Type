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
            _window = new sf::RenderWindow(sf::VideoMode(width, height), "R-TYPE");
        }

        sf::RenderWindow &getWindow() {
            return *_window;
        }

        void getEvent(registry &reg) {
            control_system(reg, KEY::NONE);
            sf::Event event;
            while (_window->pollEvent(event)) {

                if (event.type == sf::Event::Closed) {
                    _window->close();
                }

                if (event.type == sf::Event::EventType::KeyPressed){
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up:
                        control_system(reg, KEY::UP);
                        break;
                    case sf::Keyboard::Left:
                        control_system(reg, KEY::LEFT);
                        break;
                    case sf::Keyboard::Right:
                        control_system(reg, KEY::RIGHT);
                        break;
                    case sf::Keyboard::Down:
                        control_system(reg, KEY::DOWN);
                        break;
                    }
                }
            }
        }

        void gameLoop(registry &reg) {
            while (_window->isOpen()) {
            getEvent(reg);
            draw_system(reg, *_window);
            position_system(reg);
        }
    }
        
    private:
        sf::RenderWindow *_window;
};
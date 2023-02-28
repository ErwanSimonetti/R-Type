/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main2
*/

#include <functional>
#include "Engine.hpp"
#include <SFML/Graphics.hpp>

int main(void)
{   
    boost::asio::io_service io_service;
    Engine eng(io_service, "127.0.0.1", "1234");
    printf("client\n");
 
    eng.run();
    return 0;
}

// int main(void)
// {
//     sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Text Example");

//     // Set up a font to use for the text
//     sf::Font font;
//     font.loadFromFile("OpenSans-Bold.ttf");

//     sf::Text text("Hello, SFML!", font, 48);
//     text.setFillColor(sf::Color::White);
//     text.setStyle(sf::Text::Bold | sf::Text::Italic);
//     text.setPosition(200, 250);

//     while (window.isOpen())
//     {
//         window.clear(sf::Color::Black);
//         window.draw(text);
//         window.display();
//     }

//     return 0;
// }
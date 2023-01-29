/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** main
*/

// // #include "../include/RenderGame.hpp"
// #include "../include/components/Components.hpp"
// #include "../include/entity.hpp"
// #include "../include/registry.hpp"

#include <functional>
#include "Engine.hpp"

int main(void)
{   
    boost::asio::io_service io_service;
    Engine eng(1920, 1080, io_service, "1234");

    // eng.create_friendly_entity(1, sf::Color::Blue, 50, 50, 0, 0);
    // eng.create_enemy_entity(2, sf::Color::Red, 50, 50, 150, 150);
    // eng.run_game();
    eng._network.udpReceive(std::bind(&Engine::printMonCul, &eng));
    // eng.printMonCul();
    io_service.run();

    return 0;
}

/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main2
*/

#include <functional>
#include "Engine.hpp"

int main(void)
{   
    boost::asio::io_service io_service;
    Engine eng(1920, 1080, io_service, "127.0.0.1", "1234");

    eng.create_friendly_entity(1, sf::Color::Blue, 50, 50, 0, 0);
    eng.create_enemy_entity(2, sf::Color::Red, 50, 50, 150, 150);
    // eng.run_game();
    Astructlol joj;
    joj.a = 5;
    joj.b = 98;
    Protocol prot;
    DataTypes lel = typeA;
    char *ok = prot.serialiseData<Astructlol>(joj, lel);
    eng._network.udpSend<Astructlol>(ok, eng._network._endpoints.at(0));
    // eng.printMonCul();

    return 0;
}
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

void salut()
{
    std::cout << "hello";
}

int main(void)
{   
    // registry reg;
    // reg.spawn_entity();
    // reg.spawn_entity();
    // reg.spawn_entity();
    // reg.spawn_entity();
    // entity ent(2);
    // reg.spawn_entity_by_id(10);

    // reg.kill_entity(ent);

    // for (auto &it : reg._entities) {
    //     std::cout << it << ", ";
    // }
    // std::cout << std::endl;

    // reg.kill_entities()
    boost::asio::io_service io_service;
    Engine eng(1920, 1080, io_service, "1234");

    eng.create_player(1, sf::Color::Blue, 50, 50, 0, 0);
    eng.create_enemy_entity(2, sf::Color::Red, 50, 50, 150, 150);
    // eng.run_game();
    // Network network(io_service, "1234");
    eng.run_game();
    // eng.printMonCul();
    io_service.run();

    

    return 0;
}

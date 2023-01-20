/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** main
*/

#include "../include/RenderGame.hpp"
#include "../include/components/Components.hpp"
#include "../include/entity.hpp"
#include "../include/registry.hpp"
#include <functional>
// #include "ZipperIterator.hpp"

int main(void)
{    
    entity j(5); //t'as une entity J, et une entity A. J'essaie tout simplement de faire une 2e boule (rouge) mais ca fait des trucs bizarres au display
    entity a(7); //trop tard raciste


    registry reg;
    // reg.register_component<char>();
    reg.register_component<Position>();
    reg.register_component<Velocity>();
    reg.register_component<Drawable>();
    reg.register_component<Controllable>();

    Position pos;
    Velocity vel;
    Controllable control;

    reg.add_component<Position>(j, std::move(pos));
    reg.add_component<Velocity>(j, std::move(vel));
    reg.add_component<Controllable>(j, std::move(control));
    reg.add_component<Velocity>(a, std::move(vel));
    reg.add_component<Position>(a, std::move(pos));
    reg.add_component<Controllable>(a, std::move(control));

    reg.emplace_component<Position>(j, 1, 2);
    reg.emplace_component<Velocity>(j, 0, 0);

    reg.emplace_component<Position>(a, 150, 200);
    reg.emplace_component<Velocity>(a, 44, 44);

    // reg.add_system<position, velocity>(position_system);
    // logging_system(reg.get_components<position>(), reg.get_components<velocity>());

    RenderGame game(1920, 1080);

    entity entWin(0);
    Drawable draw; // Justement là j'ai pas compris
    reg.add_component<Drawable>(j, std::move(draw));
    reg.add_component<Drawable>(a, std::move(draw));

    reg.emplace_component<Drawable>(j, 50, sf::Color::Blue);
    reg.emplace_component<Drawable>(a, 50, sf::Color::Red); 

    reg.add_system<Position, Velocity>(position_system);
    reg.add_system<Position, Velocity>(position_system);
    
    reg.add_system<Position, Drawable>(std::bind(&RenderGame::draw_system, &game, std::placeholders::_1, std::placeholders::_2));
    game.gameLoop(reg);

    return 0;
}

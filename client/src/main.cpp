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

    // entity j(5);
    // entity a(7);
    // registry reg;
    // // reg.register_component<char>();
    // reg.register_component<Position>();
    // reg.register_component<Velocity>();
    // reg.register_component<Drawable>();
    // reg.register_component<Controllable>();

    // Position pos;
    // Velocity vel;
    // Controllable control;

    // reg.add_component<Position>(j, std::move(pos));
    // reg.add_component<Velocity>(j, std::move(vel));
    // reg.add_component<Controllable>(j, std::move(control));
    // reg.add_component<Velocity>(a, std::move(vel));
    // reg.add_component<Position>(a, std::move(pos));
    // reg.add_component<Controllable>(a, std::move(control));

    // reg.emplace_component<Position>(a, 150, 200);
    // reg.emplace_component<Velocity>(a, 44, 44);

int main(void)
{    
    // // reg.add_system<position, velocity>(position_system);
    // // logging_system(reg.get_components<position>(), reg.get_components<velocity>());


    // entity entWin(0);
    // Drawable draw;
    // reg.add_component<Drawable>(j, std::move(draw));
    // reg.add_component<Drawable>(a, std::move(draw));

    // reg.emplace_component<Drawable>(j, 50, sf::Color::Blue);
    // reg.emplace_component<Drawable>(a, 50, sf::Color::Red); 

    // reg.add_system<Position, Velocity>(position_system);
    // reg.add_system<Position, Velocity>(position_system);
    
    // reg.add_system<Position, Drawable>(std::bind(&RenderGame::draw_system, &game, std::placeholders::_1, std::placeholders::_2));
    // game.gameLoop(reg);

    registry reg;

    // entity window(0);

    entity niceShip(1);
    entity enemyShip(2);

    Drawable draw;
    Position Npos;
    Velocity Nvel;
    Controllable Ncontr;
    
    Position Epos;
    Velocity Evel;

    reg.register_component<Position>();
    reg.register_component<Velocity>();
    reg.register_component<Drawable>();
    reg.register_component<Controllable>();

    reg.add_component<Position>(niceShip, std::move(Npos));
    reg.add_component<Velocity>(niceShip, std::move(Nvel));
    reg.add_component<Controllable>(niceShip, std::move(Ncontr));

    reg.add_component<Position>(enemyShip, std::move(Epos));
    reg.add_component<Velocity>(enemyShip, std::move(Evel));
    
    reg.emplace_component<Position>(niceShip, 0, 0);
    reg.emplace_component<Velocity>(niceShip, 45, 45);

    reg.emplace_component<Position>(enemyShip, 100, 100);
    reg.emplace_component<Velocity>(niceShip, 30, 30);

    reg.add_component<Drawable>(niceShip, std::move(draw));
    reg.emplace_component<Drawable>(niceShip, 45, sf::Color::White);

    reg.add_component<Drawable>(enemyShip, std::move(draw));
    reg.emplace_component<Drawable>(enemyShip, 45, sf::Color::Red);

    reg.add_system<Position, Velocity, Controllable>(position_system);

    RenderGame game(1920, 1080);

    reg.add_system<Position, Drawable>(std::bind(&RenderGame::draw_system, &game, std::placeholders::_1, std::placeholders::_2));
    game.gameLoop(reg);

    return 0;
}

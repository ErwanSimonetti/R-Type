/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine
*/

#include "../include/Engine.hpp"

Engine::Engine(uint16_t width, uint16_t height) : _reg(), _game(width, height)
{
    _reg.register_component<Position>();
    _reg.register_component<Velocity>();
    _reg.register_component<Drawable>();
    _reg.register_component<Controllable>();

    _reg.add_system<Position, Velocity>(position_system);
    _reg.add_system<Position, Drawable>(std::bind(&RenderGame::draw_system, &_game, std::placeholders::_1, std::placeholders::_2));
}

Engine::~Engine()
{
}

registry Engine::get_registry() {
    return _reg;
}

void Engine::create_friendly_entity(sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{
    entity ret(_reg.spawn_entity());

    Drawable draw;
    Position pos;
    Velocity vel;
    Controllable contr;

    _reg.add_component<Position>(ret, std::move(pos));
    _reg.emplace_component<Position>(ret, posX, posY);

    _reg.add_component<Velocity>(ret, std::move(vel));
    _reg.emplace_component<Velocity>(ret, velX, velY);
    
    _reg.add_component<Drawable>(ret, std::move(draw));
    _reg.emplace_component<Drawable>(ret, 45, col);
    
    _reg.add_component<Controllable>(ret, std::move(contr));
}

void Engine::create_enemy_entity(sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{    
    entity ret(_reg.spawn_entity());

    Drawable draw;
    Position pos;
    Velocity vel;
    Controllable contr;

    _reg.add_component<Position>(ret, std::move(pos));
    _reg.emplace_component<Position>(ret, posX, posY);

    _reg.add_component<Velocity>(ret, std::move(vel));
    _reg.emplace_component<Velocity>(ret, velX, velY);

    _reg.add_component<Drawable>(ret, std::move(draw));
    _reg.emplace_component<Drawable>(ret, 45, col);
}

void Engine::create_projectile(entity parentShip, sf::Color col, const uint16_t velX, const uint16_t velY, uint16_t damage)
{
    entity ret(_reg.spawn_entity());

    Drawable draw; 
    Position pos;
    Velocity vel;
    Pet pet;

    _reg.add_component<Position>(ret, std::move(pos));
    _reg.emplace_component<Position>(ret, _reg.get_components<Position>()[parentShip].value()._x, _reg.get_components<Position>()[parentShip].value()._y);

    _reg.add_component<Velocity>(ret, std::move(vel));
    _reg.emplace_component<Velocity>(ret, velX, velY);

    _reg.add_component<Drawable>(ret, std::move(draw));
    _reg.emplace_component<Drawable>(ret, 45, col);

    _reg.add_component<Pet>(ret, std::move(pet));
    _reg.emplace_component<Pet>(ret, parentShip);
}

void Engine::run_game() {
    _game.gameLoop(_reg);
}
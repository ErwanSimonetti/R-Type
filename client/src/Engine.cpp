/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine
*/

#include "FollowPath.hpp"
#include "Engine.hpp"

Engine::Engine(uint16_t width, uint16_t height) : _reg(), _game(width, height)
{
    _reg.register_component<Position>();
    _reg.register_component<Velocity>();
    _reg.register_component<Drawable>();
    _reg.register_component<Controllable>();
    _reg.register_component<FollowPath>();

    _reg.add_system<Position, Velocity>(position_system);
    _reg.add_system<Position, Drawable>(std::bind(&RenderGame::draw_system, &_game, std::placeholders::_1, std::placeholders::_2));
}

Engine::~Engine()
{
}

registry Engine::get_registry() {
    return _reg;
}

entity Engine::create_friendly_entity(int id, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{
    entity ret(id);

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

    return ret;
}

entity Engine::create_enemy_entity(int id, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{    
    entity ret(id);

    Drawable draw;
    Position pos;
    Velocity vel;
    Controllable contr;
    FollowPath path;

    _reg.add_component<Position>(ret, std::move(pos));
    _reg.emplace_component<Position>(ret, posX, posY);

    _reg.add_component<Velocity>(ret, std::move(vel));
    _reg.emplace_component<Velocity>(ret, velX, velY);

    _reg.add_component<Drawable>(ret, std::move(draw));
    _reg.emplace_component<Drawable>(ret, 45, col);

    _reg.add_component<FollowPath>(ret, std::move(path));
    _reg.emplace_component<FollowPath>(ret, "upward_curve");

    std::cout << _reg.get_components<FollowPath>()[2].value() << std::endl;
    
    return ret;
}

void Engine::run_game() {
    _game.gameLoop(_reg);
}
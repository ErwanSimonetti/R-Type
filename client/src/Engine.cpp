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
    _reg.add_system<Position, Velocity, FollowPath>(followPathSystem);
}

Engine::~Engine()
{
}

registry Engine::get_registry() {
    return _reg;
}

entity Engine::create_friendly_entity(int id, sf::Color col, const uint16_t speedX, const uint16_t speedY, const uint16_t posX, const uint16_t posY)
{
    entity ret(id);

    _reg.emplace_component<Position>(ret, posX, posY);
    _reg.emplace_component<Velocity>(ret, 1, 1, speedX, speedY);
    _reg.emplace_component<Drawable>(ret, 45, col);
    _reg.emplace_component<Controllable>(ret);

    return ret;
}

entity Engine::create_enemy_entity(int id, sf::Color col, const uint16_t speedX, const uint16_t speedY, const uint16_t posX, const uint16_t posY) // FIXME: replace positions by just the name of the file handling the path
{    
    entity ret(id);

    _reg.emplace_component<Position>(ret, posX, posY);
    _reg.emplace_component<Velocity>(ret, 1, 1, speedX, speedY);
    _reg.emplace_component<Drawable>(ret, 45, col);
    _reg.emplace_component<FollowPath>(ret, "middle_diagonal");

    std::cout << _reg.get_components<FollowPath>()[ret].value() << std::endl;
    return ret;
}

void Engine::run_game() {
    _game.gameLoop(_reg);
}
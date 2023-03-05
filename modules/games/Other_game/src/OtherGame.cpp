/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** OtherGame
*/

#include "OtherGame.hpp"

extern "C" std::shared_ptr<IGame> createLibrary()
{
    return std::make_shared<OtherGame>();
}

OtherGame::OtherGame()
{
}

OtherGame::~OtherGame()
{
}

void OtherGame::setPlayers(std::vector<entity> newPlayers)
{
    _players = newPlayers;
}

std::vector<entity> &OtherGame::getPlayers()
{
    return _players;
}

void OtherGame::create_static(registry &r, entity newEntity, const int16_t posX, const int16_t posY, const int16_t posZ, bool hasHitBoxe, uint16_t type)
{
    r.emplace_component<Position>(newEntity, posX, posY, posZ);
    r.emplace_component<Velocity>(newEntity, 0, 0);
    r.emplace_component<Drawable>(newEntity, type, 10);
    if (hasHitBoxe)
        r.emplace_component<Hitbox>(newEntity, 20, 3, type);
}

void OtherGame::create_player(registry &r, entity newEntity, bool isControllable, const int16_t velX, const int16_t velY, const int16_t posX, const int16_t posY, const int16_t posZ)
{
    r.emplace_component<Shootable>(newEntity);
    r.emplace_component<Drawable>(newEntity, PLAYER, 1, rotation({-90, 0, 90}));
    r.emplace_component<Animatable>(newEntity, 90);
    r.emplace_component<Position>(newEntity, posX, posY, posZ);
    r.emplace_component<Velocity>(newEntity, velX, velY);
    r.emplace_component<Hitbox>(newEntity, 20, 10, 0);
    r.emplace_component<Jump>(newEntity, 120);
    r.emplace_component<Gravity>(newEntity, 1);


    if (isControllable) {
        r.emplace_component<Controllable>(newEntity);
        _players.emplace_back(newEntity);
    }
}

void OtherGame::initGame(registry &r)
{
    for (int i = 0; i < 20; ++i) {
        create_static(r, r.spawn_entity(), i*20, -50, 0, true, GRASS);
        create_static(r, r.spawn_entity(), i*20, -50, -20, true, GRASS);
        create_static(r, r.spawn_entity(), -i*20, -50, 0, true, GRASS);
        create_static(r, r.spawn_entity(), -i*20, -50, -20, true, GRASS);

        create_static(r, r.spawn_entity(), i*20, -50, 20, false, WATER);
        create_static(r, r.spawn_entity(), i*20, -50, 40, false, WATER);
        create_static(r, r.spawn_entity(), i*20, -50, 60, false, WATER);
        create_static(r, r.spawn_entity(), -i*20, -50, 20, false, WATER);
        create_static(r, r.spawn_entity(), -i*20, -50, 40, false, WATER);
        create_static(r, r.spawn_entity(), -i*20, -50, 60, false, WATER);
        if (i%2) {
            create_static(r, r.spawn_entity(), -i*20, -45, -15, false, TREE);
            create_static(r, r.spawn_entity(), i*20, -45, -15, false, TREE);
        }
    }

    for (int i = 0; i < 10; ++i) {
        create_static(r, r.spawn_entity(), 50 + i*20, 50, 0, true, GRASS);
    }
}

void OtherGame::handleInputs(registry &r, size_t entity, const uint16_t inputs[10])
{
    int left = 0;
    int right = 0;

    auto &jumps = r.get_components<Jump>();
    auto &anims = r.get_components<Animatable>();
    auto &drawables = r.get_components<Drawable>();

    for (int i = 0; i < 10; i++) {
        switch (inputs[i]) {
        case KEYBOARD::ARROW_LEFT:
            left = -1;
            break;
        case KEYBOARD::ARROW_RIGHT:
            right = 1;
            break;
        case KEYBOARD::SPACE: {
            if (entity < jumps.size()) {
                auto &jump = r.get_components<Jump>()[entity];
                if (jump && jump.value()._canJump == true) {
                    jump.value()._canJump = false;
                }
            }
            break;
        }
        case KEYBOARD::NONE:
            break;
        default:
            break;
        }
    }

    if (entity < anims.size()) {
        auto &anim = anims[entity];
        if (anim) {
            if (left == 0 && right == 0) {
                anim.value()._animationIndex = 1;
            }
            else {
                anim.value()._animationIndex = 0;
            }
        }
    }

    if (entity < drawables.size()) {
        auto &draw = drawables[entity];
        if (draw) {
            if (left != 0)
                draw.value()._rotation.angleZ = -90;
            if (right != 0)
                draw.value()._rotation.angleZ = 90;
        }
    }

    auto &vel = r.get_components<Velocity>()[entity];
    int dirX = left + right;
    
    for (int i = 0; i < _players.size(); i++) {
        if (_players.at(i) == entity)
            vel.value().set_component(vel.value()._speedX * dirX, vel.value()._vY);
    }
}

void OtherGame::updateRegistry(registry &r, const GameData data[4])
{
    for (int i = 0; i < 4; i++) {
        if (data[i].entity == -1) {
            continue;
        }
        if (_players.size() == 0 && (i == 3 || data[i + 1].entity == -1)) {
            std::cout << "Our Player\n";
            entity newEntity = r.spawn_entity_by_id(data[i].entity);
            create_player(r, newEntity, true, 1, 1, data[i].posX, data[i].posY, 0);
            _players.emplace_back(newEntity);
            continue;
        }
        if (!r.is_entity_alive(data[i].entity)) {
            std::cout << "New Player\n";
            create_player(r, r.spawn_entity_by_id(data[i].entity), false, 0, 0, data[i].posX, data[i].posY, 0);
        } else {
            r.get_components<Position>()[data[i].entity].value().set_component(data[i].posX, data[i].posY);
            handleInputs(r, data[i].entity, data[i].inputs);
        }
    }
}

// server receive
void OtherGame::updateRegistry(registry &r, const GameData &data)
{
    if (!r.is_entity_alive(data.entity)) {
        create_player(r, r.spawn_entity(), true, 1, 1, -std::rand() % 200, -30, 0);
        return;
    }
    for (int i = 0; i < _players.size(); i++) {
        if (_players.at(i) == data.entity) {
            handleInputs(r, _players.at(i), data.inputs);
        }
    }
}

std::vector<GAME_EVENT> OtherGame::run_gameLogic(registry &r)
{
    return std::vector<GAME_EVENT>();
}
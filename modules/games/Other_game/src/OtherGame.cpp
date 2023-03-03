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

std::vector<entity> OtherGame::getPLayers() const 
{
    return _players;
}

void OtherGame::create_static(registry &r, entity newEntity, const uint16_t posX, const uint16_t posY, OBJECT type)
{
    r.emplace_component<Position>(newEntity, posX, posY);
    r.emplace_component<Hitbox>(newEntity, posX+45, posY+45, type);
    r.emplace_component<Drawable>(newEntity, type);
}

void OtherGame::create_player(registry &r, entity newEntity, bool isControllable, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY)
{
    r.emplace_component<Shootable>(newEntity);
    r.emplace_component<Drawable>(newEntity, SHIP);
    r.emplace_component<Animatable>(newEntity, 90);
    r.emplace_component<Position>(newEntity, posX, posY);
    r.emplace_component<Velocity>(newEntity, velX, velY);
    r.emplace_component<Hitbox>(newEntity, posX+45, posY+45, SHIP);

    if (isControllable) {
        r.emplace_component<Controllable>(newEntity);
        _players.emplace_back(newEntity);
    }
}

void OtherGame::initGame(registry &r)
{
    create_static(r, r.spawn_entity(), 0, 900, ENEMYSHIP);
    create_static(r, r.spawn_entity(), 10, 900, ENEMYSHIP);
    create_static(r, r.spawn_entity(), 20, 900, ENEMYSHIP);
    create_static(r, r.spawn_entity(), 30, 900, ENEMYSHIP);
    create_static(r, r.spawn_entity(), 40, 900, ENEMYSHIP);
    create_static(r, r.spawn_entity(), 50, 900, ENEMYSHIP);
}

void OtherGame::handleInputs(registry &r, size_t entity, const uint16_t inputs[10])
{
    int left = 0;
    int right = 0;
    int up = 0;
    int down = 0;

    bool stopLoop = false;

    auto &jumps = r.get_components<Jump>();

    for (int i = 0; i < 10; i++) {
        if (stopLoop)
            break;
        switch (inputs[i]) {
        case KEYBOARD::ARROW_LEFT:
            left = -1;
            break;
        case KEYBOARD::ARROW_RIGHT:
            right = 1;
            break;
        case KEYBOARD::ARROW_UP:
            up = -1;
            break;
        case KEYBOARD::ARROW_DOWN:
            down = 1;
            break;
        case KEYBOARD::SPACE: {
            if (entity < jumps.size()) {
                auto &jump = r.get_components<Jump>()[entity];
                if (jump && jump.value()._canJump == true) {
                    jump.value()._canJump = false;
                    jump.value()._clock = std::chrono::high_resolution_clock::now();
                }
            }
            break;
        }
        case KEYBOARD::NONE:
            stopLoop = true;
            break;
        default:
            break;
        }
    }
    
    auto &vel = r.get_components<Velocity>()[entity];

    int dirX = left + right;
    int dirY = up + down;

    for (int i = 0; i < _players.size(); i++) {
        if (_players.at(i) == entity)
            vel.value().set_component(vel.value()._speedX * dirX, vel.value()._speedY * dirY);
    }
}

// client receive
void OtherGame::updateRegistry(registry &r, const GameData data[4])
{
    for (int i = 0; i < 4; i++) {
        if (data[i].entity == -1) {
            continue;
        }
        if (_players.size() == 0 && (i == 3 || data[i + 1].entity == -1)) {
            std::cout << "Our Player\n";
            entity newEntity = r.spawn_entity_by_id(data[i].entity);
            create_player(r, newEntity, true, 3, 3, data[i].posX, data[i].posY);
            _players.emplace_back(newEntity);
            continue;
        }
        if (!r.is_entity_alive(data[i].entity)) {
            std::cout << "New Player\n";
            create_player(r, r.spawn_entity_by_id(data[i].entity), false, 0, 0, data[i].posX, data[i].posY);
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
        create_player(r, r.spawn_entity(), true, 3, 3, 10, 10);
        return;
    }
    for (int i = 0; i < _players.size(); i++) {
        if (_players.at(i) == data.entity) {
            handleInputs(r, _players.at(i), data.inputs);
        }
    }
}

void OtherGame::run_gameLogic(registry &r, const Events &events) 
{
}
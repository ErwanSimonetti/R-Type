/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Rtype
*/

#include "Rtype.hpp"

extern "C" std::shared_ptr<IGame> createLibrary()
{
    return std::make_shared<Rtype>();
}

Rtype::Rtype() : _player(0)
{
}

Rtype::~Rtype()
{
}

void Rtype::create_entity(registry &r, entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY)
{
    r.emplace_component<Position>(newEntity, posX, posY);
    r.emplace_component<Velocity>(newEntity, velX, velY);
    r.emplace_component<Hitbox>(newEntity, posX+45, posY+45, SHIP);
    r.emplace_component<Drawable>(newEntity, SHIP);
    r.emplace_component<Animatable>(newEntity, 90);
}

void Rtype::create_player(registry &r, entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY)
{
    r.emplace_component<Controllable>(newEntity);
    r.emplace_component<Shootable>(newEntity);
    r.emplace_component<Drawable>(newEntity, SHIP);
    r.emplace_component<Animatable>(newEntity, 90);
    r.emplace_component<Position>(newEntity, posX, posY);
    r.emplace_component<Velocity>(newEntity, velX, velY);
    // can shoot component
    r.emplace_component<Hitbox>(newEntity, posX+45, posY+45, SHIP);
}

void Rtype::create_enemy_entity(registry &r, entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY)
{    
    r.emplace_component<Position>(newEntity, posX, posY);
    r.emplace_component<Velocity>(newEntity, velX, velY);
    r.emplace_component<Drawable>(newEntity, SHIP);
    r.emplace_component<Drawable>(newEntity, ENEMYSHIP);
    r.emplace_component<Hitbox>(newEntity, posX+45, posY+45, ENEMYSHIP);
    r.emplace_component<Animatable>(newEntity, 90);
    r.emplace_component<FollowPath>(newEntity, "middle_diagonal");
    // can shoot component
}

void Rtype::create_parallax(registry &r, entity newEntity, const uint16_t posX, const uint16_t posY, const uint16_t speed, const OBJECT obj) 
{
    r.emplace_component<Position>(newEntity, posX, posY);
    r.emplace_component<Drawable>(newEntity, obj);
    r.emplace_component<Animatable>(newEntity, speed);
    r.emplace_component<Parallax>(newEntity, -1920, 1920);
}

void Rtype::create_projectile(registry &r, entity newEntity, int16_t parentId, const uint16_t velX, const uint16_t velY)
{
    int16_t posX =r.get_components<Position>()[parentId].value()._x;
    int16_t posY =r.get_components<Position>()[parentId].value()._y;

    r.emplace_component<Position>(newEntity, posX, posY);
    r.emplace_component<Hitbox>(newEntity, posX+10, posY+10, BULLET);
    r.emplace_component<Velocity>(newEntity, velX, velY);
    r.emplace_component<Drawable>(newEntity, BULLET);
    r.emplace_component<Pet>(newEntity, entity(parentId));
    r.emplace_component<Animatable>(newEntity, 10);
} 

void Rtype::initGame(registry &r)
{
    create_entity(r, r.spawn_entity_by_id(0), 0, 0, 100, 100);
    create_parallax(r, r.spawn_entity(), 1920, 0, 3, PARA_1);
    create_parallax(r, r.spawn_entity(), 0, 0, 3, PARA_1);
    create_parallax(r, r.spawn_entity(), 1920, 0, 6, PARA_2);
    create_parallax(r, r.spawn_entity(), 0, 0, 6, PARA_2);
    create_parallax(r, r.spawn_entity(), 1920, 0, 9, PARA_3);
    create_parallax(r, r.spawn_entity(), 0, 0, 9, PARA_3);
    create_parallax(r, r.spawn_entity(), 1920, 346, 12, PARA_4);
    create_parallax(r, r.spawn_entity(), 0, 346, 12, PARA_4);
}

void Rtype::updateRegistry(registry &r, GameData data)
{
    for (int i = 0; i < 4; i++) {
        if (data.entities[i] == -1) {
            continue;
        }
        if (_player == 0 && (i == 3 || data.entities[i + 1] == -1)) {
            printf("Our Player\n");
            entity newEntity = r.spawn_entity_by_id(data.entities[i]);
            create_player(r, newEntity, 10, 10, data.posX[i], data.posY[i]);
            _player = newEntity;
            continue;
        }
        if (!r.is_entity_alive(data.entities[i])) {
            printf("New player\n");
            create_entity(r, r.spawn_entity_by_id(data.entities[i]), 0, 0, data.posX[i], data.posY[i]);
        } else {
            r.get_components<Position>()[data.entities[i]].value().set_component(data.posX[i], data.posY[i]);
            r.get_components<Velocity>()[data.entities[i]].value().set_component(data.xVelocity[i], data.yVelocity[i]);
            if (data.hasShot[i] == 1) {
                create_projectile(r, r.spawn_entity(), data.entities[i], 15, 0);
            }
        }
    }
}

void Rtype::run_gameLogic(registry &r, EntityEvent events) 
{
}
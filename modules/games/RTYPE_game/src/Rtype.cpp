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

Rtype::Rtype()
{
}

Rtype::~Rtype()
{
}

std::vector<entity> Rtype::getPLayers() const 
{
    return _players;
}

void Rtype::create_score(registry &r, entity newEntity, int16_t parentId, std::string score, const int16_t posX, const int16_t posY)
{
    r.emplace_component<DrawableText>(newEntity, score);
    r.emplace_component<Pet>(newEntity, parentId);
    r.emplace_component<Position>(newEntity, posX, posY);
}

void Rtype::create_static(registry &r, entity newEntity, const uint16_t posX, const uint16_t posY, int16_t type)
{
    r.emplace_component<Position>(newEntity, posX, posY);
    r.emplace_component<Hitbox>(newEntity, posX+45, posY+45, type);
    r.emplace_component<Drawable>(newEntity, type);
}

void Rtype::create_entity(registry &r, entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY)
{
    r.emplace_component<Position>(newEntity, posX, posY);
    r.emplace_component<Velocity>(newEntity, velX, velY);
    r.emplace_component<Hitbox>(newEntity, 45, 45, SHIP);
    r.emplace_component<Drawable>(newEntity, SHIP);
    r.emplace_component<Animatable>(newEntity, 90);
}

void Rtype::create_player(registry &r, entity newEntity, bool isControllable, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY)
{
    r.emplace_component<Shootable>(newEntity);
    r.emplace_component<Drawable>(newEntity, SHIP);
    r.emplace_component<Animatable>(newEntity, 90);
    r.emplace_component<Position>(newEntity, posX, posY);
    r.emplace_component<Velocity>(newEntity, velX, velY);
    r.emplace_component<Hitbox>(newEntity, 45, 45, SHIP);
    r.emplace_component<Stats>(newEntity, 3, 0);

    if (isControllable) {
        r.emplace_component<Controllable>(newEntity);
        _players.emplace_back(newEntity);
    }
}

void Rtype::create_enemy_entity(registry &r, entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY)
{    
    r.emplace_component<Position>(newEntity, posX, posY);
    r.emplace_component<Velocity>(newEntity, 0, 0);
    r.emplace_component<Drawable>(newEntity, ENEMYSHIP);
    r.emplace_component<Hitbox>(newEntity, 45, 45, ENEMYSHIP);
    r.emplace_component<Animatable>(newEntity, 90);
    r.emplace_component<Stats>(newEntity, 1, 0);
    r.emplace_component<Shootable>(newEntity);

}

void Rtype::create_parallax(registry &r, entity newEntity, const uint16_t posX, const uint16_t posY, const uint16_t speed, const int16_t obj) 
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
    r.emplace_component<Hitbox>(newEntity, 10, 10, BULLET);
    r.emplace_component<Velocity>(newEntity, velX, velY);
    r.emplace_component<Drawable>(newEntity, BULLET);
    r.emplace_component<Pet>(newEntity, entity(parentId));
    r.emplace_component<Animatable>(newEntity, 10);
    r.emplace_component<Stats>(newEntity, 1, 0);
}

void Rtype::create_enemy_projectile(registry &r, entity newEntity, int16_t parentId, const uint16_t velX, const uint16_t velY)
{
    int16_t posX = r.get_components<Position>()[parentId].value()._x;
    int16_t posY = r.get_components<Position>()[parentId].value()._y;
    r.emplace_component<Position>(newEntity, posX, posY);
    r.emplace_component<Hitbox>(newEntity, 10, 10, EBULLET);
    r.emplace_component<Velocity>(newEntity, velX, velY);
    r.emplace_component<Drawable>(newEntity, EBULLET);
    r.emplace_component<Pet>(newEntity, entity(parentId));
    r.emplace_component<Animatable>(newEntity, 10);
    r.emplace_component<Stats>(newEntity, 1, 0);


}

void Rtype::initGame(registry &r)
{
    _enemyTimer = std::chrono::system_clock::now();
    create_parallax(r, r.spawn_entity_by_id(0), 1920, 0, 3, PARA_1);
    create_parallax(r, r.spawn_entity(), 0, 0, 3, PARA_1);
    create_parallax(r, r.spawn_entity(), 1920, 0, 6, PARA_2);
    create_parallax(r, r.spawn_entity(), 0, 0, 6, PARA_2);
    create_parallax(r, r.spawn_entity(), 1920, 0, 9, PARA_3);
    create_parallax(r, r.spawn_entity(), 0, 0, 9, PARA_3);
    create_parallax(r, r.spawn_entity(), 1920, 346, 12, PARA_4);
    create_parallax(r, r.spawn_entity(), 0, 346, 12, PARA_4);
}

void Rtype::handleInputs(registry &r, size_t entity, const uint16_t inputs[10])
{
    int left = 0;
    int right = 0;
    int up = 0;
    int down = 0;

    bool stopLoop = false;

    auto &shootables = r.get_components<Shootable>();

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
            if (entity < shootables.size()) {
                auto &shoot = r.get_components<Shootable>()[entity];
                if (shoot && shoot.value()._canShoot == true) {
                    create_projectile(r, r.spawn_entity(), entity, 15, 0);
                    shoot.value()._canShoot = false;
                    shoot.value()._clock = std::chrono::high_resolution_clock::now();
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
void Rtype::updateRegistry(registry &r, const GameData data[4])
{
    for (int i = 0; i < 4; i++) {
        if (data[i].entity == -1) {
            continue;
        }
        if (_players.size() == 0 && (i == 3 || data[i + 1].entity == -1)) {
            std::cout << "Our Player\n";
            entity newEntity = r.spawn_entity_by_id(data[i].entity);
            create_player(r, newEntity, true, 5, 5, data[i].posX, data[i].posY);
            create_score(r, r.spawn_entity(), newEntity, "0", 1600, 30);
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
void Rtype::updateRegistry(registry &r, const GameData &data)
{
    if (!r.is_entity_alive(data.entity)) {
        entity newEntity = r.spawn_entity();
        create_player(r, newEntity, true, 5, 5, 10, 10);
        create_score(r, r.spawn_entity(), newEntity, "0", 1600, 30);

        return;
    }
    for (int i = 0; i < _players.size(); i++) {
        if (_players.at(i) == data.entity) {
            handleInputs(r, _players.at(i), data.inputs);
        }
    }
}

void Rtype::checkStats(sparse_array<Hitbox> &hbxs, sparse_array<Stats> &sts, sparse_array<Pet> &pets) {
    for (size_t i = 0; i < hbxs.size() && i < sts.size() && i < pets.size(); ++i) {
        auto &hbx = hbxs[i];
        auto &stat = sts[i];
        auto &pet = pets[i];
        if (stat && hbx && (hbx.value()._type == ENEMYSHIP && hbx.value()._obstacle == BULLET)) {
            stat.value().set_component(stat.value()._health - 1, 0);
        }
        if (stat && hbx && (hbx.value()._type == SHIP && hbx.value()._obstacle == EBULLET)) {
            stat.value().set_component(stat.value()._health - 1, 0);
        }
        if (hbx && (hbx.value()._type == BULLET && hbx.value()._obstacle == ENEMYSHIP) ) {
            if (pet && sts[pet.value()._ent].has_value()) {
                int16_t ent = pet.value()._ent;
                sts[ent].value().set_component(sts[ent].value()._health, sts[ent].value()._score + 5);
                pet.value().set_component(0);
            }
        }
    }
}

bool Rtype::spawnEnemies(registry &r)
{
    int posY = rand() % 1000;
    int posX = rand() % 500 + 400;
    if (std::chrono::system_clock::now() - _enemyTimer  > std::chrono::seconds(5)) {
        create_enemy_entity(r, r.spawn_entity(), 1, 1, posX, posY);
        _enemyTimer = std::chrono::system_clock::now();
        _shootingTimer = std::chrono::system_clock::now();
        return true;
    }
    return false;
}

void Rtype::enemyShoot(registry &r, sparse_array<Hitbox> &hitboxes, sparse_array<Shootable> &shoot)
{
    for (size_t i = 0; i < hitboxes.size() && i < shoot.size(); ++i) {
        auto &hbx = hitboxes[i];
        auto &sht = shoot[i];
        if (sht && hbx && hbx.value()._type == ENEMYSHIP) {
            if (std::chrono::system_clock::now() - sht.value()._clock > std::chrono::seconds(3)) {
                create_enemy_projectile(r, r.spawn_entity(), i, -15, 0);
                sht.value()._clock = std::chrono::high_resolution_clock::now();
            }
        }
    }
}

void Rtype::createEnemies(registry &r, EnemyData &data)
{
    if (!r.is_entity_alive(data.entities)) {
        create_enemy_entity(r, entity(data.entities), 0, 0, data.posX, data.posY);
    } else {
        r.get_components<Position>()[data.entities].value().set_component(data.posX, data.posY);
    }
}

void Rtype::run_gameLogic(registry &r, const Events &events) 
{
    checkStats(r.get_components<Hitbox>(), r.get_components<Stats>(), r.get_components<Pet>());
    enemyShoot(r, r.get_components<Hitbox>(), r.get_components<Shootable>());
}
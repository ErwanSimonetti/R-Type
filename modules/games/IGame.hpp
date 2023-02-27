/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "registry.hpp"
#include "Engine_utils.hpp"
#include "registry.hpp"
#include "System.hpp"

struct GameData {
    int16_t entities[4];
    uint16_t posX[4];
    uint16_t posY[4];
    int16_t directionsX[4];
    int16_t directionsY[4];
    // uint16_t inputs[4][10];
    uint16_t hasShot[4];
};

class IGame {
    public:
        IGame() = default;
        ~IGame() = default;
        virtual void initGame(registry &r) = 0;
        virtual void run_gameLogic(registry &r, EntityEvent events) = 0;
        virtual void updateRegistry(registry &r, GameData data) = 0;

        virtual void create_player(registry &r, entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY) = 0;
        virtual void create_enemy_entity(registry &r, entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, uint16_t posY) = 0;
        virtual void create_entity(registry &r, entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY) = 0;
        virtual void create_projectile(registry &r, entity newEntity, int16_t parentId, const uint16_t velX, const uint16_t velY) = 0;

    protected:
    private:
};

#endif /* !IGAME_HPP_ */

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
    int16_t entity;
    uint16_t posX;
    uint16_t posY;
    uint16_t inputs[10];
};

class IGame {
    public:
        IGame() = default;
        ~IGame() = default;

        /**
         * @brief Function used to return the players entities
         * 
         * @return std::vector<entity>
         */
        virtual std::vector<entity> getPLayers() const = 0;

        /**
         * @brief Function used to create all starting assets needed fro the game
         * 
         * @param r the registery comming from the Game Engine
         */
        virtual void initGame(registry &r) = 0;

        /**
         * @brief Function used to execute all the game logic (handling event or phases of the game)
         * 
         * @param r the registery comming from the Game Engine
         * @param events the events that happened
         */
        virtual void run_gameLogic(registry &r, const Events &events) = 0;

        /**
         * @brief Function used to update the registery with data received from the server
         * 
         * @param r the registery comming from the Game Engine
         * @param data struct corresponding to every player's data
         */
        virtual void updateRegistry(registry &r, const GameData &data) = 0;

        /**
         * @brief Function used to update the registery with data received from the server
         * 
         * @param r the registery comming from the Game Engine
         * @param data struct corresponding to every players's datas
         */
        virtual void updateRegistry(registry &r, const GameData data[4]) = 0;


        /** 
         * @brief Function used to create a friendly "character" entity, giving it an id, and various parameters 
         * @param r registry the registery to update
         * @param newEntity Entity ID
         * @param velX int16_t corresponding to the vertical velocity
         * @param velY int16_t corresponding to the horizontal velocity
         * @param posX uint16_t corresponding to the vertical position
         * @param posY uint16_t corresponding to the horizontal position
         **/
        virtual void create_player(registry &r, entity newEntity, bool isControllable, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY) = 0;

        /**
         * @brief Function used to create an enemy "character" entity, giving it an id, and various parameters 
         * @param r registry the registery to update
         * @param newEntity Entity ID, has to be unused
         * @param velX int16_t corresponding to the vertical velocity
         * @param velY int16_t corresponding to the horizontal velocity
         * @param posX uint16_t corresponding to the vertical position
         * @param posY uint16_t corresponding to the horizontal position
         **/
        virtual void create_enemy_entity(registry &r, entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, uint16_t posY) = 0;

        /** 
         * @brief Function used to create an entity, giving it an id, and various parameters.
         * @param r registry the registery to update
         * @param newEntity Entity ID, has to be unused
         * @param velX int16_t corresponding to the vertical velocity
         * @param velY int16_t corresponding to the horizontal velocity
         * @param posX uint16_t corresponding to the vertical position
         * @param posY uint16_t corresponding to the horizontal position
         */
        virtual void create_entity(registry &r, entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY) = 0;

        /**
         * @brief Generate a projectile using the id of a previously generated ship entity
         * @param r registry the registery to update
         * @param newEntity Entity ID, has to be unused
         * @param parentId id of the parent ship
         * @param col color
         * @param velX x velocity
         * @param velY y velocity
         * @return a projectile entity 
        */
        virtual void create_projectile(registry &r, entity newEntity, int16_t parentId, const uint16_t velX, const uint16_t velY) = 0;

    protected:
    private:
};

#endif /* !IGAME_HPP_ */

/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Rtype
*/

#ifndef RTYPE_HPP_
#define RTYPE_HPP_

#include "IGame.hpp"
#include <memory>

class Rtype : public IGame {
    public:
        Rtype();
        ~Rtype();

        /**
         * @brief Function used to create all starting assets needed fro the game
         * 
         * @param r the registery comming from the Game Engine
         */
        void initGame(registry &r);

        /**
         * @brief Function used to execute all the game logic (handling event or phases of the game)
         * 
         * @param r the registery comming from the Game Engine
         */
        void run_gameLogic(registry &r, EntityEvent events);

        /**
         * @brief Function used to update the registery with data received from the server
         * 
         * @param data struct corresponding to every player's data
         */
        void updateRegistry(registry &r, GameData data);

        /** 
         * @brief Function used to create a friendly "character" entity, giving it an id, and various parameters 
         * @param r registry the registery to update
         * @param newEntity Entity ID
         * @param velX int16_t corresponding to the vertical velocity
         * @param velY int16_t corresponding to the horizontal velocity
         * @param posX uint16_t corresponding to the vertical position
         * @param posY uint16_t corresponding to the horizontal position
         **/
        void create_player(registry &r, entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY);
        
        /**
         * @brief Function used to create an enemy "character" entity, giving it an id, and various parameters 
         * @param r registry the registery to update
         * @param newEntity Entity ID, has to be unused
         * @param velX int16_t corresponding to the vertical velocity
         * @param velY int16_t corresponding to the horizontal velocity
         * @param posX uint16_t corresponding to the vertical position
         * @param posY uint16_t corresponding to the horizontal position
         **/
        void create_enemy_entity(registry &r, entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, uint16_t posY);

        /** 
         * @brief Function used to create an entity, giving it an id, and various parameters.
         * @param r registry the registery to update
         * @param newEntity Entity ID, has to be unused
         * @param velX int16_t corresponding to the vertical velocity
         * @param velY int16_t corresponding to the horizontal velocity
         * @param posX uint16_t corresponding to the vertical position
         * @param posY uint16_t corresponding to the horizontal position
         */
        void create_entity(registry &r, entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY);

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
        void create_projectile(registry &r, entity newEntity, int16_t parentId, const uint16_t velX, const uint16_t velY);

        void create_parallax(registry &r, entity newEntity, const uint16_t posX, const uint16_t posY, const uint16_t speed, const OBJECT obj);

    protected:
    private:
        entity _player;

};

extern "C" std::shared_ptr<IGame> createLibrary();

#endif /* !RTYPE_HPP_ */
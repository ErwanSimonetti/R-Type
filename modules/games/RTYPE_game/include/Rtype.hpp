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
#include <unordered_map>

enum OBJECT_TYPE {
    EMPTY = -1,
    SHIP,
    ENEMYSHIP,
    BULLET,
    PARA_1,
    PARA_2,
    PARA_3,
    PARA_4,
    PLAY,
    EXIT,
    RTYPE,
    HEALTH
};

enum MENU_EVENT {
    LAUNCHGAME,
    EXITGAME
};

class Rtype : public IGame {
    public:
        Rtype();
        ~Rtype();

        std::vector<entity> &getPlayers();
        
        void setPlayers(std::vector<entity> newPlayers);
 
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
        std::vector<GAME_EVENT> run_gameLogic(registry &r);

        /**
         * @brief Function used to update the registery with data received from the server
         * 
         * @param data struct corresponding to every player's data
         */
        void updateRegistry(registry &r, const GameData &data);

        void updateRegistry(registry &r, const GameData data[4]);
        void checkStats(sparse_array<Hitbox> &hbxs, sparse_array<Stats> &sts, sparse_array<Pet> &pets);
        void create_score(registry &r, entity newEntity, int16_t parentId, std::string score, const int16_t posX, const int16_t posY);

        /** 
         * @brief Function used to create a friendly "character" entity, giving it an id, and various parameters 
         * @param r registry the registery to update
         * @param newEntity Entity ID
         * @param velX int16_t corresponding to the vertical velocity
         * @param velY int16_t corresponding to the horizontal velocity
         * @param posX uint16_t corresponding to the vertical position
         * @param posY uint16_t corresponding to the horizontal position
         **/
        void create_player(registry &r, entity newEntity, bool isControllable, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY);

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
        void create_parallax(registry &r, entity newEntity, const uint16_t posX, const uint16_t posY, const uint16_t speed, const int16_t obj);

        void create_static(registry &r, entity newEntity, const uint16_t posX, const uint16_t posY, int16_t type);
        void createButton(registry &r, entity newEntity, int16_t posX, int16_t posY, int16_t type, uint16_t event);

    protected:
        void handleInputs(registry &r, size_t entity, const uint16_t inputs[10]);
        void menuEvent(registry &reg, sparse_array<Cliquable> &cliquables);
        void addMenuEvent();
        void LaunchGame(registry &r);
        void closeGame(registry &r);

    private:
        /**
         * @brief players vector 
         **/ 
        std::vector<entity> _players;
        std::unordered_map<int, std::function<void(registry&)>> _menuEvent;
        std::vector<GAME_EVENT> _gameEvents;

};

extern "C" std::shared_ptr<IGame> createLibrary();

#endif /* !RTYPE_HPP_ */

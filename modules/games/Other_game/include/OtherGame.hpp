/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** OtherGame
*/

#ifndef OTHERGAME_HPP_
#define OTHERGAME_HPP_

#include "IGame.hpp"
#include <memory>

enum OBJECT_TYPE {
    EMPTY = -1,
    PLAYER,
    WATER,
    FLAG,
    GRASS,
    LADDER,
    TREE,
    PARA_4
};


class OtherGame : public IGame {
    public:
        OtherGame();
        ~OtherGame();

        void setPlayers(std::vector<entity> newPlayers);

        std::vector<entity> &getPlayers();

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
         * @param events the events that happened
         */
        std::vector<GAME_EVENT> run_gameLogic(registry &r);

        /**
         * @brief Function used to update the registery with data received from the server
         * 
         * @param data struct corresponding to every player's data
         */
        void updateRegistry(registry &r, const GameData &data);

        void updateRegistry(registry &r, const GameData data[4]);

        /** 
         * @brief Function used to create a friendly "character" entity, giving it an id, and various parameters 
         * @param r registry the registery to update
         * @param newEntity Entity ID
         * @param velX int16_t corresponding to the vertical velocity
         * @param velY int16_t corresponding to the horizontal velocity
         * @param posX uint16_t corresponding to the vertical position
         * @param posY uint16_t corresponding to the horizontal position
         **/
        void create_player(registry &r, entity newEntity, bool isControllable, const int16_t velX, const int16_t velY, const int16_t posX, const int16_t posY, const int16_t posZ);

        void create_static(registry &r, entity newEntity, const int16_t posX, const int16_t posY, const int16_t posZ, bool hasHitBoxe, uint16_t type);
        
    protected:
        void handleInputs(registry &r, size_t entity, const uint16_t inputs[10]);
    private:
        /**
         * @brief players vector 
         **/ 
        std::vector<entity> _players;
};

extern "C" std::shared_ptr<IGame> createLibrary();

#endif /* !OTHERGAME_HPP_ */

/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "registry.hpp"
#include "GameEvents.hpp"
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
        virtual std::vector<GAME_EVENT> run_gameLogic(registry &r) = 0;

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

    protected:
    private:
};

#endif /* !IGAME_HPP_ */

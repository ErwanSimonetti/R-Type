/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine
*/

#pragma once

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "RenderGame.hpp"
<<<<<<< HEAD
#include "MyNetwork.hpp"
=======
#include "Network.hpp"
>>>>>>> 6be9af8 (feat(hierarchy) split the project in two section: client & server)
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "Engine_utils.hpp"

/// @brief Engine class used to handle everything related to the game engine

class Engine {
    public:
        /// @brief Create a new instance of object Engine, with a game window size of width and height 
        /// @param width Width of the game window
        /// @param height Height of the game window
        Engine(uint16_t width, uint16_t height, boost::asio::io_service &io_service, const std::string &port);
        Engine(uint16_t width, uint16_t height, boost::asio::io_service &io_service, const std::string &host, const std::string &port);
        ~Engine();
        
        /// @brief Registry variable getter
        /// @return the registry object
        registry get_registry();

        /// @brief Function used to create a friendly "character" entity, giving it an id, and various parameters 
        /// @param id Entity ID
        /// @param col sf::Color object, until we use actual sprites
        /// @param velX uint_16_t corresponding to the vertical velocity
        /// @param velY uint_16_t corresponding to the horizontal velocity
        /// @param posX uint_16_t corresponding to the vertical position
        /// @param posY uint_16_t corresponding to the horizontal position
<<<<<<< HEAD
        void create_player(entity newEntity, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY);

        void create_entity(entity newEntity, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY);
=======
        /// @return a friendly entity, that is controllable
        entity create_friendly_entity(int id, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY);
>>>>>>> 6be9af8 (feat(hierarchy) split the project in two section: client & server)
        
        /// @brief Function used to create an enemy "character" entity, giving it an id, and various parameters 
        /// @param id Entity ID, has to be unused
        /// @param col sf::Color object, until we use actual sprites
        /// @param velX uint_16_t corresponding to the vertical velocity
        /// @param velY uint_16_t corresponding to the horizontal velocity
        /// @param posX uint_16_t corresponding to the vertical position
        /// @param posY uint_16_t corresponding to the horizontal position
<<<<<<< HEAD
        void create_enemy_entity(entity newEntity, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, uint16_t posY);
        
        /// @brief function used to launch the whole game, systems and all
        void run();

        void sendData(ServerData data);

        void updateRegistry(ClientData data);

        ServerData buildServerData();

        void runNetwork();

        void runGame();

        MyNetwork _network;
=======
        /// @return an enemy enity, that cannot be controlled by the user
        entity create_enemy_entity(int id, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, uint16_t posY);
        
        /// @brief function used to launch the whole game, systems and all
        void run_game();

        void sendData(ServerData data);

        void UpdateRegistery(ClientData newData);

        ClientData buildClientData(EntityEvent entityEvent);

        void printMonCul(ClientData clientData) {
            std::cerr << "⠄⠄⠸⣿⣿⢣⢶⣟⣿⣖⣿⣷⣻⣮⡿⣽⣿⣻⣖⣶⣤⣭⡉⠄⠄⠄⠄⠄\n⠄⠄⠄⢹⠣⣛⣣⣭⣭⣭⣁⡛⠻⢽⣿⣿⣿⣿⢻⣿⣿⣿⣽⡧⡄⠄⠄⠄\n⠄⠄⠄⠄⣼⣿⣿⣿⣿⣿⣿⣿⣿⣶⣌⡛⢿⣽⢘⣿⣷⣿⡻⠏⣛⣀⠄⠄\n⠄⠄⠄⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⠙⡅⣿⠚⣡⣴⣿⣿⣿⡆⠄\n⠄⠄⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠄⣱⣾⣿⣿⣿⣿⣿⣿⠄\n⠄⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⣿⣿⣿⣿⣿⣿⣿⣿⠄\n⠄⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠣⣿⣿⣿⣿⣿⣿⣿⣿⣿⠄\n⠄⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠑⣿⣮⣝⣛⠿⠿⣿⣿⣿⣿⠄\n⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⠄⠄⠄⠄⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠄\n⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠄⠄⠄⠄⢹⣿⣿⣿⣿⣿⣿⣿⣿⠁⠄\n⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠄⠄⠄⠄⠄⠸⣿⣿⣿⣿⣿⡿⢟⣣⣀\n";
            std::cerr << "|" << clientData.entity << "|" << "\n";
            std::cerr << "|" << clientData.posX << " " << clientData.posY << "|" << "\n";
        }

        Network _network;
>>>>>>> 6be9af8 (feat(hierarchy) split the project in two section: client & server)
    protected:
    private:
        /// @brief registry object 
        registry _reg;
<<<<<<< HEAD
        std::vector<entity> _players;
=======
>>>>>>> 6be9af8 (feat(hierarchy) split the project in two section: client & server)
};

#endif /* !ENGINE_HPP_ */
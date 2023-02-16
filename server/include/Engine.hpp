/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine
*/

#pragma once

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <boost/asio.hpp>
#include <boost/array.hpp>

#include "MyNetwork.hpp"
#include "Engine_utils.hpp"
#include "registry.hpp"
#include "System.hpp"
#include "Engine_utils.hpp"

struct Player {
    entity id;
    bool hasShot;
};

/// @brief Engine class used to handle everything related to the game engine
class Engine {
    public:

        /**
         * @brief Create a new instance of object Engine, with a game window size of width and height 
         * 
         * @param width width of the game window
         * @param height height of the game window
         * @param io_service core I/O functionality for users of the asynchronous I/O objects
         * @param port listening port
         */
        Engine(uint16_t width, uint16_t height, boost::asio::io_service &io_service, const std::string &port);

        /**
         * @brief Create a new instance of object Engine, with a game window size of width and height 
         * 
         * @param width width of the game window
         * @param height height of the game window
         * @param io_service core I/O functionality for users of the asynchronous I/O objects
         * @param host listening IP
         * @param port listening port
         */
        Engine(uint16_t width, uint16_t height, boost::asio::io_service &io_service, const std::string &host, const std::string &port);
        ~Engine();
        
        /**
         * @brief Get the registry object
         * 
         * @return registry 
         */
        registry get_registry();

        /** @brief Function used to create a friendly "character" entity, giving it an id, and various parameters 
         * @param newEntity Entity ID
         * @param velX int16_t corresponding to the vertical velocity
         * @param velY int16_t corresponding to the horizontal velocity
         * @param posX uint16_t corresponding to the vertical position
         * @param posY uint16_t corresponding to the horizontal position
         **/
        void create_player(entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY);

        /** 
         * @brief Function used to create an entity, giving it an id, and various parameters
         * @param newEntity Entity ID, has to be unused
         * @param velX int16_t corresponding to the vertical velocity
         * @param velY int16_t corresponding to the horizontal velocity
         * @param posX uint16_t corresponding to the vertical position
         * @param posY uint16_t corresponding to the horizontal position
         * @return an enity, that might be controlled by the user
         */
        void create_entity(entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY);
        
        /**
         * @brief Function used to create an enemy "character" entity, giving it an id, and various parameters 
         * @param newEntity Entity ID, has to be unused
         * @param velX int16_t corresponding to the vertical velocity
         * @param velY int16_t corresponding to the horizontal velocity
         * @param posX uint16_t corresponding to the vertical position
         * @param posY uint16_t corresponding to the horizontal position
         * @return an enemy enity, that might be controlled by the user
         */
        void create_enemy_entity(entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, uint16_t posY);
        
        /**
         * @brief function used to launch the whole game, systems and all 
         */
        void run();

        /**
         * @brief Function used to send each player's data to the server
         * 
         * @param data struct corresponding to each player's data
         */
        void sendData(ServerData data);

        /**
         * @brief Function used to update the registery with data received from the server
         * 
         * @param data struct corresponding to every player's data
         */
        void updateRegistry(ClientData data);

        ServerData buildServerData();

        /**
         * @brief Runs network threads
         */
        void runNetwork();

        /**
         * @brief runs the whole game
         */
        void runGame();

        MyNetwork _network;
    protected:
    private:

        /**
         * @brief registry object 
         **/
        registry _reg;

        /**
         * @brief players vector 
         **/ 
        std::vector<Player> _players;
};

#endif /* !ENGINE_HPP_ */
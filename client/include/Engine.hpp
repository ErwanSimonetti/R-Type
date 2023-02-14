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
#include "MyNetwork.hpp"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "Engine_utils.hpp"

/**
 * @brief A class used to handle everything related to the game engine
 * 
 */
class Engine {
    public:
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
        registry &get_registry();

        /** 
         * @brief Function used to create a friendly "character" entity, giving it an id, and various parameters 
         * @param id Entity ID
         * @param col sf::Color object, until we use actual sprites
         * @param velX uint_16_t corresponding to the vertical velocity
         * @param velY uint_16_t corresponding to the horizontal velocity
         * @param posX uint_16_t corresponding to the vertical position
         * @param posY uint_16_t corresponding to the horizontal position
         * @return a friendly entity, that is controllable
         **/
        void create_player(entity newEntity, const uint16_t speedX, const uint16_t speedY, const uint16_t posX, const uint16_t posY);
        
        /**
         * @brief Function used to create an enemy "character" entity, giving it an id, and various parameters 
         * @param id Entity ID, has to be unused
         * @param col sf::Color object, until we use actual sprites
         * @param velX uint_16_t corresponding to the vertical velocity
         * @param velY int_16_t corresponding to the horizontal velocity
         * @param posX uint_16_t corresponding to the vertical position
         * @param posY uint_16_t corresponding to the horizontal position
         * @return an enemy enity, that might be controlled by the user
         **/
        void create_enemy_entity(entity newEntity, const uint16_t speedX, const uint16_t speedY, const uint16_t posX, uint16_t posY);

        /** 
         * @brief Function used to create an entity, giving it an id, and various parameters.
         * @param id Entity ID, has to be unused
         * @param velX uint_16_t corresponding to the vertical velocity
         * @param velY uint_16_t corresponding to the horizontal velocity
         * @param posX uint_16_t corresponding to the vertical position
         * @param posY uint_16_t corresponding to the horizontal position
         * @return an enity, that might be controlled by the user
         */
        void create_entity(entity newEntity, const uint16_t speedX, const uint16_t speedY, const uint16_t posX, const uint16_t posY);

        void create_projectile(entity newEntity, int16_t parentId, const uint16_t velX, const uint16_t velY);

        void create_parallax(entity newEntity, const uint16_t posX, const uint16_t posY, const uint16_t speed, const OBJECT obj);

        void connectToServer();
        ClientData buildClientData(EntityEvent entityEvent);

        /**
         * @brief Function used to send each player's data to the server
         * 
         * @param data struct corresponding to each player's data
         */
        void sendData(ClientData data);

        /**
         * @brief Function used to update the registery with data received from the server
         * 
         * @param data struct corresponding to every player's data
         */
        void updateRegistry(ServerData data);

        /**
         * @brief Runs network threads
         * 
         */
        void runNetwork();

        /**
         * @brief runs the whole game
         * 
         */
        void runGame();

        /**
         * @brief function used to launch the whole game, systems and all
         * 
         */
        void run();

    protected:
    private:
        /**
         * @brief registry object 
         **/
        registry _reg;

        MyNetwork _network;

        /**
         * @brief SFML encapsulation 
         **/
        RenderGame _game;
        entity _player;
};

#endif /* !ENGINE_HPP_ */
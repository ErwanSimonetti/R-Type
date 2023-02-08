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

/// @brief Engine class used to handle everything related to the game engine

class Engine {
    public:
        /// @brief Create a new instance of object Engine, with a game window size of width and height 
        /// @param width Width of the game window
        /// @param height Height of the game window
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
        void create_player(entity newEntity, const uint16_t speedX, const uint16_t speedY, const uint16_t posX, const uint16_t posY);
        
        /// @brief Function used to create an enemy "character" entity, giving it an id, and various parameters 
        /// @param id Entity ID, has to be unused
        /// @param col sf::Color object, until we use actual sprites
        /// @param velX uint_16_t corresponding to the vertical velocity
        /// @param velY uint_16_t corresponding to the horizontal velocity
        /// @param posX uint_16_t corresponding to the vertical position
        /// @param posY uint_16_t corresponding to the horizontal position
        void create_enemy_entity(entity newEntity, const uint16_t speedX, const uint16_t speedY, const uint16_t posX, uint16_t posY);

        void create_entity(entity newEntity, const uint16_t speedX, const uint16_t speedY, const uint16_t posX, const uint16_t posY);

        /// @brief Generate a projectile using the id of a previously generated ship entity
        /// @param parentId id of the parent ship
        /// @param col color
        /// @param velX x velocity
        /// @param velY y velocity
        /// @return a projectile entity 
        entity create_projectile(int parentId, const uint16_t velX, const uint16_t velY);

        entity create_parallax(const int16_t id, const uint16_t posX, const uint16_t posY, const uint16_t speed, const OBJECT obj);
        
        void connectToServer();
        ClientData buildClientData(EntityEvent entityEvent);
        void sendData(ClientData data);
        void updateRegistry(ServerData data);

        void runNetwork();
        void runGame();
        /// @brief function used to launch the whole game, systems and all
        void run();

    protected:
    private:
        /// @brief registry object 
        registry _reg;
        MyNetwork _network;
        /// @brief SFML encapsulation
        RenderGame _game;
        entity _player;
};

#endif /* !ENGINE_HPP_ */
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
#include "IGraphic.hpp"
#include "IGame.hpp"
#include "LoadLibrary.hpp"
#include "GameEvents.hpp"

using create_d_graphic = std::shared_ptr<IGraphic> (*)();
using create_d_game = std::shared_ptr<IGame> (*)();


enum MODULE_TYPE {
    GAME,
    GRAPHIC
};

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
        Engine(boost::asio::io_service &io_service, const std::string &host, const std::string &port, const std::string &graphicLibrary);
        ~Engine();
        
        /**
         * @brief Get the registry object
         * 
         * @return registry 
         */
        registry &get_registry();

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

        void loadModules(std::string libName, MODULE_TYPE type);


    protected:
    private:
        /**
         * @brief registry object 
         **/
        registry _reg;
        MyNetwork _network;
        entity _player;

        /**
         * @brief modules 
         **/
        std::shared_ptr<IGraphic> _graphic;
        std::shared_ptr<IGame> _game;
};

#endif /* !ENGINE_HPP_ */
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
#include "registry.hpp"
#include "System.hpp"
#include "IGame.hpp"
#include "LoadLibrary.hpp"

using create_d_game = std::shared_ptr<IGame> (*)();

enum MODULE_TYPE {
    GAME,
    GRAPHIC
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
        Engine(boost::asio::io_service &io_service, const std::string &host, const std::string &port, const std::string &graphicModulePath);
        ~Engine();


        /**
         * @brief Create a new instance of object Engine, with a game window size of width and height 
         * 
         * @param width width of the game window
         * @param height height of the game window
         * @param io_service core I/O functionality for users of the asynchronous I/O objects
         * @param host listening IP
         * @param port listening port
         */
        
        /**
         * @brief Get the registry object
         * 
         * @return registry 
         */
        registry get_registry();

        /**
         * @brief Get the registry object
         * 
         * @param libName std::string the path to the .so
         * @param type MODULE_TYPE Enum representing the type of module is being loaded
         */
        void loadModules(std::string libName, MODULE_TYPE type);
        
        /**
         * @brief function used to launch the whole game, systems and all 
         */
        void run();

        /**
         * @brief Function used to send each player's data to the server
         * 
         * @param data struct corresponding to each player's data
         */
        template<typename T>
        void addDataInSendBuffer(const T& data, int header, std::vector<char> &buffer) 
        {
            Header sendHeader{header};
            const char* headerBytes = _network.getProtocol().serialiseData<Header>(sendHeader);
            const char* dataBytes = _network.getProtocol().serialiseData<T>(data);

            buffer.reserve(buffer.size() + sizeof(Header) + sizeof(T));
            buffer.insert(buffer.end(), headerBytes, headerBytes + sizeof(Header));
            buffer.insert(buffer.end(), dataBytes, dataBytes + sizeof(T));
        }

        void sendData(std::vector<char> &data);

        /**
         * @brief Function used to update the registery with data received from the server
         * 
         * @param data struct corresponding to every player's data
         */
        void updateRegistry(char *data);

        ServerData buildServerData(size_t id, uint16_t inputs[10]);

        /**
         * @brief Runs network threads
         */
        void runNetwork();

        /**
         * @brief runs the whole game
         */
        void runGame();

        /**
         * @brief runs the Interactive Command Line
         */
        void runServerCommandLine();

    protected:
    private:

        /**
         * @brief registry object 
         **/
        registry _reg;
        MyNetwork _network;

        /**
         * @brief modules 
         **/
        std::shared_ptr<IGame> _game;

        void sendEnemies(registry &r, sparse_array<Position> &positions, sparse_array<Velocity> &velocities, const sparse_array<Drawable> &drawable);
};

#endif /* !ENGINE_HPP_ */
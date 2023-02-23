/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ProtocolServer
*/

#ifndef PROTOCOLSERVER_HPP_
#define PROTOCOLSERVER_HPP_

#include <unordered_map>
#include <functional>
#include <cstddef>

#include "Header.hpp"
#include "AProtocol.hpp"
#include "NewPlayer.hpp"

namespace Protocol
{
    class ProtocolServer : public IProtocol {
        public:
            ProtocolServer()
            {
                std::cout << "Hey, I build a new Protocol Server." << std::endl;
                _idToType.emplace(1, std::bind(&ProtocolServer::receivePlayer, this, std::placeholders::_1, std::placeholders::_2));
            };

            ~ProtocolServer() = default;

            void read(char *buffer)
            {
                std::cout << "Receive buffer of size == " << strlen(buffer) << std::endl;
                Header* ptr1 = reinterpret_cast<Header*>(buffer);
                std::cout << "Header ==  [" << ptr1->_id << "]" << std::endl;

                std::cout << "Size of the map == " << _idToType.size() << std::endl;
                if (_idToType.count(ptr1->_id)) {
                    _idToType[ptr1->_id](buffer, sizeof(Header));
                } else {
                    std::cout << "Error: Invalid header id : "  << ptr1->_id << " not found." << std::endl;
                }
            };

        protected:
        private:

            void receivePlayer(char *buffer, size_t lenghtValue)
            {
                NewPlayer* ptr1 = reinterpret_cast<NewPlayer*>(buffer + lenghtValue);
                std::cout << "receiveNewPlayer" << std::endl;
                std::cout << "ID == " << ptr1->id << std::endl;
            }

            std::unordered_map<int, std::function<void(char *, size_t)>> _idToType;
    };
}

#endif /* !PROTOCOLSERVER_HPP_ */

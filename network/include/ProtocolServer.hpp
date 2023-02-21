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
    class ProtocolServer : public AProtocol {
        public:
            ProtocolServer() : AProtocol()
            {
                std::cout << "Hey, I build a new Protocol Server." << std::endl;
                _idToType.emplace(1, std::bind(&ProtocolServer::receivePlayer, this, std::placeholders::_1, std::placeholders::_2));
            };

            ~ProtocolServer() = default;

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

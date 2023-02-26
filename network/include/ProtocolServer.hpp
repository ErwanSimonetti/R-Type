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
#include "IProtocol.hpp"
#include "NewPlayer.hpp"

namespace Protocol
{
    class ProtocolServer : public IProtocol {
        public:
            ProtocolServer() :
                _network(nullptr)
            {
                std::cout << "Hey, I build a new Protocol Server." << std::endl;
                _idToType.emplace(1, std::bind(&ProtocolServer::receivePlayer, this, std::placeholders::_1, std::placeholders::_2));
                _idToType.emplace(2, std::bind(&ProtocolServer::receiveClientData, this, std::placeholders::_1, std::placeholders::_2));
            };

            ~ProtocolServer() = default;

            void read(char *buffer)
            {
                Header* ptr1 = reinterpret_cast<Header*>(buffer);

                std::cout << "Receive header == " << ptr1->_id << std::endl;

                if (_idToType.count(ptr1->_id)) {
                    _idToType[ptr1->_id](buffer, sizeof(Header));
                } else {
                    std::cout << "Error: Invalid header id : "  << ptr1->_id << " not found." << std::endl;
                }
            };

            char *askConnection(char *buffer, int id)
            {

            }

            void setNetwork(MyNetwork &net)
            {
                _network = std::make_shared<MyNetwork>(net);
            }

        protected:
        private:

            void receivePlayer(char *buffer, size_t lenghtValue)
            {
                NewPlayer* ptr1 = reinterpret_cast<NewPlayer*>(buffer + lenghtValue);
                std::cout << "receiveNewPlayer" << std::endl;
                std::cout << "ID == " << ptr1->id << std::endl;
                if (_network->getEndpoints().size() > 4) {
                    std::cout << "Connection refused" << std::endl;
                } else {
                    std::cout << "Connection accepted" << std::endl;
                }
            }

            void receiveClientData(char *buffer, size_t lenghtValue)
            {
                ClientData* ptr1 = reinterpret_cast<ClientData*>(buffer + lenghtValue);
                std::cout << "receiveNewClientData" << std::endl;
                std::cout << "directionsX == " << ptr1->directionsX << std::endl;
                std::cout << "directionsY == " << ptr1->directionsY << std::endl;
                std::cout << "Entity      == " << ptr1->entity << std::endl;
                std::cout << "hasshot     == " << ptr1->hasShot << std::endl;
                std::cout << "PosX        == " << ptr1->posX << std::endl;
                std::cout << "PosY        == " << ptr1->posY << std::endl;
            }


            std::unordered_map<int, std::function<void(char *, size_t)>> _idToType;
            std::shared_ptr<MyNetwork> _network;
    };
}

#endif /* !PROTOCOLSERVER_HPP_ */

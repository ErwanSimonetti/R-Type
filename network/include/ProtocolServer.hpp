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
#include "registry.hpp"
#include "IProtocol.hpp"
#include "Protocol.hpp"
#include "NewPlayer.hpp"
#include "MyNetwork.hpp"

namespace Protocol
{
    class ProtocolServer : public IProtocol {
        public:
            ProtocolServer(MyNetwork &net, std::unordered_map<int, std::function<void(void)>> &functionEngine) :
                _net(net),
                _functionEngine(functionEngine)
            {
                std::cout << "Hey, I build a new Protocol Server." << std::endl;
                _idToType.emplace(1, std::bind(&ProtocolServer::receiveRequestOfConnection, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                _idToType.emplace(2, std::bind(&ProtocolServer::receiveClientData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                _idToType.emplace(2, std::bind(&ProtocolServer::receiveInputPressed, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            };

            ~ProtocolServer() = default;

            void read(char *buffer, boost::asio::ip::udp::endpoint endpoint)
            {
                Header* ptr1 = reinterpret_cast<Header*>(buffer);

                std::cout << "Receive header == " << ptr1->_id << std::endl;

                if (_idToType.count(ptr1->_id)) {
                    _idToType[ptr1->_id](buffer, sizeof(Header), endpoint);
                } else {
                    std::cout << "Error: Invalid header id : "  << ptr1->_id << " not found." << std::endl;
                }
            };

            void askConnection()
            {

            }

        protected:
        private:

            void receiveRequestOfConnection(char *buffer, size_t lenghtValue, boost::asio::ip::udp::endpoint endpoint)
            {
                NewPlayer* ptr1 = reinterpret_cast<NewPlayer*>(buffer + lenghtValue);
                if (_net.getEndpoints().size() > 3) {
                    std::cout << "Send access refused to " << endpoint.address() << std::endl;
                    this->sendConnectionStatus(ConnectionStatus{false, -1}, endpoint);
                } else {
                    std::cout << "Nb of Endpoints == " << _net.getEndpoints().size() << std::endl;
                    if (_net.isNewEndpoint(endpoint))
                        _net.addEndpoint(endpoint);
                    _functionEngine[1]();
                    this->sendConnectionStatus(ConnectionStatus{true, 0}, endpoint);
                }
            }

            void receiveInputPressed(char *buffer, size_t lenghtValue, boost::asio::ip::udp::endpoint endpoint)
            {
                InputPressed* ptr1 = reinterpret_cast<InputPressed*>(buffer + lenghtValue);
            }

            void receiveClientData(char *buffer, size_t lenghtValue, boost::asio::ip::udp::endpoint endpoint)
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

            void sendConnectionStatus(const ConnectionStatus &coStatus, boost::asio::ip::udp::endpoint endpoint)
            {
                char buffer[1024];
                std::memcpy(buffer, Protocol::serialiseData<Header>(Header{1}), sizeof(Header));
                std::memcpy(buffer + sizeof(Header), Protocol::serialiseData<ConnectionStatus>(coStatus), sizeof(ConnectionStatus));
                _net.udpSend(buffer, endpoint, sizeof(buffer));
            }

            std::unordered_map<int, std::function<void(char *, size_t, boost::asio::ip::udp::endpoint)>> _idToType;
            MyNetwork &_net;
            std::unordered_map<int, std::function<void(void)>> &_functionEngine;
    };
}

#endif /* !PROTOCOLSERVER_HPP_ */

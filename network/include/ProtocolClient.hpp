/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ProtocolClient
*/

#ifndef PROTOCOLCLIENT_HPP_
#define PROTOCOLCLIENT_HPP_

#include <unordered_map>
#include <functional>
#include <cstddef>

#include "Header.hpp"
#include "Protocol.hpp"
#include "IProtocol.hpp"
#include "NewPlayer.hpp"

namespace Protocol
{
    class ProtocolClient : public IProtocol {
        public:
            ProtocolClient(MyNetwork &net, registry &reg) :
                _net(net),
                _reg(reg)
            {
                std::cout << "Hey, I build a new Protocol Client." << std::endl;
                _idToType.emplace(1, std::bind(&ProtocolClient::receiveStatusOfConnection, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            };

            ~ProtocolClient() = default;

            void read(char *buffer, boost::asio::ip::udp::endpoint endpoint)
            {
                std::cout << "Receive buffer of size == " << strlen(buffer) << std::endl;
                Header* ptr1 = reinterpret_cast<Header*>(buffer);
                std::cout << "Header ==  [" << ptr1->_id << "]" << std::endl;

                std::cout << "Size of the map == " << _idToType.size() << std::endl;
                if (_idToType.count(ptr1->_id)) {
                    _idToType[ptr1->_id](buffer, sizeof(Header), endpoint);
                } else {
                    std::cout << "Error: Invalid header id : "  << ptr1->_id << " not found." << std::endl;
                }
            };

            void askConnection()
            {
                char buffer[1024];
                std::memcpy(buffer, Protocol::serialiseData<Header>(Header{1}), sizeof(Header));
                std::memcpy(buffer + sizeof(Header), Protocol::serialiseData<NewPlayer>(NewPlayer{0}), sizeof(NewPlayer));
                std::cout << "Send access ask connection to " << _net.getServerEndpoint() << std::endl;
                _net.udpSend(buffer, _net.getServerEndpoint(), sizeof(buffer));
            }

        protected:
        private:

            void receiveStatusOfConnection(char *buffer, size_t lenghtValue, boost::asio::ip::udp::endpoint endpoint)
            {
                ConnectionStatus* ptr1 = reinterpret_cast<ConnectionStatus*>(buffer + lenghtValue);

                std::cout << "Receive Status of Connection" << std::endl;
                if (ptr1->isAccepted) {
                    std::cout << "Receive Status of Connection Accepted" << std::endl;
                    std::cout << "nbplayer == " << ptr1->nbPlayer << std::endl;

                } else {
                    std::cout << "Receive Status of Connection Refused" << std::endl;
                    _net._isSuspendClient = true;
                    _net._shouldCallback = false;
                }
            }

            std::unordered_map<int, std::function<void(char *, size_t, boost::asio::ip::udp::endpoint)>> _idToType;
            MyNetwork &_net;
            registry &_reg;
    };
}

#endif /* !PROTOCOLCLIENT_HPP_ */

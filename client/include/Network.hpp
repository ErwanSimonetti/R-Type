/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network
*/

#pragma once

#ifndef NETWORK_HPP_
#define NETWORK_HPP_


#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <vector>

#include "Protocol.hpp"

struct jaj {
    int lol;
    int lil;
};

class Network {
    public:
        Network(boost::asio::io_service &io_service, const std::string& host, const std::string& port);
        Network(boost::asio::io_service& io_service, const std::string &port);
        ~Network();
        
        void addEndpoint(boost::asio::ip::udp::endpoint endpoint);
        
        template <typename Data>
        void udpSend(char *buffer, boost::asio::ip::udp::endpoint endpoint) {
            _socket.async_send_to(boost::asio::buffer(buffer, sizeof(Data)), endpoint,
                [this, buffer, endpoint](boost::system::error_code /*ec*/, std::size_t bytes_sent) 
            {
                std::cerr << "Succefully sent: " << buffer << " to:" << endpoint << "\n";
            });
        }

        void UDPReceiveClient(std::function<void(ServerData)> func) {
            std::memset(_recvBuffer, '\0', 1024);
            boost::asio::ip::udp::endpoint endpoint;

            _socket.async_receive_from(boost::asio::buffer(_recvBuffer), endpoint,
            [this, func] (boost::system::error_code ec, std::size_t recvd_bytes) {
                if (ec || recvd_bytes >= 0)
                    UDPReceiveClient(func);
                std::cout << "Data received from Server\n";
                func(_protocol.readServer(_recvBuffer));
            });
        };

        void UDPReceiveServer(std::function<void(ClientData)> func) {
            std::memset(_recvBuffer, '\0', 1024);
            boost::asio::ip::udp::endpoint endpoint;

            _socket.async_receive_from(boost::asio::buffer(_recvBuffer), endpoint,
            [this, func] (boost::system::error_code ec, std::size_t recvd_bytes) {
                if (ec || recvd_bytes >= 0)
                    UDPReceiveServer(func);
                std::cout << "Data received from Client\n";
                std::cout << "[" << recvd_bytes << "] " << _recvBuffer << std::endl;
                func(_protocol.readClient(_recvBuffer));
            });
        };
        

        std::vector<boost::asio::ip::udp::endpoint> _endpoints;
    protected:
    private:
        boost::asio::ip::udp::socket _socket;
        char _recvBuffer[1024];

        Protocol _protocol;
};

#endif /* !NETWORK_HPP_ */

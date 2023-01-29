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
                [this, buffer, endpoint](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/) 
            {
                std::cerr << "Succefully sent: " << buffer << " to:" << endpoint << "\n";
            });
        }

        void udpReceive(std::function<void()> func);
        

        std::vector<boost::asio::ip::udp::endpoint> _endpoints;
    protected:
    private:
        boost::asio::ip::udp::socket _socket;
        char _recvBuffer[1024];

        Protocol _protocol;
};

#endif /* !NETWORK_HPP_ */

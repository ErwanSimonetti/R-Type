/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <vector>

class Network {
    public:
        Network(boost::asio::io_service& io_service);
        ~Network();
        
        void addEndpoint(boost::asio::ip::udp::endpoint endpoint);
        
        template <typename Data>
        void udpSend(char *buffer, boost::asio::ip::udp::endpoint endpoint);

        void udpReceive();
        

    protected:
    private:
        boost::asio::ip::udp::socket _socket;
        std::vector<boost::asio::ip::udp::endpoint> _endpoints;
        char _recvBuffer[1024];
};

#endif /* !NETWORK_HPP_ */

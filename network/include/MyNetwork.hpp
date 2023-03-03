/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** MyNetwork
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <vector>

class MyNetwork {
    public:
        MyNetwork(boost::asio::io_service &io_service, const std::string& host, const std::string& port);
        MyNetwork(boost::asio::io_service& io_service, const std::string &port);
        ~MyNetwork();
        
        void udpSend(char *buffer, boost::asio::ip::udp::endpoint endpoint, std::size_t const& sizeOfBuffer) {
            _socket.async_send_to(boost::asio::buffer(buffer, 1024), endpoint,
                [this, buffer, endpoint](boost::system::error_code ec, std::size_t bytes_sent) 
            {
            });
        }

        void UDPReceiveClient(std::function<void(char *)> func, bool shouldCallback);
        void UDPReceiveServer(std::function<void(char *)> func);

        void addEndpoint(boost::asio::ip::udp::endpoint endpoint);
        bool isNewEndpoint(boost::asio::ip::udp::endpoint endpoint);
        void manageMessageReceive(char *message, boost::asio::ip::udp::endpoint endpointSender);
        boost::asio::ip::udp::endpoint getServerEndpoint();
        boost::asio::io_service &getIOService();
        std::vector<boost::asio::ip::udp::endpoint> &getEndpoints();
        bool _isSuspendClient;
        bool _shouldCallback;

    protected:
    private:
        std::vector<boost::asio::ip::udp::endpoint> _endpoints;
        boost::asio::ip::udp::endpoint _endpoint;
        boost::asio::ip::udp::endpoint _receiverEndpoint;
        boost::asio::ip::udp::socket _socket;
        boost::asio::io_service &_io_services;
        char _recvBuffer[1024];

};

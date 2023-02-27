/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** MyNetwork
*/

#pragma once

#ifndef MYNETWORK_HPP_
#define MYNETWORK_HPP_


#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <vector>

#include "Protocol.hpp"

class MyNetwork {
    public:
        MyNetwork(boost::asio::io_service &io_service, const std::string& host, const std::string& port);
        MyNetwork(boost::asio::io_service& io_service, const std::string &port);
        ~MyNetwork();
        
        template <typename Data>
        void udpSend(char *buffer, boost::asio::ip::udp::endpoint endpoint) {
            _socket.async_send_to(boost::asio::buffer(buffer, sizeof(Data)), endpoint,
                [this, buffer, endpoint](boost::system::error_code ec, std::size_t bytes_sent) 
            {
            });
            std::cout << "out of send" << std::endl;
        }

        void UDPReceiveClient(std::function<void(ServerData)> func, bool shouldCallback);
        void UDPReceiveServer(std::function<void(ClientData)> func);

        void addEndpoint(boost::asio::ip::udp::endpoint endpoint);
        boost::asio::ip::udp::endpoint getServerEndpoint();
        boost::asio::io_service &getIOService();
        Protocol &getProtocol();
        std::vector<boost::asio::ip::udp::endpoint> &getEndpoints();

    protected:
    private:
        std::vector<boost::asio::ip::udp::endpoint> _endpoints;
        boost::asio::ip::udp::endpoint _endpoint;
        Protocol _protocol;
        boost::asio::ip::udp::socket _socket;
        boost::asio::io_service &_io_services;
        char _recvBuffer[1024];
        bool _shouldCallback;

};

#endif /* !MYNETWORK_HPP_ */

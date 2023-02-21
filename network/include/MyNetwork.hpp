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

#include "IProtocol.hpp"

class MyNetwork {
    public:
        MyNetwork(std::shared_ptr<Protocol::IProtocol> protocol, boost::asio::io_service &io_service, const std::string& host, const std::string& port);
        MyNetwork(std::shared_ptr<Protocol::IProtocol> protocol, boost::asio::io_service& io_service, const std::string &port);
        ~MyNetwork();
        
        template <typename Data>
        void udpSend(char *buffer, boost::asio::ip::udp::endpoint endpoint) {
            _socket.async_send_to(boost::asio::buffer(buffer, sizeof(Data)), endpoint,
                [this, buffer, endpoint](boost::system::error_code ec, std::size_t bytes_sent) 
            {
            });
        }

        void UDPReceiveClient(std::function<void(char *)> func, bool shouldCallback);
        void UDPReceiveServer(std::function<void(char *)> func);

        void addEndpoint(boost::asio::ip::udp::endpoint endpoint);
        boost::asio::ip::udp::endpoint getServerEndpoint();
        boost::asio::io_service &getIOService();
        // Protocol &getProtocol();
        std::vector<boost::asio::ip::udp::endpoint> &getEndpoints();

    protected:
    private:
        std::vector<boost::asio::ip::udp::endpoint> _endpoints;
        boost::asio::ip::udp::endpoint _endpoint;
        std::shared_ptr<Protocol::IProtocol> _protocol;
        boost::asio::ip::udp::socket _socket;
        boost::asio::io_service &_io_services;
        char _recvBuffer[1024];
        bool _shouldCallback;

};

#endif /* !MYNETWORK_HPP_ */

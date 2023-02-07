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
        
        void addEndpoint(boost::asio::ip::udp::endpoint endpoint);
        
        template <typename Data>
        void udpSend(char *buffer, boost::asio::ip::udp::endpoint endpoint) {
            _socket.async_send_to(boost::asio::buffer(buffer, sizeof(Data)), endpoint,
                [this, buffer, endpoint](boost::system::error_code ec, std::size_t bytes_sent) 
            {
            });
        }

        void UDPReceiveClient(std::function<void(ServerData)> func, bool shouldCallback) {
            std::memset(_recvBuffer, '\0', 1024);
            boost::asio::ip::udp::endpoint endpoint;
            _shouldCallback = shouldCallback;
            _socket.async_receive_from(boost::asio::buffer(_recvBuffer), endpoint,
            [this, func] (boost::system::error_code ec, std::size_t recvd_bytes) {
                if (ec || recvd_bytes <= 0 && _shouldCallback)
                    UDPReceiveClient(func, _shouldCallback);
                func(_protocol.readServer(_recvBuffer));
                if (_shouldCallback)
                    UDPReceiveClient(func, _shouldCallback);
            });
        };

        void UDPReceiveServer(std::function<void(ClientData)> func) {
            std::memset(_recvBuffer, '\0', 1024);
            _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _endpoint,
            [this, func] (boost::system::error_code ec, std::size_t recvd_bytes) {
                if (ec || recvd_bytes <= 0)
                    UDPReceiveServer(func);
                addEndpoint(_endpoint);
                func(_protocol.readClient(_recvBuffer));
                UDPReceiveServer(func);
            });
        };

        boost::asio::ip::udp::endpoint getServerEndpoint();
        boost::asio::io_service &getIOService();
        

    protected:
    private:
        std::vector<boost::asio::ip::udp::endpoint> _endpoints;
        boost::asio::ip::udp::endpoint _endpoint;
        Protocol _protocol;
        boost::asio::ip::udp::endpoint _serverEndpoint;
        boost::asio::ip::udp::socket _socket;
        boost::asio::io_service &_io_services;
        char _recvBuffer[1024];
        bool _shouldCallback;

};

#endif /* !MYNETWORK_HPP_ */

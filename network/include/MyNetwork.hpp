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

#include "Header.hpp"
#include "Protocol.hpp"
#include "EndpointInformation.hpp"

class MyNetwork {
    public:
        MyNetwork(boost::asio::io_service &io_service, const std::string& host, const std::string& port);
        MyNetwork(boost::asio::io_service& io_service, const std::string &port);
        ~MyNetwork();
        
        void udpSend(char *buffer, const std::size_t &sizeOfBuffer, boost::asio::ip::udp::endpoint endpoint) {
            _socket.async_send_to(boost::asio::buffer(buffer, sizeOfBuffer), endpoint,
                [this, buffer, endpoint](boost::system::error_code ec, std::size_t bytes_sent) 
            {
            });
        }

        void udpSendToAllClients(char *buffer, std::size_t const& sizeOfBuffer) {
            for (int i = 0; i < _endpoints.size(); i++) {
                _socket.async_send_to(boost::asio::buffer(buffer, 1024), _endpoints.at(i)._endpoint,
                    [this](boost::system::error_code ec, std::size_t bytes_sent) 
                {
                });
            } 
        }

        template <class Data>
        char *serialiseData(Data data)
        {
            char *buffer = new char[sizeof(Data)];
            std::memcpy(buffer, &data, sizeof(Data));
            return buffer;
        };


        void UDPReceiveClient(std::function<void(ServerData)> func, bool shouldCallback);
        void UDPReceiveServer(std::function<void(ClientData)> func);

        void addEndpoint(boost::asio::ip::udp::endpoint endpoint);
        bool isNewEndpoint(boost::asio::ip::udp::endpoint endpoint);
        boost::asio::ip::udp::endpoint getServerEndpoint();
        boost::asio::io_service &getIOService();
        Protocol &getProtocol();
        std::vector<EndpointInformation> &getEndpoints();
        void kickPlayer(boost::asio::ip::udp::endpoint endpoint, bool isBan);
        void kickPlayer(const std::string &endpoint, bool isBan);
        bool isLobbyFull();
        bool isClientAccepted();

    protected:
    private:
        std::vector<EndpointInformation> _endpoints;
        std::vector<boost::asio::ip::udp::endpoint> _endpointsBannedPlayer;
        boost::asio::ip::udp::endpoint _endpoint;
        Protocol _protocol;
        boost::asio::ip::udp::socket _socket;
        boost::asio::io_service &_io_services;
        char _recvBuffer[1024];
        bool _shouldCallback;
        bool _isSuspendClient;
        bool _isClientAccepted;
};

#endif /* !MYNETWORK_HPP_ */

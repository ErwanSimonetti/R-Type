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

#include "Header.hpp"
#include "Protocol.hpp"
#include "EndpointInformation.hpp"

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

        void UDPReceiveClient(std::function<void(char *)> func, bool shouldCallback);
        void UDPReceiveServer(std::function<void(char *)> func);

        void addEndpoint(boost::asio::ip::udp::endpoint endpoint, const bool& status);
        bool isNewEndpoint(boost::asio::ip::udp::endpoint endpoint);
        void manageMessageReceive(char *message, boost::asio::ip::udp::endpoint endpointSender, std::function<void(char *, int)> func);
        boost::asio::ip::udp::endpoint getServerEndpoint();
        boost::asio::io_service &getIOService();
        std::vector<EndpointInformation> &getEndpoints();
        bool isLobbyFull();
        bool _isSuspendClient;
        bool _shouldCallback;

    protected:
    private:
        void checkRequestOfConnection(char* buffer, boost::asio::ip::udp::endpoint endpoint, int lenghtValue);
        void sendConnectionStatus(const ConnectionStatus &coStatus);

        std::vector<EndpointInformation> _endpoints;
        boost::asio::ip::udp::endpoint _endpoint;
        boost::asio::ip::udp::endpoint _receiverEndpoint;
        boost::asio::ip::udp::socket _socket;
        boost::asio::io_service &_io_services;
        char _recvBuffer[1024];
        bool _isClientAccepted;

};

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

struct jaj {
    int lol;
    int lil;
};

class MyNetwork {
    public:
        MyNetwork(boost::asio::io_service &io_service, const std::string& host, const std::string& port);
        MyNetwork(boost::asio::io_service& io_service, const std::string &port);
        ~MyNetwork();
        
        void addEndpoint(boost::asio::ip::udp::endpoint endpoint);
        
        template <typename Data>
        void udpSend(char *buffer, boost::asio::ip::udp::endpoint endpoint) {
    //         ClientData test;
    // std::memcpy(&test, buffer, sizeof(ClientData));
    // std::cerr << test.event << " " << test.string << "\n\n";
            _socket.async_send_to(boost::asio::buffer(buffer, sizeof(ClientData)), endpoint,
                [this, buffer, endpoint](boost::system::error_code /*ec*/, std::size_t bytes_sent) 
            {
                std::cerr << "nb byte : " << bytes_sent;
                std::cerr << "Succefully sent: " << buffer << " to:" << endpoint << "\n";
            });
        }

        void UDPReceiveClient(std::function<void(ServerData)> func) {
            std::memset(_recvBuffer, '\0', 1024);
            boost::asio::ip::udp::endpoint endpoint;

            _socket.async_receive_from(boost::asio::buffer(_recvBuffer), endpoint,
            [this, func] (boost::system::error_code ec, std::size_t recvd_bytes) {
                if (ec || recvd_bytes <= 0)
                    UDPReceiveClient(func);
                std::cout << "Data received from Server\n";
                func(_protocol.readServer(_recvBuffer));
                UDPReceiveClient(func);
            });
        };

        void UDPReceiveServer(std::function<void(ClientData)> func) {
            std::memset(_recvBuffer, '\0', 1024);
            boost::asio::ip::udp::endpoint endpoint;

            _socket.async_receive_from(boost::asio::buffer(_recvBuffer), endpoint,
            [this, func] (boost::system::error_code ec, std::size_t recvd_bytes) {
                if (ec || recvd_bytes <= 0)
                    UDPReceiveServer(func);
                std::cout << "Data received from Client\n";
                std::cout << "[" << recvd_bytes << "] " << _recvBuffer << std::endl;
                func(_protocol.readClient(_recvBuffer));
                UDPReceiveServer(func);
            });
        };

        boost::asio::ip::udp::endpoint getServerEndpoint();
        

        std::vector<boost::asio::ip::udp::endpoint> _endpoints;
        Protocol _protocol;
    protected:
    private:
        boost::asio::ip::udp::endpoint _serverEndpoint;
        boost::asio::ip::udp::socket _socket;
        char _recvBuffer[1024];

};

#endif /* !MYNETWORK_HPP_ */

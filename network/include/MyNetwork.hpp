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
    //         ClientData test;
    // std::memcpy(&test, buffer, sizeof(ClientData));
    // std::cerr << test.event << " " << test.string << "\n\n";
            printf("send was called \n");
            std::cout << "AAAAAAAAh " << endpoint << "\n";
            _socket.async_send_to(boost::asio::buffer(buffer, sizeof(Data)), endpoint,
                [this, buffer, endpoint](boost::system::error_code ec, std::size_t bytes_sent) 
            {
                std::cerr << "nb byte : " << bytes_sent;
                std::cerr << "Succefully sent: " << buffer << " to:" << endpoint << "\n";
            });
            std::cout << "out of send" << std::endl;
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
            // boost::asio::ip::udp::endpoint endpoint;
            std::cout << "change socket" << std::endl;
            _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _endpoint,
            [this, func] (boost::system::error_code ec, std::size_t recvd_bytes) {
                std::cout << "receive stg" << std::endl;
                if (ec || recvd_bytes <= 0)
                    UDPReceiveServer(func);
                addEndpoint(_endpoint);
                std::cout << "Data received from Client: ";
                std::cout << "[" << recvd_bytes << "] " << _recvBuffer << std::endl;
                func(_protocol.readClient(_recvBuffer));
                std::cout << "finish receive stg" << std::endl;
                UDPReceiveServer(func);
            });
        };

        boost::asio::ip::udp::endpoint getServerEndpoint();
        boost::asio::io_service &getIOService();
        

        std::vector<boost::asio::ip::udp::endpoint> _endpoints;
        boost::asio::ip::udp::endpoint _endpoint;
        Protocol _protocol;
    protected:
    private:
        boost::asio::ip::udp::endpoint _serverEndpoint;
        boost::asio::ip::udp::socket _socket;
        boost::asio::io_service &_io_services;
        char _recvBuffer[1024];

};

#endif /* !MYNETWORK_HPP_ */

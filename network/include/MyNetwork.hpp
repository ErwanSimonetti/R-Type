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

/**
 * @brief Network Encapsulation of the lib boost asio udp
 * 
 */
class MyNetwork {
    public:
        /**
         * @brief Construct a new My Network object
         * 
         * @param io_service give variable of asio lib
         * @param host ip adress of the server
         * @param port port in the ip adress
         */
        MyNetwork(boost::asio::io_service &io_service, const std::string& host, const std::string& port);

        /**
         * @brief Construct a new My Network object
         * 
         * @param io_service give variable of asio lib
         * @param port port in the ip adress
         */
        MyNetwork(boost::asio::io_service& io_service, const std::string &port);

        /**
         * @brief Destroy the My Network object
         * 
         */
        ~MyNetwork();

        /**
         * @brief Add endpoint to the list of endpoint in the server.
         * 
         * @param endpoint of the client
         */
        void addEndpoint(boost::asio::ip::udp::endpoint endpoint);

        /**
         * @brief send a buffer in udp
         * 
         * @tparam Data binerize with data type
         * @param buffer char * to send
         * @param endpoint target of the message
         */
        template <typename Data>
        void udpSend(char *buffer, boost::asio::ip::udp::endpoint endpoint) {
            _socket.async_send_to(boost::asio::buffer(buffer, sizeof(Data)), endpoint,
                [this, buffer, endpoint](boost::system::error_code ec, std::size_t bytes_sent) 
            {
            });
        }

        /**
         * @brief receive message in the client
         * 
         * @param func manager for the receive
         * @param shouldCallback state of send or not a message in return
         */
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

        /**
         * @brief receive message in the server
         * 
         * @param func manager for the receive
         */
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

        /**
         * @brief Get the Server Endpoint object
         * 
         * @return boost::asio::ip::udp::endpoint 
         */
        boost::asio::ip::udp::endpoint getServerEndpoint();

        /**
         * @brief getter for IO service
         * 
         * @return boost::asio::io_service& 
         */
        boost::asio::io_service &getIOService();

        /**
         * @brief getter the Protocol object
         * 
         * @return Protocol& 
         */
        Protocol &getProtocol() {
            return _protocol;
        }

        /**
         * @brief Get the Endpoints object with all target of the server
         * 
         * @return std::vector<boost::asio::ip::udp::endpoint>& 
         */
        std::vector<boost::asio::ip::udp::endpoint> &getEndpoints()
        {
            return _endpoints;
        }

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

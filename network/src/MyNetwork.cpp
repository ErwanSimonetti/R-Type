/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** MyNetwork
*/

#include "MyNetwork.hpp"

// client
MyNetwork::MyNetwork(boost::asio::io_service &io_service, const std::string& host, const std::string& port) : 
    _io_services(io_service), _socket(io_service, boost::asio::ip::udp::v4())
{
    boost::asio::ip::udp::endpoint serverEndpoint(boost::asio::ip::address::from_string(host), std::stoi(port));
    _endpoints.emplace_back(serverEndpoint);
    _shouldCallback = false;
}

// server
MyNetwork::MyNetwork(boost::asio::io_service& io_service, const std::string &port)
    : _io_services(io_service), _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), std::stoi(port)))
{
    _shouldCallback = false;
}

MyNetwork::~MyNetwork()
{
}

void MyNetwork::addEndpoint(boost::asio::ip::udp::endpoint endpoint)
{
    if ((std::find(_endpoints.begin(), _endpoints.end(), endpoint) != _endpoints.end())) {
        std::cerr << "User: " << endpoint << "\n";
    } else {
        std::cerr << "New user:" << endpoint << "connected\n";
        _endpoints.emplace_back(endpoint);
    }
}

boost::asio::ip::udp::endpoint MyNetwork::getServerEndpoint()
{
    return _endpoints.at(0);
}

boost::asio::io_service &MyNetwork::getIOService() {
    return _io_services;
}

/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** MyNetwork
*/

#include "MyNetwork.hpp"

// client
MyNetwork::MyNetwork(boost::asio::io_service &io_service, const std::string& host, const std::string& port) : 
    _io_services(io_service),
    _socket(io_service, boost::asio::ip::udp::v4())
{
    boost::asio::ip::udp::endpoint serverEndpoint(boost::asio::ip::address::from_string(host), std::stoi(port));
    _endpoints.emplace_back(serverEndpoint);
    _shouldCallback = false;
    _isSuspendClient = false;
}

// server
MyNetwork::MyNetwork(boost::asio::io_service& io_service, const std::string &port) :
    _io_services(io_service),
    _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 1234))
{
    _shouldCallback = false;
    _isSuspendClient = false;
}

MyNetwork::~MyNetwork()
{
}

bool MyNetwork::isNewEndpoint(boost::asio::ip::udp::endpoint endpoint)
{
    if ((std::find(_endpoints.begin(), _endpoints.end(), endpoint) != _endpoints.end())) {
        std::cerr << "User already connected : " << endpoint << std::endl;
        return false;
    }
    std::cerr << "New user:" << endpoint << "connected"  << std::endl;
    return true;    
}

void MyNetwork::addEndpoint(boost::asio::ip::udp::endpoint endpoint)
{
    _endpoints.emplace_back(endpoint);
}

void MyNetwork::setProtocol(std::shared_ptr<Protocol::IProtocol> iproto)
{
    _protocol = iproto;
}

boost::asio::ip::udp::endpoint MyNetwork::getServerEndpoint()
{
    return _endpoints.at(0);
}

boost::asio::io_service &MyNetwork::getIOService() 
{
    return _io_services;
}

// Protocol &MyNetwork::getProtocol() 
// {
//     return _protocol;
// }

std::vector<boost::asio::ip::udp::endpoint> &MyNetwork::getEndpoints()
{
    return _endpoints;
}

void MyNetwork::UDPReceiveClient(std::function<void(char *, boost::asio::ip::udp::endpoint)> func, bool shouldCallback) 
{
    std::memset(_recvBuffer, '\0', 1024);
    _shouldCallback = shouldCallback;
    _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _receiverEndpoint,
    [this, func] (boost::system::error_code ec, std::size_t recvd_bytes) {
        if (ec || recvd_bytes <= 0 && _shouldCallback)
            UDPReceiveClient(func, _shouldCallback);
        func(_recvBuffer, _receiverEndpoint);
        if (_shouldCallback)
            UDPReceiveClient(func, _shouldCallback);
    });
};

void MyNetwork::UDPReceiveServer(std::function<void(char *, boost::asio::ip::udp::endpoint endpoint)> func) 
{
    std::memset(_recvBuffer, '\0', 1024);
    _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _endpoint,
    [this, func] (boost::system::error_code ec, std::size_t recvd_bytes) {
        if (!ec)
        {
            if (ec || recvd_bytes <= 0)
                UDPReceiveServer(func);
            func(_recvBuffer, _endpoint);
            UDPReceiveServer(func);
        }
    });
};
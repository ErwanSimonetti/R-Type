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
    _endpoints.emplace_back(EndpointInformation{serverEndpoint, false});
    _shouldCallback = false;
}

// server
MyNetwork::MyNetwork(boost::asio::io_service& io_service, const std::string &port)
    : _io_services(io_service), _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 1234))
{
    _shouldCallback = false;
}

MyNetwork::~MyNetwork()
{
}

bool MyNetwork::isNewEndpoint(boost::asio::ip::udp::endpoint endpoint)
{
    for (size_t i = 0; i < _endpoints.size(); i++) {
        if (endpoint == _endpoints.at(i)._endpoint) {
            return false;
        }
    }
    std::cerr << "New user:" << endpoint << "connected"  << std::endl;
    return true;    
}

void MyNetwork::addEndpoint(boost::asio::ip::udp::endpoint endpoint)
{
    _endpoints.emplace_back(EndpointInformation{endpoint, true});
}

boost::asio::ip::udp::endpoint MyNetwork::getServerEndpoint()
{
    return _endpoints.at(0)._endpoint;
}

boost::asio::io_service &MyNetwork::getIOService() 
{
    return _io_services;
}

Protocol &MyNetwork::getProtocol() 
{
    return _protocol;
}

std::vector<EndpointInformation> &MyNetwork::getEndpoints()
{
    return _endpoints;
}

void MyNetwork::UDPReceiveClient(std::function<void(char *)> func, bool shouldCallback) 
{
    std::memset(_recvBuffer, '\0', 1024);
    boost::asio::ip::udp::endpoint endpoint;
    _shouldCallback = shouldCallback;
    _socket.async_receive_from(boost::asio::buffer(_recvBuffer), endpoint,
    [this, func] (boost::system::error_code ec, std::size_t recvd_bytes) {
        if (ec || recvd_bytes <= 0 && _shouldCallback)
            UDPReceiveClient(func, _shouldCallback);
        func(_recvBuffer);
        if (_shouldCallback)
            UDPReceiveClient(func, _shouldCallback);
    });
};

void MyNetwork::UDPReceiveServer(std::function<void(char *)> func) 
{
    std::memset(_recvBuffer, '\0', 1024);
    boost::asio::ip::udp::endpoint endpoint;
    _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _endpoint,
    [this, func] (boost::system::error_code ec, std::size_t recvd_bytes) {
        if (ec || recvd_bytes <= 0)
            UDPReceiveServer(func);
        if (isNewEndpoint(_endpoint)) 
            addEndpoint(_endpoint);
        func(_recvBuffer);
        UDPReceiveServer(func);
    });
};

void MyNetwork::kickPlayer(boost::asio::ip::udp::endpoint endpoint, bool isBan)
{
    for (int i = 0; i < _endpoints.size(); i++) {
        if (endpoint == _endpoints.at(i)._endpoint) {
            _endpoints.erase(_endpoints.begin() + i);
            if (isBan) {
                _endpointsBannedPlayer.emplace_back(endpoint);
            }
        }
    }
}

void MyNetwork::kickPlayer(const std::string &endpoint, bool isBan)
{
    for (int i = 0; i < _endpoints.size(); i++) {
        if (endpoint == _endpoints.at(i)._endpoint.address().to_string()) {
            if (isBan) {
                _endpointsBannedPlayer.push_back(_endpoints.at(i)._endpoint);
            }
            _endpoints.erase(_endpoints.begin() + i);
        }
    }
}

bool MyNetwork::isLobbyFull()
{
    if (getEndpoints().size() == 4)
        return true;
    return false;
}

bool MyNetwork::isClientAccepted()
{
    return _isClientAccepted;
}

void MyNetwork::udpSendToAllClients(char *buffer, std::size_t const& sizeOfBuffer)
{
    for (int i = 0; i < _endpoints.size(); i++) {
        _socket.async_send_to(boost::asio::buffer(buffer, 1024), _endpoints.at(i)._endpoint,
            [this](boost::system::error_code ec, std::size_t bytes_sent) 
        {
        });
    } 
}

void MyNetwork::udpSend(char *buffer, const std::size_t &sizeOfBuffer, boost::asio::ip::udp::endpoint endpoint)
{
    _socket.async_send_to(boost::asio::buffer(buffer, sizeOfBuffer), endpoint,
        [this, buffer, endpoint](boost::system::error_code ec, std::size_t bytes_sent) 
    {
    });
}
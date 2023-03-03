/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** MyNetwork
*/

#include "MyNetwork.hpp"
#include "NewPlayer.hpp"
#include "Protocol.hpp"

// client
MyNetwork::MyNetwork(boost::asio::io_service &io_service, const std::string& host, const std::string& port) : 
    _io_services(io_service),
    _socket(io_service, boost::asio::ip::udp::v4())
{
    boost::asio::ip::udp::endpoint serverEndpoint(boost::asio::ip::address::from_string(host), std::stoi(port));
    _endpoints.emplace_back(EndpointInformation{serverEndpoint, false});
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
    for (size_t i = 0; i < _endpoints.size(); i++) {
        if (endpoint == _endpoints.at(i)._endpoint) {
            std::cerr << "User already connected : " << endpoint << std::endl;
            return false;
        }
    }
    std::cerr << "New user:" << endpoint << "connected"  << std::endl;
    return true;    
}

void MyNetwork::addEndpoint(boost::asio::ip::udp::endpoint endpoint, const bool& status)
{
    _endpoints.emplace_back(EndpointInformation{endpoint, status});
}

boost::asio::ip::udp::endpoint MyNetwork::getServerEndpoint()
{
    return _endpoints.at(0)._endpoint;
}

boost::asio::io_service &MyNetwork::getIOService() 
{
    return _io_services;
}

std::vector<EndpointInformation> &MyNetwork::getEndpoints()
{
    return _endpoints;
}

void MyNetwork::UDPReceiveClient(std::function<void(char *)> func, bool shouldCallback) 
{
    std::memset(_recvBuffer, '\0', 1024);
    _shouldCallback = shouldCallback;
    _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _receiverEndpoint,
    [this, func] (boost::system::error_code ec, std::size_t recvd_bytes) {
        if (ec || recvd_bytes <= 0 && _shouldCallback)
            UDPReceiveClient(func, _shouldCallback);
        func(_recvBuffer);
        if (_shouldCallback)
            UDPReceiveClient(func, _shouldCallback);
    });
};

void MyNetwork::UDPReceiveServer(std::function<void(char *, int)> func) 
{
    std::memset(_recvBuffer, '\0', 1024);
    _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _endpoint,
    [this, func] (boost::system::error_code ec, std::size_t recvd_bytes) {
        if (!ec)
        {
            if (ec || recvd_bytes <= 0)
                UDPReceiveServer(func);
            manageMessageReceive(_recvBuffer, _endpoint, func);
            UDPReceiveServer(func);
        }
    });
};

bool MyNetwork::isLobbyFull()
{
    if (getEndpoints().size() == 4)
        return true;
    return false;
}

void MyNetwork::manageMessageReceive(char *message, boost::asio::ip::udp::endpoint endpointSender, std::function<void(char *)> func)
{
    Header* ptr1 = reinterpret_cast<Header*>(message);
    std::cout << "Receive header == " << ptr1->_id << std::endl;
    if (ptr1->_id == 1) {
        if (getEndpoints().size() > 3)
            return;
        if (isNewEndpoint(endpointSender))
            addEndpoint(endpointSender, true);
    }
    func(message);
}

void MyNetwork::checkRequestOfConnection(char* buffer, boost::asio::ip::udp::endpoint endpoint, int lenghtValue)
{
    NewPlayer* ptr1 = reinterpret_cast<NewPlayer*>(buffer + lenghtValue);
}

void MyNetwork::sendConnectionStatus(const ConnectionStatus &coStatus)
{
    char buffer[1024];
    std::memcpy(buffer, serialiseData<Header>(Header{1}), sizeof(Header));
    std::memcpy(buffer + sizeof(Header), serialiseData<ConnectionStatus>(coStatus), sizeof(ConnectionStatus));
    udpSendToAllClients(buffer, sizeof(buffer));
}

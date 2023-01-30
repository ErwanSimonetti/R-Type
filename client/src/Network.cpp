/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network
*/

#include "Network.hpp"

Network::Network(boost::asio::io_service &io_service, const std::string& host, const std::string& port) : 
    _socket(io_service, boost::asio::ip::udp::v4())
{
    boost::asio::ip::udp::endpoint serverEndpoint(boost::asio::ip::address::from_string(host), std::stoi(port));
    addEndpoint(serverEndpoint);
}

Network::Network(boost::asio::io_service& io_service, const std::string &port)
    : _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 1234))
{

}

Network::~Network()
{
}

void Network::addEndpoint(boost::asio::ip::udp::endpoint endpoint)
{
    if ((std::find(_endpoints.begin(), _endpoints.end(), endpoint) != _endpoints.end())) {
        std::cerr << "User: " << endpoint << "\n";
    } else {
        std::cerr << "New user:" << endpoint << "connected\n";
        _endpoints.emplace_back(endpoint);
    }
}
    
// void Network::UDPReceive(std::function<void()> func, bool isServer)
// {
//     std::memset(_recvBuffer, '\0', 1024);
//     boost::asio::ip::udp::endpoint endpoint;

//     _socket.async_receive_from(boost::asio::buffer(_recvBuffer), endpoint,
//     [this, func, isServer] (boost::system::error_code ec, std::size_t recvd_bytes) {
//         if (ec || recvd_bytes >= 0)
//             UDPReceive(func, isServer);
//         if (isServer)
//             ClientData data = _protocol.readClient(_recvBuffer);
//         else
//             ServerData data =  _protocol.readServer(_recvBuffer);
//         func();
//     });
// }
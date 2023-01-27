/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Network
*/

#include "../include/Network.hpp"

Network::Network(boost::asio::io_service& io_service)
    : _socket(io_service, boost::asio::ip::udp::v4())
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

template <typename Data>
void Network::udpSend(char *buffer, boost::asio::ip::udp::endpoint endpoint)
{
    _socket.async_send_to(boost::asio::buffer(buffer, sizeof(Data)), endpoint,
        [this, buffer, endpoint](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/) 
    {
        std::cerr << "Succefully sent: " << buffer << " to:" << endpoint << "\n";
    });
}
    
void Network::udpReceive()
{
    std::memset(_recvBuffer, '\0', 1024);
    boost::asio::ip::udp::endpoint endpoint;

    _socket.async_receive_from(boost::asio::buffer(_recvBuffer), endpoint,
    [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
        if ( !ec && recvd_bytes > 0 ) {

        }
        else {
            udpReceive();
        }
    });
}

int main ()
{
    printf("jaj\n");
}
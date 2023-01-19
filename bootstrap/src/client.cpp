/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** juju
*/

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>

class UDPClient
{
public:
    UDPClient(boost::asio::io_service& io_service, const std::string& host, const std::string& port)
        : socket_(io_service, boost::asio::ip::udp::v4()),
          endpoint_(boost::asio::ip::address::from_string(host), std::stoi(port))
    {
    }

    void send(const std::string& message)
    {
        std::cout << message;
        socket_.async_send_to(boost::asio::buffer(message), endpoint_,
            [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/) {
            });
    }

    void receive()
    {
        std::memset(recv_buf_, '\0', 500);
        socket_.async_receive_from(boost::asio::buffer(recv_buf_), endpoint_, [this] (boost::system::error_code ec, std::size_t bytes_sent) {
            if (!ec && bytes_sent > 0) {     
                std::cerr << recv_buf_ << std::endl;
                receive();
            }
        });
        // return std::string(recv_buf, bytes_recvd);
    }

private:
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint endpoint_;
    char recv_buf_[500];
};

int main()
{
    boost::asio::io_service io_service;
    UDPClient client(io_service, "127.0.0.1", "1234");
    // client.receive();
    client.receive();
    client.send("Hello");
    io_service.run();
    // std::cout << "received: " << client.receive() << std::endl;
    return 0;
}
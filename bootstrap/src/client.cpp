/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** juju
*/

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>

struct jaj {
  int a;
  float b;
  char c[20];
};

class UDPClient
{
public:
    UDPClient(boost::asio::io_service& io_service, const std::string& host, const std::string& port)
        : socket_(io_service, boost::asio::ip::udp::v4()),
          endpoint_(boost::asio::ip::address::from_string(host), std::stoi(port))
    {
    }

    void send(char *buffer)
    {
        std::cout << buffer;
        socket_.async_send_to(boost::asio::buffer(buffer, sizeof(jaj)), endpoint_,
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
    printf("CLient on\n");
    // client.receive();
    jaj joj;
    joj.a = 1;
    joj.b = 6;
    strcpy(joj.c, "you massive fuck");
    char buffer[sizeof(jaj)];
    memcpy(buffer, &joj, sizeof(jaj));

    jaj jij;

    // memcpy(&jij, buffer, sizeof(jaj));
    client.receive();
    client.send(buffer);
    io_service.run();
    // std::cout << "received: " << client.receive() << std::endl;
    return 0;
}
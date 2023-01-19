/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** client
*/

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <iostream>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/array.hpp>

using boost::asio::ip::udp;

class UDPClient {
public:
    UDPClient(boost::asio::io_context& io_context, 
              const std::string& host, const std::string& port)
        : socket_(io_context),
          endpoint_(boost::asio::ip::make_address(host), 
                    std::atoi(port.c_str())) {
        start_receive();
    }

    void send(const std::string& message) {
        socket_.send_to(boost::asio::buffer(message), endpoint_);
    }

private:
    void start_receive() {
        socket_.async_receive_from(
            boost::asio::buffer(recv_buffer_), remote_endpoint_,
            [this](boost::system::error_code ec, std::size_t bytes_recvd) {
                if (!ec && bytes_recvd > 0) {
                    // process the incoming data
                    std::cout << "Received " << bytes_recvd << " bytes from "
                              << remote_endpoint_ << std::endl;
                }
                start_receive();
            });
    }

    udp::socket socket_;
    udp::endpoint endpoint_;
    udp::endpoint remote_endpoint_;
    std::array<char, 1> recv_buffer_;
};

int main(int argc, char **argv) {
    try {
        printf("joj\n");
        boost::asio::io_context io_context;
        UDPClient client(io_context, "localhost", "1234");
        printf("juj\n");

        while (true) {
            std::string message;
            std::getline(std::cin, message);
            client.send(message);
        }
    } catch (std::exception& e) {
        printf("jaj\n");
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
// int main(int argc, char **argv)
// {
//     int sockfd;
//     if (argc != 3) {
//         std::cout << "Usage udp_client port + message";
//         return 0;
//     }

//     char bufferSend[256];
//     char bufferRecv[256];
//     memset(bufferSend, '\0', sizeof(bufferSend) + 1);
//     memset(bufferRecv, '\0', sizeof(bufferRecv) + 1);
//     memcpy(bufferSend, argv[2], strlen(argv[2]));

//     if ((sockfd == socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
//         std::cout << "cannot create";
//         return 0;
//     }

//     struct sockaddr_in servAddr;
//     struct sockaddr_in  cliAddr;
//     socklen_t cLen = sizeof(cliAddr);
//     socklen_t sLen = sizeof(servAddr);
//     servAddr.sin_family = AF_INET;
//     servAddr.sin_port = htons(std::stoi(argv[1]));
//     servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
//     ssize_t sByte = sendto(sockfd, bufferSend, sizeof(bufferSend), 0, (struct sockaddr *)&servAddr, sLen);
//     // boost::asio::write( socket, boost::asio::buffer(msg), error );
//     std::cout << "[" << sByte << "] Bytes Sent : " << std::endl;

//     ssize_t rByte = recvfrom(sockfd,bufferRecv,sizeof(bufferRecv),0,(struct sockaddr *)&cliAddr, &cLen);
//     std::cout << "[" << sByte << "] Bytes receive : " << std::endl;

//     close(sockfd);
// }

// int main(int argc, char **argv) {
//     boost::asio::io_context io_context;

//     boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::udp::v4(), std::stoi(argv[1]));
//     boost::asio::ip::udp::socket socket(io_context);
//     socket.open(boost::asio::ip::udp::v4());

//     std::string message = "Hello, Server!";
//     char ok[300];
//     socket.send_to(boost::asio::buffer(message), endpoint);
//     // socket.send_to(boost::asio::buffer(message), endpoint);

//     // boost::asio::streambuf receive_buffer;
//     char letter[200];
//     std::memset(letter, '\0', sizeof(letter) + 1);
//     socket.receive_from(boost::asio::buffer(&letter, 200), endpoint);

//     std::cout << letter;

    // boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
    // if( error && error != boost::asio::error::eof ) {
    //     cout << "receive failed: " << error.message() << endl;
    // }
    // else {
    //     const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
    //     cout << data << endl;
    // }
    // return 0;
// }
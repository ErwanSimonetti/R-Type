/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** asio
*/

#include <iostream>
#include <boost/asio.hpp>
// #include <asio.hpp>
#include <iostream>
#include <boost/array.hpp>

using boost::asio::ip::udp;

class myUdpServer
{
public:
  myUdpServer(boost::asio::io_service& io_service, short port)
    : socket_(io_service, udp::endpoint(udp::v4(), port))
  {
    my_udp_receive();
  }

  void my_udp_receive()
  {
      // do asyn receiving  to buffer data_
      // [ captures ] ( params ) { body }
      std::memset(data_, '\0', 1024);

      socket_.async_receive_from(boost::asio::buffer(data_), sender_endpoint_,
      [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
          if ( !ec && recvd_bytes > 0 ) {
            std::cout << "[" << recvd_bytes << "] " << data_ << std::endl;
            my_udp_send_back();
          }
          else {
            my_udp_receive();
          }
      });
  }

  void my_udp_send_back()
  {
      // do add sender information and send back
      std::cerr << "send back" << std::endl;
      std::string myStr = " Sender endpoint : ";
      myStr += sender_endpoint_.address().to_string().c_str();
      myStr += " port ";
      myStr += std::to_string((int)sender_endpoint_.port());
      myStr += " Message : ";
      myStr += data_;
      socket_.async_send_to(boost::asio::buffer(myStr.c_str(), myStr.length()), sender_endpoint_,
      [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
          my_udp_receive();
      });
  }

private:
  udp::socket socket_;
  udp::endpoint sender_endpoint_;
  enum { max_length = 1024};
  char data_[max_length];
  // boost::array <char, 128> data_;
};

int main(int argc, char **argv) {
      try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_service io_service;
    myUdpServer mySer(io_service, std::atoi(argv[1]));
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
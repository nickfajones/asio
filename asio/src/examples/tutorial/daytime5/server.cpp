#include <ctime>
#include <iostream>
#include <string>
#include "asio.hpp"

int main()
{
  try
  {
    asio::demuxer demuxer;

    asio::dgram_socket socket(demuxer, asio::ipv4::address(13));

    for (;;)
    {
      char recv_buf[1];
      asio::ipv4::address remote_address;
      socket.recvfrom(recv_buf, sizeof(recv_buf), remote_address,
          asio::throw_error_if(
            asio::error != asio::socket_error::message_size));

      using namespace std; // For time_t, time and ctime.
      time_t now = time(0);
      std::string msg = ctime(&now);

      socket.sendto(msg.c_str(), msg.length(), remote_address,
          asio::ignore_error());
    }
  }
  catch (asio::socket_error& e)
  {
    std::cerr << e.what() << ": " << e.message() << std::endl;
  }

  return 0;
}
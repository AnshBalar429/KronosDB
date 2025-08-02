#include "Server.h"
#include <iostream>

Server::Server(unsigned short port)
    : acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
    std::cout << "Server will listen on port " << port << std::endl;
}

void Server::run() {
    std::cout << "Server is starting..." << std::endl;
    io_context_.run();
}

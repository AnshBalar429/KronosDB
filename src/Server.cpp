#include "Server.h"
#include <iostream>
#include "Session.h"

Server::Server(unsigned short port, std::shared_ptr<KeyValueStore>& store)
    : acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) ,
      store_(store) {
    std::cout << "Server will listen on port " << port << std::endl;
}

void Server::run() {
    std::cout << "Server is starting..." << std::endl;
    do_accept();
    io_context_.run();
}


void Server::do_accept() {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket), store_)->start();
            } else {
                std::cerr << "Accept Error : " << ec.message() << std::endl;
            }
            do_accept();
        }
    );
}

#include "Session.h"
#include <iostream>
#include <istream>
#include <ostream>

Session::Session(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket)) {}

void Session::start() {
    std::cout << "New session started from" << socket_.remote_endpoint() << std::endl;
    do_read();
}

void Session::do_read() {
    auto self(shared_from_this());

    boost::asio::async_read_until(socket_,buffer_,'\n',
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                do_write(length);
            } else if (ec == boost::asio::error::eof) {
                std::cout << "Session end by peer." << std::endl;
            } else {
                std::cerr << "Session Error : " << ec.message() << std::endl;
            }
        });
}

void Session::do_write(std::size_t length) {
    auto self(shared_from_this());

    boost::asio::async_write(socket_, buffer_.data(),
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
            if (!ec) {
                // Data has been written, now wait for the next message.
                buffer_.consume(buffer_.size()); // Clear the buffer
                do_read();
            } else {
                std::cerr << "Write Error: " << ec.message() << std::endl;
            }
        });
}


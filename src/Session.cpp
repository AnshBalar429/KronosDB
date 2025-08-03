#include "Session.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <utility>

Session::Session(boost::asio::ip::tcp::socket socket, std::shared_ptr<KeyValueStore> store)
    : socket_(std::move(socket)) , store_(std::move(store)) {}

void Session::start() {
    std::cout << "New session started from" << socket_.remote_endpoint() << std::endl;
    do_read();
}

std::string Session::process_command(const std::string& line) {
    std::stringstream ss(line);
    std::string command;
    ss >> command;

    if (command == "GET") {
        std::string key;
        ss >> key;
        if (key.empty()) {
            return "ERROR : Key not specified\n";
        }

        const auto value = store_->get(key);

        return value.has_value() ? *value + "\n" : "(nil)\n";

    } else if (command == "SET") {
        std::string key, value;
        ss >> key;

        // The rest of the line will be the value
        std::getline(ss, value);

        if (!value.empty() && value[0] == ' ') {
            value.erase(0, 1);
        }

        if (key.empty() || value.empty()) {
            return "ERROR : SET requires a key and value\n";
        }

        store_->set(key, value);
        return "OK\n";

    } else if (command == "DEL") {
        std::string key;
        ss >> key;
        if (key.empty()) return "ERROR: Key not specified\n";

        store_->del(key);
        return "DELETED\n";
    }

    return "ERROR: Unknown command '" + command + "'\n";
}


void Session::do_read() {
    auto self(shared_from_this());

    boost::asio::async_read_until(socket_,buffer_,'\n',
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::istream is(&buffer_);
                std::string line;
                std::getline(is, line);

                std::string response = process_command(line);

                do_write(response);

            } else if (ec == boost::asio::error::eof) {
                std::cout << "Session end by peer." << std::endl;
            } else {
                std::cerr << "Session Error : " << ec.message() << std::endl;
            }
        });
}

void Session::do_write(const std::string& response) {
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


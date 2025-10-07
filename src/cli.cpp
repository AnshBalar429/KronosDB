#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
    try {
        // hardcoding the server address
        const char* host = "127.0.0.1";
        const char* port = "12345";

        boost::asio::io_context io_context;

        // finding the endpoints to connect
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(host, port);

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::cout << "Connected to KronosDB at " << host << ":" << port << std::endl;
        std::cout << "Type 'exit' or 'quit' to close." << std::endl;

    }catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}
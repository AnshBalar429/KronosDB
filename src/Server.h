#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>

class Server {
public:
    Server(unsigned short port);

    void run();

private:
    // Starts an asynchronous accept operation.
    void do_accept();

    boost::asio::io_context io_context_;

    boost::asio::ip::tcp::acceptor acceptor_;
};

#endif // SERVER_H

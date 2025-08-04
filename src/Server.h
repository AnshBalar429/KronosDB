#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>

#include "KeyValueStore.h"

class Server {
public:
    Server(unsigned short port, std::shared_ptr<KeyValueStore>& store);

    void run();

private:
    // Starts an asynchronous accept operation.
    void do_accept();

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::shared_ptr<KeyValueStore> store_;
};

#endif // SERVER_H

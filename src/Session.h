#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>
#include <memory>

#include "KeyValueStore.h"

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(boost::asio::ip::tcp::socket socket, std::shared_ptr<KeyValueStore> store);

    void start();

private:
    void do_read();
    void do_write(const std::string& response);

    std::string process_command(const std::string& line);

    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf buffer_;
    std::shared_ptr<KeyValueStore> store_;
};


#endif // SESSION_H

#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <fstream>
#include <string>
#include <mutex>

class Persistence {
public:
    Persistence(const std::string& filename);

    void log_command(const std::string& command);

private:
    std::ofstream aof_file_;
    std::mutex mtx_;
};


#endif // PERSISTENCE_H
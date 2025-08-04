#include "Persistence.h"
#include <stdexcept>

Persistence::Persistence(const std::string& filename) {
    aof_file_.open(filename, std::ios::app);
    if (!aof_file_.is_open()) {
        throw std::runtime_error("Failed to open AOF file: " + filename);
    }
}

void Persistence::log_command(const std::string& command) {
    std::lock_guard<std::mutex> lock(mtx_);
    aof_file_ << command << std::endl;
}

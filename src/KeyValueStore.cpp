#include "KeyValueStore.h"
#include <iostream>
#include <fstream>
#include <sstream>

void KeyValueStore::load_from_aof(const std::string& filename) {
    std::ifstream aof_file(filename);
    if (!aof_file.is_open()) {
        std::cout << "AOF file not found. Starting with an empty store." << std::endl;
        return;
    }

    std::cout << "Loading data from AOF file: " << filename << std::endl;
    std::string line;
    while (std::getline(aof_file, line)) {
        std::stringstream ss(line);
        std::string command, key, value;
        ss >> command;
        if (command == "SET") {
            ss >> key;
            std::getline(ss, value);
            if (!value.empty() && value[0] == ' ') value.erase(0, 1);
            set(key, value);
        } else if (command == "DEL") {
            ss >> key;
            del(key);
        }
    }
    std::cout << "AOF loading complete." << std::endl;
}


std::shared_mutex& KeyValueStore::get_lock_for_key(const std::string& key) const {
    const auto index = std::hash<std::string >{}(key) % NUM_LOCKS;
    // std::cout << index << '\n';
    return locks_[index];
}



KeyValueStore::KeyValueStore(const std::string& aof_filename) : locks_(NUM_LOCKS) {
    // Load data from the file first. During this phase, persistence_ is null,
    // so the set/del calls inside load_from_aof won't write back to the file
    load_from_aof(aof_filename);

    persistence_ = std::make_unique<Persistence>(aof_filename);
    std::cout << "Persistence enabled. Logging to " << aof_filename << std::endl;

}


void KeyValueStore::set(const std::string& key, const std::string& value) {
    // acquire the lock
    // std::unique_lock<std::shared_mutex> lock(mtx);

    std::unique_lock<std::shared_mutex> lock(get_lock_for_key(key));


    // if key exists it reassigns or insert
    data_map.insert_or_assign(key, value);

    std::cout << "SET: " << key << " = " << value << std::endl;

    if (persistence_) {
        persistence_->log_command("SET " + key + " " + value);
    }
}

std::optional<std::string> KeyValueStore::get(const std::string& key) const {
    // std::shared_lock<std::shared_mutex> lock(mtx);
    std::unique_lock<std::shared_mutex> lock(get_lock_for_key(key));
    auto it = data_map.find(key);

    if (it != data_map.end()) {
        std::cout << "GET: " << key << " -> " << it->second << std::endl;
        return it->second;
    } else {
        std::cout << "GET: " << key << " -> (not found)" << std::endl;
        return std::nullopt; // empty optional
    }
}

void KeyValueStore::del(const std::string& key) {
    // std::unique_lock<std::shared_mutex> lock(mtx);
    std::unique_lock<std::shared_mutex> lock(get_lock_for_key(key));

    data_map.erase(key);
    std::cout << "DELETE: " << key << std::endl;

    if (persistence_) {
        persistence_->log_command("DEL " + key);
    }
}

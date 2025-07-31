#include "KeyValueStore.h"
#include <iostream>

KeyValueStore::KeyValueStore() = default;

void KeyValueStore::set(const std::string& key, const std::string& value) {
    // if key exists it reassigns or insert
    data_map.insert_or_assign(key, value);
    std::cout << "SET: " << key << " = " << value << std::endl;
}

std::optional<std::string> KeyValueStore::get(const std::string& key) {
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
    data_map.erase(key);
    std::cout << "DELETE: " << key << std::endl;
}

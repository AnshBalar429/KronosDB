#ifndef KEY_VALUE_STORE_H
#define KEY_VALUE_STORE_H
#include <string>
#include <unordered_map>

class KeyValueStore {
private:
    // The main underlying data structure to store the key-value pair
    std::unordered_map<std::string, std::string> data_map;

public:
    KeyValueStore();
};

#endif // KEY_VALUE_STORE_H

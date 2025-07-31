#ifndef KEY_VALUE_STORE_H
#define KEY_VALUE_STORE_H
#include <string>
#include <unordered_map>
#include <optional>

class KeyValueStore {
private:
    // The main underlying data structure to store the key-value pair
    std::unordered_map<std::string, std::string> data_map;

public:
    KeyValueStore();

    void set(const std::string& key, const std::string& value);

    std::optional<std::string> get(const std::string& key);

    void del(const std::string& key);
};

#endif // KEY_VALUE_STORE_H

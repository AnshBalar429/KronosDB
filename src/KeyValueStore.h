#ifndef KEY_VALUE_STORE_H
#define KEY_VALUE_STORE_H
#include <string>
#include <unordered_map>
#include <optional>
#include <shared_mutex>
#include <memory>

#include "Persistence.h"

class KeyValueStore {
private:
    // The main underlying data structure to store the key-value pair
    std::unordered_map<std::string, std::string> data_map;

    mutable std::shared_mutex mtx;
    // while using locks in a function the state of lock changes so we can not use locks
    // in a const function because the data can not be changed in const functions.
    // so we should make mutex mutable so it can be used inside const function.
    // Here const function is KeyValueStore::get()

    std::unique_ptr<Persistence> persistence_;

    void load_from_aof(const std::string& filename);

public:
    KeyValueStore(const std::string& aof_filename);

    void set(const std::string& key, const std::string& value);

    std::optional<std::string> get(const std::string& key) const;

    void del(const std::string& key);
};

#endif // KEY_VALUE_STORE_H

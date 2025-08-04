#include <iostream>
#include <memory>
#include "Server.h"
#include "KeyValueStore.h"

int main() {
    try {
        // The single, shared KeyValueStore instance.
        auto store = std::make_shared<KeyValueStore>("store.aof");

        Server s(12345, store);
        s.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}

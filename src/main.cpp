#include <iostream>
#include "KeyValueStore.h"

int main() {
    std::cout << "--- Single-Threaded Key-Value Store Test ---" << std::endl;

    KeyValueStore store;

    store.set("apple", "red");
    store.set("banana", "yellow");

    store.get("apple");
    store.get("banana");

    store.set("apple", "green");
    store.get("apple");

    store.get("grape");

    store.del("banana");
    store.get("banana");

    std::cout << "\n--- Test Complete ---" << std::endl;

    return 0;
}

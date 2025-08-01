#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <memory>
#include <string>

#include "KeyValueStore.h"


void writer_task(std::shared_ptr<KeyValueStore> store, int client_id) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> key_dist(1, 10); // Keys will be "key1", "key2", ...
    std::uniform_int_distribution<> op_dist(0, 1); // 0 for SET, 1 for DELETE

    for (int i = 0; i < 20; ++i) {
        std::string key = "key" + std::to_string(key_dist(gen));

        if (op_dist(gen) == 0) {
            // Perform a SET operation
            std::string value = "value_from_" + std::to_string(client_id);
            store->set(key, value);
        } else {
            // Perform a DELETE operation

            store->del(key);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}


void reader_task(std::shared_ptr<KeyValueStore> store, int client_id) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> key_dist(1, 10);

    for (int i = 0; i < 50; ++i) {
        std::string key = "key" + std::to_string(key_dist(gen));

        store->get(key);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}


int main() {
    // stress test
    const int NUM_WRITERS = 10;
    const int NUM_READERS = 50;

    auto store = std::make_shared<KeyValueStore>();

    std::vector<std::thread> threads;

    std::cout << "--- Starting Simulation ---" << std::endl;
    std::cout << "Launching " << NUM_WRITERS << " writers and " << NUM_READERS << " readers." << std::endl;

    for (int i = 0; i < NUM_WRITERS; ++i) {
        threads.emplace_back(writer_task, store, i);
    }

    for (int i = 0; i < NUM_READERS; ++i) {
        threads.emplace_back(reader_task, store, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "\n--- Simulation Finished ---" << std::endl;

    // Consistency Check
    int NUM_KEY = 10;
    for (int i = 1; i <= NUM_KEY; i++) {
        std::string key = "key" + std::to_string(i);
        store->get(key);
    }

    return 0;
}

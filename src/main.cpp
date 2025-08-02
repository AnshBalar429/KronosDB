#include <iostream>
#include "Server.h"

int main() {
    try {
        Server s(12345);
        s.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
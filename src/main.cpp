#include "state.hpp"

#include <exception>
#include <iostream>

int main() {
    try {
        state_t state;
        state.run();
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}

#include "../include/random.hpp"
#include <cstdint>
#include <iostream>
#include <iterator>
#include <string>

char uniform_char_distribution(uint32_t rn) {
    static const std::string chars = "ABCDEFGHIJKLMNOPQESTUVWXYZ"
                                     "abcdefghijklmnopqrstuvwxyz"
                                     "1234567890"
                                     "!@#$%^&*()";

    return chars[rn % std::size(chars)];
}

int main() {
    Random &rng = thread_local_random();

    std::cout << "10 random passwords:\n";
    for (int p = 0; p < 10; p++) {
        std::string password = "";
        uint32_t length = rng.uniform_int(12, 24);

        for (uint32_t i = 0; i < length; ++i) {
            password += uniform_char_distribution(rng.rand32());
        }
        std::cout << " " << password << "\n";
    }

    return 0;
}
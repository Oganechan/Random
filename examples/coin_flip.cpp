#include "../include/random.hpp"
#include <cstdint>
#include <iostream>

constexpr uint32_t N = 1e6;

int main() {
    Random &rng = thread_local_random();

    uint32_t heads = 0;
    for (uint32_t i = 0; i < N; ++i)
        if (rng.bernoulli(0.5))
            heads++;

    double prob = 100.0 * heads / N;
    std::cout << "Heads: " << prob << "%\n";
    std::cout << "Tails: " << 100.0 - prob << "%\n";

    return 0;
}
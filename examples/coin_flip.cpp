#include "../include/random.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>

constexpr uint32_t N = 1e9;

int main()
{
    Random rng;

     auto start_time = std::chrono::high_resolution_clock::now();

    uint32_t heads = 0;
    for (uint32_t i = 0; i < N; ++i)
        if (rng.bernoulli(0.5))
            heads++;

    auto end_time = std::chrono::high_resolution_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);

    double prob = 100.0 * heads / N;
    std::cout << "Heads: " << prob << "%\n";
    std::cout << "Tails: " << 100.0 - prob << "%\n";

    std::cout << "Total time: " << total_duration.count() << " milliseconds\n";

    return 0;
}
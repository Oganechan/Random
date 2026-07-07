#include "../include/random.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>

constexpr uint32_t N = 1e9;
constexpr uint32_t DOORS = 3;

int main()
{
    Random rng;

    uint32_t stay_and_win = 0;
    uint32_t switch_and_win = 0;

    auto start_time = std::chrono::high_resolution_clock::now();

    for (uint32_t i = 0; i < N; ++i)
    {
        uint32_t car = rng.uniform_int<uint32_t>(0, DOORS - 1);
        uint32_t player = rng.uniform_int<uint32_t>(0, DOORS - 1);

        car == player ? stay_and_win++ : switch_and_win++;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);

    std::cout << "Winnings without change: " << 100.0 * stay_and_win / N
              << "%\n";
    std::cout << "Winnings when changing choices: "
              << 100.0 * switch_and_win / N << "%\n";

    std::cout << "Total time: " << total_duration.count() << " milliseconds\n";

    return 0;
}
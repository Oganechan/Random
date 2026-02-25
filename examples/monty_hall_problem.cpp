#include "../include/random.hpp"
#include <cstdint>
#include <iostream>

constexpr uint32_t N = 1e6;
constexpr uint32_t DOORS = 3;

int main() {
    Random &rng = thread_local_random();

    uint32_t stay_and_win = 0;
    uint32_t switch_and_win = 0;

    for (uint32_t i = 0; i < N; ++i) {
        uint32_t car = rng.uniform_int<uint32_t>(0, DOORS - 1);
        uint32_t player = rng.uniform_int<uint32_t>(0, DOORS - 1);

        car == player ? stay_and_win++ : switch_and_win++;
    }

    std::cout << "Winnings without change: " << 100.0 * stay_and_win / N
              << "%\n";
    std::cout << "Winnings when changing choices: "
              << 100.0 * switch_and_win / N << "%\n";

    return 0;
}
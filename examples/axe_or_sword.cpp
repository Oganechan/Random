#include "../include/random.hpp"
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <vector>

constexpr uint32_t N = 1e6;
constexpr bool TRAIT = false;

inline uint32_t sword_roll(Random &rng) {
    return rng.uniform_int(1, 6) + rng.uniform_int(1, 6);
}
inline uint32_t axe_roll(Random &rng) { return rng.uniform_int(1, 12); }

void print_histogram(const std::vector<uint32_t> &hist,
                     std::string label = "") {
    int32_t max_bar = 25;
    int32_t max_count = 0;

    if (label != "") {
        std::cout << label << "\n";
    }

    for (int32_t count : hist)
        if (count >= max_count)
            max_count = count;

    for (uint32_t i = 1; i < hist.size(); ++i) {
        int32_t bar_length =
            static_cast<int>((hist[i] * 1.0 / max_count) * max_bar);
        std::string bar(bar_length, '#');
        double percentage = 100.0 * hist[i] / N;

        std::cout << std::setw(4) << i << ": " << bar << " (" << percentage
                  << "%)\n";
    }
}

int main() {
    Random &rng = thread_local_random();

    std::vector<uint32_t> sword_results, sword_hist(13, 0);
    std::vector<uint32_t> axe_results, axe_hist(13, 0);

    for (uint32_t i = 0; i < N; ++i) {
        uint32_t sword = sword_roll(rng);
        uint32_t axe = axe_roll(rng);

        if (TRAIT) { // if uses the Great Weapon Fighter trait
            (sword < 3) && (sword = sword_roll(rng));
            (axe < 3) && (axe = axe_roll(rng));
        }
        sword_results.push_back(sword);
        sword_hist[sword]++;
        axe_results.push_back(axe);
        axe_hist[axe]++;
    }

    double sword_mean = 0, axe_mean = 0;
    for (uint32_t i = 0; i < N; ++i) {
        sword_mean += sword_results[i];
        axe_mean += axe_results[i];
    }
    sword_mean /= N;
    axe_mean /= N;

    double sword_deviation = 0, axe_deviation = 0;
    for (uint32_t i = 0; i < N; ++i) {
        sword_deviation += std::abs(sword_results[i] - sword_mean);
        axe_deviation += std::abs(axe_results[i] - axe_mean);
    }
    sword_deviation /= N;
    axe_deviation /= N;

    print_histogram(sword_hist, "Sword (2d6):");
    std::cout << "mean: " << sword_mean << "\n"
              << "standard deviation: " << sword_deviation << "\n\n";

    print_histogram(axe_hist, "Axe (1d12):");
    std::cout << "mean: " << axe_mean << "\n"
              << "standard deviation: " << axe_deviation << "\n";

    return 0;
}
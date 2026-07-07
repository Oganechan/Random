#include "../include/random.hpp"
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>

constexpr uint32_t N = 1e9;

int main()
{
    Random rng;

    auto start_time = std::chrono::high_resolution_clock::now();

    uint32_t inside_circle = 0;
    for (uint32_t i = 0; i < N; ++i)
    {
        double x = rng.rand();
        double y = rng.rand();
        (x * x + y * y <= 1.0) && (inside_circle++);
    }
    double em_pi = 4.0 * inside_circle / N;

    auto end_time = std::chrono::high_resolution_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);

    std::cout << "Empirical π: " << em_pi << "\n"
              << "Accurate π: " << M_PI << "\n"
              << "Error: " << 100.0 * std::abs(M_PI - em_pi) / M_PI << "%\n";

    std::cout << "Total time: " << total_duration.count() << " milliseconds\n";

    return 0;
}
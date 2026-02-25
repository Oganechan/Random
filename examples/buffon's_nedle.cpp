#include "../include/random.hpp"
#include <cmath>
#include <cstdint>
#include <iostream>

constexpr uint32_t N = 1e6;

int main() {
    Random &rng = thread_local_random();

    uint32_t inside_circle = 0;
    for (uint32_t i = 0; i < N; ++i) {
        double x = rng.rand();
        double y = rng.rand();
        (x * x + y * y <= 1.0) && (inside_circle++);
    }
    double em_pi = 4.0 * inside_circle / N;

    std::cout << "Empirical π: " << em_pi << "\n"
              << "Accurate π: " << M_PI << "\n"
              << "Error: " << 100.0 * std::abs(M_PI - em_pi) / M_PI << "%\n";

    return 0;
}
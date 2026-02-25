#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdint>
#include <random>
#include <stdexcept>
#include <type_traits>

class Random {
  public:
    Random(const Random &) = delete;
    Random &operator=(const Random &) = delete;
    Random(Random &&) = default;
    Random &operator=(Random &&) = default;

    explicit Random() { reseed(); }
    explicit Random(uint32_t sd) : engine_(sd) {}

    void reseed() {
        std::random_device rd;
        engine_.seed(rd());
    }

    template <typename T> T uniform_int(T min, T max) {
        static_assert(std::is_integral_v<T>);
        std::uniform_int_distribution<T> dist(min, max);
        return dist(engine_);
    }

    uint32_t rand32() { return engine_(); }
    double rand() { return uniform_real(0.0, 1.0); }

    template <typename T> T uniform_real(T min, T max) {
        static_assert(std::is_floating_point_v<T>);
        std::uniform_real_distribution<T> dist(min, max);
        return dist(engine_);
    }

    bool bernoulli(double p = 0.5) {
        if (p < 0.0 || p > 1.0)
            throw std::out_of_range("");
        std::bernoulli_distribution dist(p);
        return dist(engine_);
    }

    std::mt19937 &engine() { return engine_; }

  private:
    std::mt19937 engine_;
};

inline Random &thread_local_random() {
    thread_local Random rng;
    return rng;
}

inline Random &thread_local_random(uint32_t sd) {
    thread_local Random rng(sd);
    return rng;
}

#endif // RANDOM_HPP
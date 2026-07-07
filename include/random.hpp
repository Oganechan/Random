#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdint>
#include <random>
#include <stdexcept>
#include <type_traits>
#include <tuple>

class Random
{
public:
    Random(const Random &) = delete;
    Random &operator=(const Random &) = delete;
    Random(Random &&) = default;
    Random &operator=(Random &&) = default;

    explicit Random() { random_reseed(); }
    explicit Random(uint32_t sd) { set_seed(sd); }

    void random_reseed()
    {
        std::random_device rd;
        seed_ = rd();
        engine_.seed(seed_);
    }

    void set_seed(uint32_t sd)
    {
        seed_ = sd;
        engine_.seed(seed_);
    }

    template <typename T>
    T uniform_int(const T min, const T max)
    {
        static_assert(std::is_integral_v<T> && !std::is_same_v<T, bool>,
                      "T must be non-boolean integral type");

        auto &dist = std::get<std::uniform_int_distribution<T>>(int_dists_);

        typename std::uniform_int_distribution<T>::param_type new_param(min, max);
        if (dist.param() != new_param)
            dist.param(new_param);

        return dist(engine_);
    }

    template <typename T>
    T uniform_real(const T min, const T max)
    {
        static_assert(std::is_floating_point_v<T>,
                      "T must be floating point type");

        auto &dist = std::get<std::uniform_real_distribution<T>>(real_dists_);

        typename std::uniform_real_distribution<T>::param_type new_param(min, max);
        if (dist.param() != new_param)
            dist.param(new_param);

        return dist(engine_);
    }

    template <typename T>
    T normal_distribution(const T mean, const T stddev)
    {
        static_assert(std::is_floating_point_v<T>,
                      "T must be floating point type");

        auto &dist = std::get<std::normal_distribution<T>>(normal_dists_);

        typename std::normal_distribution<T>::param_type new_param(mean, stddev);
        if (dist.param() != new_param)
            dist.param(new_param);

        return dist(engine_);
    }

    bool bernoulli(const double p = 0.5)
    {
        if (p < 0.0 || p > 1.0)
            throw std::out_of_range("p must be between 0 and 1");

        typename std::bernoulli_distribution::param_type new_param(p);
        if (bernoulli_dist_.param() != new_param)
            bernoulli_dist_.param(new_param);

        return bernoulli_dist_(engine_);
    }

    uint32_t rand32() { return engine_(); }
    double rand() { return uniform_real<double>(0.0, 1.0); }

    std::mt19937 &engine() { return engine_; }
    const std::mt19937 &engine() const { return engine_; }
    uint32_t seed() const { return seed_; }

private:
    std::mt19937 engine_;
    uint32_t seed_;

    std::tuple<
        std::uniform_int_distribution<int>,
        std::uniform_int_distribution<unsigned int>,
        std::uniform_int_distribution<long>,
        std::uniform_int_distribution<unsigned long>>
        int_dists_;

    std::tuple<
        std::uniform_real_distribution<float>,
        std::uniform_real_distribution<double>>
        real_dists_;

    std::tuple<
        std::normal_distribution<float>,
        std::normal_distribution<double>>
        normal_dists_;

    std::bernoulli_distribution bernoulli_dist_;
};

#endif // RANDOM_HPP

#include "../include/random.hpp"
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    Random rng;

    std::vector<std::string> deck = {
        "2♥", "3♥", "4♥", "5♥", "6♥", "7♥", "8♥", "9♥", "10♥", "В♥", "Д♥",
        "К♥", "Т♥", "2♦", "3♦", "4♦", "5♦", "6♦", "7♦", "8♦", "9♦", "10♦",
        "В♦", "Д♦", "К♦", "Т♦", "2♣", "3♣", "4♣", "5♣", "6♣", "7♣", "8♣",
        "9♣", "10♣", "В♣", "Д♣", "К♣", "Т♣", "2♠", "3♠", "4♠", "5♠", "6♠",
        "7♠", "8♠", "9♠", "10♠", "В♠", "Д♠", "К♠", "Т♠"};

    auto start_time = std::chrono::high_resolution_clock::now();

    std::shuffle(deck.begin(), deck.end(), rng.engine());

    auto end_time = std::chrono::high_resolution_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);

    uint32_t n = 1;
    std::cout << "Shuffled deck:\n";
    for (std::string card : deck)
        std::cout << card << (n++ % 13 == 0 ? "\n" : " ");

    std::cout << "Total time: " << total_duration.count() << " milliseconds\n";

    return 0;
}
#include "../include/random.hpp"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

int main() {
    Random &rng = thread_local_random();

    std::vector<std::string> deck = {
        "2♥", "3♥",  "4♥", "5♥",  "6♥", "7♥", "8♥", "9♥", "10♥", "В♥", "Д♥",
        "К♥", "Т♥",  "2♦", "3♦",  "4♦", "5♦", "6♦", "7♦", "8♦",  "9♦", "10♦",
        "В♦", "Д♦",  "К♦", "Т♦",  "2♣", "3♣", "4♣", "5♣", "6♣",  "7♣", "8♣",
        "9♣", "10♣", "В♣", "Д♣",  "К♣", "Т♣", "2♠", "3♠", "4♠",  "5♠", "6♠",
        "7♠", "8♠",  "9♠", "10♠", "В♠", "Д♠", "К♠", "Т♠"};

    std::shuffle(deck.begin(), deck.end(), rng.engine());

    uint32_t n = 1;
    std::cout << "Shuffled deck:\n";
    for (std::string card : deck)
        std::cout << card << (n++ % 13 == 0 ? "\n" : " ");

    return 0;
}
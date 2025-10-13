#include <bits/stdc++.h>

int main() {
    std::vector<std::string> suits = {"S", "H", "D", "C"};
    std::vector<std::string> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    std::vector<std::string> deck;
    deck.reserve(52);
    for (const auto &s : suits) {
        for (const auto &r : ranks) {
            deck.push_back(s + r);
        }
    }
    unsigned seed;
    if (std::cin >> seed) {
        std::mt19937 rng(seed);
        std::shuffle(deck.begin(), deck.end(), rng);
    } else {
        std::mt19937 rng(std::random_device{}());
        std::shuffle(deck.begin(), deck.end(), rng);
    }
    std::array<std::vector<std::string>, 4> players;
    for (int i = 0; i < 52; ++i) {
        players[i % 4].push_back(deck[i]);
    }
    const std::array<std::string, 4> names = {"North", "East", "South", "West"};
    for (int i = 0; i < 4; ++i) {
        std::cout << names[i] << ':';
        std::sort(players[i].begin(), players[i].end());
        for (const auto &card : players[i]) {
            std::cout << ' ' << card;
        }
        std::cout << '\n';
    }
    return 0;
}

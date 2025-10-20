#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> suits = {"S", "H", "D", "C"};
    vector<string> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    vector<string> deck;
    deck.reserve(52);
    for (const auto &s : suits) {
        for (const auto &r : ranks) {
            deck.push_back(s + r);
        }
    }
    unsigned seed;
    if (cin >> seed) {
        mt19937 rng(seed);
        shuffle(deck.begin(), deck.end(), rng);
    } else {
        mt19937 rng(random_device{}());
        shuffle(deck.begin(), deck.end(), rng);
    }
    array<vector<string>, 4> players;
    for (int i = 0; i < 52; ++i) {
        players[i % 4].push_back(deck[i]);
    }
    const array<string, 4> names = {"North", "East", "South", "West"};
    for (int i = 0; i < 4; ++i) {
        cout << names[i] << ':';
        sort(players[i].begin(), players[i].end());
        for (const auto &card : players[i]) {
            cout << ' ' << card;
        }
        cout << '\n';
    }
    return 0;
}

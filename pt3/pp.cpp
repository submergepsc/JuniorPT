#include <bits/stdc++.h>

int main() {
    std::vector<char> opponents = {'X', 'Y', 'Z'};
    do {
        bool ok = true;
        if (opponents[0] == 'X') ok = false; // A vs X
        if (opponents[2] == 'X' || opponents[2] == 'Z') ok = false; // C vs X or Z
        if (ok) {
            std::cout << "A vs " << opponents[0] << '\n';
            std::cout << "B vs " << opponents[1] << '\n';
            std::cout << "C vs " << opponents[2] << '\n';
            return 0;
        }
    } while (std::next_permutation(opponents.begin(), opponents.end()));
    std::cout << "No valid arrangement" << '\n';
    return 0;
}

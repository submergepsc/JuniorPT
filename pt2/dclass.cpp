#include <bits/stdc++.h>

int main() {
    std::vector<int> ids;
    for (int id = 2020001; id <= 2020100; ++id) {
        ids.push_back(id);
    }
    unsigned seed;
    if (std::cin >> seed) {
        std::mt19937 rng(seed);
        std::shuffle(ids.begin(), ids.end(), rng);
    } else {
        std::mt19937 rng(std::random_device{}());
        std::shuffle(ids.begin(), ids.end(), rng);
    }
    auto print_group = [](const std::vector<int> &group) {
        for (size_t i = 0; i < group.size(); ++i) {
            std::cout << group[i];
            if ((i + 1) % 8 == 0 || i + 1 == group.size()) {
                std::cout << '\n';
            } else {
                std::cout << ' ';
            }
        }
    };

    std::vector<int> classA(ids.begin(), ids.begin() + 50);
    std::vector<int> classB(ids.begin() + 50, ids.end());

    std::cout << "Class A:\n";
    print_group(classA);
    std::cout << "Class B:\n";
    print_group(classB);
    return 0;
}

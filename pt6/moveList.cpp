#include <bits/stdc++.h>

int main() {
    int n;
    if (!(std::cin >> n) || n <= 0) {
        return 0;
    }
    std::vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> values[i];
    }
    std::vector<int> kept;
    int max_val = std::numeric_limits<int>::min();
    for (int i = n - 1; i >= 0; --i) {
        if (values[i] >= max_val) {
            kept.push_back(values[i]);
            max_val = values[i];
        }
    }
    std::reverse(kept.begin(), kept.end());
    for (size_t i = 0; i < kept.size(); ++i) {
        if (i) {
            std::cout << ' ';
        }
        std::cout << kept[i];
    }
    std::cout << '\n';
    return 0;
}

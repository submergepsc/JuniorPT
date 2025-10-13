#include <bits/stdc++.h>

int main() {
    int n;
    if (!(std::cin >> n) || n <= 0) {
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        int stars = 2 * i - 1;
        std::cout << std::string(stars, '*') << '\n';
    }
    for (int i = n - 1; i >= 1; --i) {
        int stars = 2 * i - 1;
        std::cout << std::string(stars, '*') << '\n';
    }
    return 0;
}

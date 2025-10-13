#include <bits/stdc++.h>

int main() {
    int n;
    if (!(std::cin >> n) || n < 2 || n > 9) {
        return 0;
    }
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j) {
                std::cout << ' ';
            }
            std::cout << nums[(i + j) % n];
        }
        std::cout << '\n';
    }
    return 0;
}

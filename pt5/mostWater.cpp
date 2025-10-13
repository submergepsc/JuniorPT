#include <bits/stdc++.h>

int main() {
    int n;
    if (!(std::cin >> n) || n < 2) {
        return 0;
    }
    std::vector<int> height(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> height[i];
    }
    int left = 0;
    int right = n - 1;
    long long best = 0;
    while (left < right) {
        long long width = right - left;
        long long h = std::min(height[left], height[right]);
        best = std::max(best, width * h);
        if (height[left] < height[right]) {
            ++left;
        } else {
            --right;
        }
    }
    std::cout << best << '\n';
    return 0;
}

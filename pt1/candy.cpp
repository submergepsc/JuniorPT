#include <bits/stdc++.h>

int main() {
    int n;
    if (!(std::cin >> n) || n <= 0) {
        return 0;
    }
    std::vector<int> ratings(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> ratings[i];
    }
    std::vector<int> candies(n, 1);
    for (int i = 1; i < n; ++i) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }
    for (int i = n - 2; i >= 0; --i) {
        if (ratings[i] > ratings[i + 1]) {
            candies[i] = std::max(candies[i], candies[i + 1] + 1);
        }
    }
    long long total = std::accumulate(candies.begin(), candies.end(), 0LL);
    std::cout << total << '\n';
    return 0;
}

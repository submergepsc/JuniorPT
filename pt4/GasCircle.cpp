#include <bits/stdc++.h>

int main() {
    int n;
    if (!(std::cin >> n) || n <= 0) {
        return 0;
    }
    std::vector<int> gas(n), cost(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> gas[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> cost[i];
    }
    int total = 0;
    int tank = 0;
    int start = 0;
    for (int i = 0; i < n; ++i) {
        int diff = gas[i] - cost[i];
        total += diff;
        tank += diff;
        if (tank < 0) {
            tank = 0;
            start = i + 1;
        }
    }
    if (total >= 0 && start < n) {
        std::cout << start << '\n';
    } else {
        std::cout << -1 << '\n';
    }
    return 0;
}

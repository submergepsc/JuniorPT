#include <bits/stdc++.h>

int main() {
    int n, m;
    if (!(std::cin >> n >> m) || n <= 0 || m <= 0) {
        return 0;
    }
    std::vector<int> monkeys(n);
    std::iota(monkeys.begin(), monkeys.end(), 1);
    int index = 0;
    while (monkeys.size() > 1) {
        index = (index + m - 1) % monkeys.size();
        monkeys.erase(monkeys.begin() + index);
    }
    std::cout << monkeys.front() << '\n';
    return 0;
}

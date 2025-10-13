#include <bits/stdc++.h>

void countDigit(long long n, std::array<int, 10> &a) {
    a.fill(0);
    if (n == 0) {
        a[0] = 1;
        return;
    }
    long long value = std::llabs(n);
    while (value > 0) {
        int d = static_cast<int>(value % 10);
        ++a[d];
        value /= 10;
    }
}

int main() {
    long long n;
    if (!(std::cin >> n)) {
        return 0;
    }
    std::array<int, 10> cnt{};
    countDigit(n, cnt);
    for (int i = 0; i < 10; ++i) {
        std::cout << i << ':' << cnt[i];
        if (i + 1 != 10) {
            std::cout << ' ';
        }
    }
    std::cout << '\n';
    return 0;
}

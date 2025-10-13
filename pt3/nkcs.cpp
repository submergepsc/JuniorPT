#include <bits/stdc++.h>

int main() {
    long long n;
    if (!(std::cin >> n) || n <= 0) {
        return 0;
    }
    long long start = n * n - n + 1;
    std::cout << n << "^3 = ";
    for (long long i = 0; i < n; ++i) {
        if (i) {
            std::cout << '+';
        }
        std::cout << (start + 2 * i);
    }
    std::cout << '\n';
    return 0;
}

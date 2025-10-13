#include <bits/stdc++.h>

int main() {
    int n;
    if (!(std::cin >> n) || n <= 0 || n % 2 == 0) {
        return 0;
    }
    std::vector<std::vector<int>> magic(n, std::vector<int>(n, 0));
    int num = 1;
    int i = 0;
    int j = n / 2;
    while (num <= n * n) {
        magic[i][j] = num;
        if (num % n == 0) {
            i = (i + 1) % n;
        } else {
            i = (i - 1 + n) % n;
            j = (j + 1) % n;
        }
        ++num;
    }
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (c) {
                std::cout << ' ';
            }
            std::cout << magic[r][c];
        }
        std::cout << '\n';
    }
    return 0;
}

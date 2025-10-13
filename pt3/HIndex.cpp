#include <bits/stdc++.h>

int main() {
    int n;
    if (!(std::cin >> n) || n <= 0) {
        return 0;
    }
    std::vector<int> citations(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> citations[i];
    }
    std::sort(citations.begin(), citations.end(), std::greater<int>());
    int h = 0;
    for (int i = 0; i < n; ++i) {
        if (citations[i] >= i + 1) {
            h = i + 1;
        } else {
            break;
        }
    }
    std::cout << h << '\n';
    return 0;
}

#include <bits/stdc++.h>

int main() {
    int n;
    if (!(std::cin >> n) || n <= 0) {
        return 0;
    }
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    int x;
    std::cin >> x;
    a.insert(std::upper_bound(a.begin(), a.end(), x), x);
    for (size_t i = 0; i < a.size(); ++i) {
        if (i) {
            std::cout << ' ';
        }
        std::cout << a[i];
    }
    std::cout << '\n';
    return 0;
}

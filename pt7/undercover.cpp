#include <bits/stdc++.h>

int main() {
    int n, m;
    if (!(std::cin >> n >> m) || n <= 0 || m < 0) {
        return 0;
    }
    std::vector<int> statements(n);
    for (int i = 0; i < n; ++i) {
        std::string token;
        std::cin >> token;
        statements[i] = std::stoi(token);
    }
    bool any_valid = false;
    std::vector<int> state(n, -1); // -1 unknown, 0 lie, 1 truth, 2 ambiguous
    for (int undercover = 1; undercover <= n; ++undercover) {
        int truths = 0;
        std::vector<int> current(n);
        for (int i = 0; i < n; ++i) {
            int claim = statements[i];
            int target = std::abs(claim);
            bool is_true = (claim > 0) ? (undercover == target) : (undercover != target);
            current[i] = is_true ? 1 : 0;
            if (is_true) {
                ++truths;
            }
        }
        if (truths == m) {
            any_valid = true;
            for (int i = 0; i < n; ++i) {
                if (state[i] == -1) {
                    state[i] = current[i];
                } else if (state[i] != current[i]) {
                    state[i] = 2;
                }
            }
        }
    }
    if (!any_valid) {
        for (int i = 0; i < n; ++i) {
            std::cout << "contradiction" << '\n';
        }
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (state[i] == 1) {
            std::cout << "truth" << '\n';
        } else if (state[i] == 0) {
            std::cout << "lie" << '\n';
        } else {
            std::cout << "not defined" << '\n';
        }
    }
    return 0;
}

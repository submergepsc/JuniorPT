#include <bits/stdc++.h>

int main() {
    int k, n;
    long long w;
    if (!(std::cin >> k >> w >> n) || k < 0 || n < 0) {
        return 0;
    }
    std::vector<long long> profits(n);
    std::vector<long long> capital(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> profits[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> capital[i];
    }
    std::vector<std::pair<long long, long long>> projects;
    projects.reserve(n);
    for (int i = 0; i < n; ++i) {
        projects.emplace_back(capital[i], profits[i]);
    }
    std::sort(projects.begin(), projects.end());
    std::priority_queue<long long> available;
    size_t idx = 0;
    for (int i = 0; i < k; ++i) {
        while (idx < projects.size() && projects[idx].first <= w) {
            available.push(projects[idx].second);
            ++idx;
        }
        if (available.empty()) {
            break;
        }
        w += available.top();
        available.pop();
    }
    std::cout << w << '\n';
    return 0;
}

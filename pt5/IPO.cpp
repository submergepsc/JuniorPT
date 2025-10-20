#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int main() {
    int k, n;
    long long w;
    if (!(cin >> k >> w >> n) || k < 0 || n < 0) {
        return 0;
    }
    vector<long long> profits(n);
    vector<long long> capital(n);
    for (int i = 0; i < n; ++i) {
        cin >> profits[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> capital[i];
    }
    vector<pair<long long, long long>> projects;
    projects.reserve(n);
    for (int i = 0; i < n; ++i) {
        projects.emplace_back(capital[i], profits[i]);
    }
    sort(projects.begin(), projects.end());
    priority_queue<long long> available;
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
    cout << w << '\n';
    return 0;
}

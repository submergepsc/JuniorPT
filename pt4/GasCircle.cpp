#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    if (!(cin >> n) || n <= 0) {
        return 0;
    }
    vector<int> gas(n), cost(n);
    for (int i = 0; i < n; ++i) {
        cin >> gas[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
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
        cout << start << '\n';
    } else {
        cout << -1 << '\n';
    }
    return 0;
}

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    int n;
    if (!(cin >> n) || n <= 0) {
        return 0;
    }
    vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        cin >> values[i];
    }
    vector<int> kept;
    int max_val = numeric_limits<int>::min();
    for (int i = n - 1; i >= 0; --i) {
        if (values[i] >= max_val) {
            kept.push_back(values[i]);
            max_val = values[i];
        }
    }
    for (size_t idx = 0; idx < kept.size(); ++idx) {
        size_t i = kept.size() - 1 - idx;
        if (idx) {
            cout << ' ';
        }
        cout << kept[i];
    }
    cout << '\n';
    return 0;
}

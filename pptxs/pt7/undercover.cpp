#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n, m;
    if (!(cin >> n >> m) || n <= 0 || m < 0) {
        return 0;
    }
    vector<int> statements(n);
    for (int i = 0; i < n; ++i) {
        string token;
        cin >> token;
        statements[i] = stoi(token);
    }
    bool any_valid = false;
    vector<int> state(n, -1); // -1 unknown, 0 lie, 1 truth, 2 ambiguous
    for (int undercover = 1; undercover <= n; ++undercover) {
        int truths = 0;
        vector<int> current(n);
        for (int i = 0; i < n; ++i) {
            int claim = statements[i];
            int target = claim >= 0 ? claim : -claim;
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
            cout << "contradiction" << '\n';
        }
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (state[i] == 1) {
            cout << "truth" << '\n';
        } else if (state[i] == 0) {
            cout << "lie" << '\n';
        } else {
            cout << "not defined" << '\n';
        }
    }
    return 0;
}

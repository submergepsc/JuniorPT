#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    if (!(cin >> n >> m) || n <= 0 || m <= 0) {
        return 0;
    }
    vector<int> monkeys(n);
    for (int i = 0; i < n; ++i) {
        monkeys[i] = i + 1;
    }
    int index = 0;
    while (monkeys.size() > 1) {
        index = (index + m - 1) % monkeys.size();
        monkeys.erase(monkeys.begin() + index);
    }
    cout << monkeys.front() << '\n';
    return 0;
}

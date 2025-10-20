#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    if (!(cin >> n) || n <= 0) {
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        int stars = 2 * i - 1;
        cout << string(stars, '*') << '\n';
    }
    for (int i = n - 1; i >= 1; --i) {
        int stars = 2 * i - 1;
        cout << string(stars, '*') << '\n';
    }
    return 0;
}

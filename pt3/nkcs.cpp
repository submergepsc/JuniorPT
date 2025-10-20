#include <iostream>

using namespace std;

int main() {
    long long n;
    if (!(cin >> n) || n <= 0) {
        return 0;
    }
    long long start = n * n - n + 1;
    cout << n << "^3 = ";
    for (long long i = 0; i < n; ++i) {
        if (i) {
            cout << '+';
        }
        cout << (start + 2 * i);
    }
    cout << '\n';
    return 0;
}

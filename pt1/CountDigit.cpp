#include <array>
#include <iostream>

using namespace std;

void countDigit(long long n, array<int, 10> &a) {
    a.fill(0);
    if (n == 0) {
        a[0] = 1;
        return;
    }
    long long value = n >= 0 ? n : -n;
    while (value > 0) {
        int d = static_cast<int>(value % 10);
        ++a[d];
        value /= 10;
    }
}

int main() {
    long long n;
    if (!(cin >> n)) {
        return 0;
    }
    array<int, 10> cnt{};
    countDigit(n, cnt);
    for (int i = 0; i < 10; ++i) {
        cout << i << ':' << cnt[i];
        if (i + 1 != 10) {
            cout << ' ';
        }
    }
    cout << '\n';
    return 0;
}

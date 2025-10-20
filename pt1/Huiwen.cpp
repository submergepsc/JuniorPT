#include <iostream>

using namespace std;

int main() {
    long long n;
    if (!(cin >> n) || n < 0) {
        return 0;
    }
    long long original = n;
    long long reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    if (reversed == original) {
        cout << "Yes" << '\n';
    } else {
        cout << "No" << '\n';
    }
    return 0;
}

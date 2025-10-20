#include <iostream>

using namespace std;

bool isAutomorphic(int n) {
    long long square = 1LL * n * n;
    int temp = n;
    while (temp > 0) {
        if (square % 10 != temp % 10) {
            return false;
        }
        square /= 10;
        temp /= 10;
    }
    return true;
}

int main() {
    for (int i = 1; i <= 10000; ++i) {
        if (isAutomorphic(i)) {
            cout << i << '\n';
        }
    }
    return 0;
}

#include <iostream>

using namespace std;

int main() {
    for (int i = 32; i <= 99; ++i) {
        int sq = i * i;
        if (sq < 1000 || sq > 9999) {
            continue;
        }
        int a = sq / 1000;
        int b = (sq / 100) % 10;
        int c = (sq / 10) % 10;
        int d = sq % 10;
        if (a == b && c == d && a != c) {
            cout << "Plate: " << sq << " (" << i << "^2)" << '\n';
        }
    }
    return 0;
}

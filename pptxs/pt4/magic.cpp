#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    if (!(cin >> n) || n <= 0 || n % 2 == 0) {
        return 0;
    }
    vector<vector<int>> magic(n, vector<int>(n, 0));
    int num = 1;
    int i = 0;
    int j = n / 2;
    while (num <= n * n) {
        magic[i][j] = num;
        if (num % n == 0) {
            i = (i + 1) % n;
        } else {
            i = (i - 1 + n) % n;
            j = (j + 1) % n;
        }
        ++num;
    }
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (c) {
                cout << ' ';
            }
            cout << magic[r][c];
        }
        cout << '\n';
    }
    return 0;
}

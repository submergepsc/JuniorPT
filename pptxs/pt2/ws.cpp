#include <iostream>
#include <vector>

using namespace std;

int main() {
    for (int n = 2; n <= 1000; ++n) {
        vector<int> divisors;
        int sum = 0;
        for (int i = 1; i <= n / 2; ++i) {
            if (n % i == 0) {
                divisors.push_back(i);
                sum += i;
            }
        }
        if (sum == n) {
            cout << n << " = ";
            for (size_t i = 0; i < divisors.size(); ++i) {
                if (i) {
                    cout << " + ";
                }
                cout << divisors[i];
            }
            cout << '\n';
        }
    }
    return 0;
}

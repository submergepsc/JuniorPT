#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

string factorize(long long n) {
    vector<long long> factors;
    long long value = n;
    for (long long i = 2; i * i <= value; ++i) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 1) {
        factors.push_back(n);
    }
    ostringstream oss;
    oss << value << '=';
    for (size_t i = 0; i < factors.size(); ++i) {
        if (i) {
            oss << '*';
        }
        oss << factors[i];
    }
    return oss.str();
}

int main() {
    long long n;
    if (!(cin >> n) || n <= 1) {
        return 0;
    }
    cout << factorize(n) << '\n';
    return 0;
}

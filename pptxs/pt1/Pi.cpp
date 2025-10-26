#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    const double eps = 1e-8;
    double sum = 0.0;
    double term;
    long long k = 0;
    int sign = 1;
    while (true) {
        term = sign * 1.0 / (2 * k + 1);
        sum += term;
        if (fabs(term) < eps) {
            break;
        }
        ++k;
        sign = -sign;
    }
    cout.setf(ios::fixed);
    cout << setprecision(10) << sum * 4 << '\n';
    cout << "terms=" << (k + 1) << '\n';
    return 0;
}

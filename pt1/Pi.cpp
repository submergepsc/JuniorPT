#include <bits/stdc++.h>

int main() {
    const double eps = 1e-8;
    double sum = 0.0;
    double term;
    long long k = 0;
    int sign = 1;
    while (true) {
        term = sign * 1.0 / (2 * k + 1);
        sum += term;
        if (std::fabs(term) < eps) {
            break;
        }
        ++k;
        sign = -sign;
    }
    std::cout.setf(std::ios::fixed);
    std::cout << std::setprecision(10) << sum * 4 << '\n';
    std::cout << "terms=" << (k + 1) << '\n';
    return 0;
}

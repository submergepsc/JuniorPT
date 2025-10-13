#include <bits/stdc++.h>

int main() {
    std::string s;
    if (!(std::cin >> s)) {
        return 0;
    }
    bool valid = !s.empty();
    long long value = 0;
    for (char ch : s) {
        if (ch < '0' || ch > '7') {
            valid = false;
            break;
        }
        int digit = ch - '0';
        value = value * 8 + digit;
    }
    if (!valid) {
        std::cout << "Invalid octal number" << '\n';
    } else {
        std::cout << value << '\n';
    }
    return 0;
}

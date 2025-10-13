#include <bits/stdc++.h>

int main() {
    std::string s;
    if (!(std::cin >> s) || s.size() != 4) {
        return 0;
    }
    for (char &ch : s) {
        if (!std::isdigit(static_cast<unsigned char>(ch))) {
            return 0;
        }
        int digit = (ch - '0' + 5) % 10;
        ch = static_cast<char>('0' + digit);
    }
    std::swap(s[0], s[3]);
    std::swap(s[1], s[2]);
    std::cout << s << '\n';
    return 0;
}

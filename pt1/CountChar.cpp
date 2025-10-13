#include <bits/stdc++.h>

int main() {
    std::string s;
    if (!std::getline(std::cin, s)) {
        return 0;
    }
    if (s.empty() && std::cin) {
        std::getline(std::cin, s);
    }
    std::map<char, int> freq;
    for (char ch : s) {
        ++freq[ch];
    }
    bool first = true;
    for (const auto &entry : freq) {
        if (!first) {
            std::cout << ' ';
        }
        std::cout << entry.first << '=' << entry.second;
        first = false;
    }
    if (!freq.empty()) {
        std::cout << '\n';
    }
    return 0;
}

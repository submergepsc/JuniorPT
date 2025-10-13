#include <bits/stdc++.h>

int main() {
    std::map<std::string, int> freq;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::string word;
        for (char ch : line) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                word.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
            } else {
                if (!word.empty()) {
                    ++freq[word];
                    word.clear();
                }
            }
        }
        if (!word.empty()) {
            ++freq[word];
        }
    }
    for (const auto &entry : freq) {
        std::cout << entry.first << ' ' << entry.second << '\n';
    }
    return 0;
}

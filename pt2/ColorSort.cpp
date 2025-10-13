#include <bits/stdc++.h>

int main() {
    std::vector<std::string> colors;
    std::string token;
    while (std::cin >> token) {
        std::string cleaned;
        for (char ch : token) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                cleaned.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
            }
        }
        if (!cleaned.empty()) {
            colors.push_back(cleaned);
        }
    }
    if (colors.empty()) {
        return 0;
    }
    auto order = [](const std::string &color) {
        if (color == "red") return 0;
        if (color == "green" || color == "white") return 1;
        if (color == "blue") return 2;
        return 3;
    };
    std::stable_sort(colors.begin(), colors.end(), [&](const std::string &a, const std::string &b) {
        int oa = order(a);
        int ob = order(b);
        if (oa != ob) {
            return oa < ob;
        }
        return a < b;
    });
    for (size_t i = 0; i < colors.size(); ++i) {
        if (i) {
            std::cout << ' ';
        }
        std::cout << colors[i];
    }
    std::cout << '\n';
    return 0;
}

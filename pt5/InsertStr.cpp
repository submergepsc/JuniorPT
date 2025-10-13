#include <bits/stdc++.h>

int main() {
    std::string mainStr;
    if (!std::getline(std::cin, mainStr)) {
        return 0;
    }
    std::string subStr;
    if (!std::getline(std::cin, subStr)) {
        return 0;
    }
    int pos;
    if (!(std::cin >> pos)) {
        pos = static_cast<int>(mainStr.size());
    }
    pos = std::clamp(pos, 0, static_cast<int>(mainStr.size()));
    mainStr.insert(pos, subStr);
    std::cout << mainStr << '\n';
    return 0;
}

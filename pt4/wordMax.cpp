 #include<bits/stdc++.h>
int main() {
    std::string line;
    std::getline(std::cin, line);
    if (line.empty() && std::cin.good()) {
        std::getline(std::cin, line);
    }
    std::istringstream iss(line);
    std::string word;
    std::string best;
    while (iss >> word) {
        if (word.size() > best.size()) {
            best = word;
        }
    }
    if (!best.empty()) {
        std::cout << best << ' ' << best.size() << '\n';
    }
    return 0;
}


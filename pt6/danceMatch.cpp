#include <bits/stdc++.h>

int main() {
    int total;
    if (!(std::cin >> total) || total <= 0) {
        return 0;
    }
    std::queue<std::string> males;
    std::queue<std::string> females;
    for (int i = 0; i < total; ++i) {
        std::string name, gender;
        std::cin >> name >> gender;
        if (!std::cin) {
            return 0;
        }
        if (gender == "M" || gender == "m") {
            males.push(name);
        } else if (gender == "F" || gender == "f") {
            females.push(name);
        }
    }
    int songs;
    if (!(std::cin >> songs) || songs < 0) {
        return 0;
    }
    struct PairInfo {
        std::string male;
        std::string female;
    };
    std::vector<PairInfo> history;
    history.reserve(songs);
    for (int k = 1; k <= songs; ++k) {
        if (!males.empty() && !females.empty()) {
            std::string m = males.front();
            males.pop();
            std::string f = females.front();
            females.pop();
            history.push_back({m, f});
            std::cout << "Song " << k << ": " << m << " - " << f << '\n';
            males.push(m);
            females.push(f);
        } else {
            history.push_back({"", ""});
            std::cout << "Song " << k << ": waiting" << '\n';
        }
    }
    int q;
    if (std::cin >> q) {
        for (int i = 0; i < q; ++i) {
            std::string mname, fname;
            std::cin >> mname >> fname;
            if (!std::cin) {
                break;
            }
            std::vector<int> occurrences;
            for (size_t k = 0; k < history.size(); ++k) {
                if (history[k].male == mname && history[k].female == fname) {
                    occurrences.push_back(static_cast<int>(k) + 1);
                }
            }
            if (occurrences.empty()) {
                std::cout << mname << " and " << fname << " never danced together" << '\n';
            } else {
                std::cout << mname << " and " << fname << " danced on songs: ";
                for (size_t idx = 0; idx < occurrences.size(); ++idx) {
                    if (idx) {
                        std::cout << ' ';
                    }
                    std::cout << occurrences[idx];
                }
                std::cout << '\n';
            }
        }
    }
    return 0;
}

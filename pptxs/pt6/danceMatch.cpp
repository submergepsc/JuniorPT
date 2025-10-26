#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int main() {
    int total;
    if (!(cin >> total) || total <= 0) {
        return 0;
    }
    queue<string> males;
    queue<string> females;
    for (int i = 0; i < total; ++i) {
        string name, gender;
        cin >> name >> gender;
        if (!cin) {
            return 0;
        }
        if (gender == "M" || gender == "m") {
            males.push(name);
        } else if (gender == "F" || gender == "f") {
            females.push(name);
        }
    }
    int songs;
    if (!(cin >> songs) || songs < 0) {
        return 0;
    }
    struct PairInfo {
        string male;
        string female;
    };
    vector<PairInfo> history;
    history.reserve(songs);
    for (int k = 1; k <= songs; ++k) {
        if (!males.empty() && !females.empty()) {
            string m = males.front();
            males.pop();
            string f = females.front();
            females.pop();
            history.push_back({m, f});
            cout << "Song " << k << ": " << m << " - " << f << '\n';
            males.push(m);
            females.push(f);
        } else {
            history.push_back({"", ""});
            cout << "Song " << k << ": waiting" << '\n';
        }
    }
    int q;
    if (cin >> q) {
        for (int i = 0; i < q; ++i) {
            string mname, fname;
            cin >> mname >> fname;
            if (!cin) {
                break;
            }
            vector<int> occurrences;
            for (size_t k = 0; k < history.size(); ++k) {
                if (history[k].male == mname && history[k].female == fname) {
                    occurrences.push_back(static_cast<int>(k) + 1);
                }
            }
            if (occurrences.empty()) {
                cout << mname << " and " << fname << " never danced together" << '\n';
            } else {
                cout << mname << " and " << fname << " danced on songs: ";
                for (size_t idx = 0; idx < occurrences.size(); ++idx) {
                    if (idx) {
                        cout << ' ';
                    }
                    cout << occurrences[idx];
                }
                cout << '\n';
            }
        }
    }
    return 0;
}

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    string line;
    getline(cin, line);
    if (line.empty() && cin.good()) {
        getline(cin, line);
    }
    istringstream iss(line);
    string word;
    string best;
    while (iss >> word) {
        if (word.size() > best.size()) {
            best = word;
        }
    }
    if (!best.empty()) {
        cout << best << ' ' << best.size() << '\n';
    }
    return 0;
}


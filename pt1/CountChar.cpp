#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    string s;
    if (!getline(cin, s)) {
        return 0;
    }
    if (s.empty() && cin) {
        getline(cin, s);
    }
    map<char, int> freq;
    for (char ch : s) {
        ++freq[ch];
    }
    bool first = true;
    for (const auto &entry : freq) {
        if (!first) {
            cout << ' ';
        }
        cout << entry.first << '=' << entry.second;
        first = false;
    }
    if (!freq.empty()) {
        cout << '\n';
    }
    return 0;
}

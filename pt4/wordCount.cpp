#include <cctype>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    map<string, int> freq;
    string line;
    while (getline(cin, line)) {
        string word;
        for (char ch : line) {
            if (isalpha(static_cast<unsigned char>(ch))) {
                word.push_back(static_cast<char>(tolower(static_cast<unsigned char>(ch))));
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
        cout << entry.first << ' ' << entry.second << '\n';
    }
    return 0;
}

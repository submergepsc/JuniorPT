#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> reds;
    vector<string> middles;
    vector<string> blues;
    vector<string> others;
    string token;
    while (cin >> token) {
        string cleaned;
        for (char ch : token) {
            if (isalpha(static_cast<unsigned char>(ch))) {
                cleaned.push_back(static_cast<char>(tolower(static_cast<unsigned char>(ch))));
            }
        }
        if (cleaned.empty()) {
            continue;
        }
        if (cleaned == "red") {
            reds.push_back(cleaned);
        } else if (cleaned == "green" || cleaned == "white") {
            middles.push_back(cleaned);
        } else if (cleaned == "blue") {
            blues.push_back(cleaned);
        } else {
            others.push_back(cleaned);
        }
    }
    bool first = true;
    vector<vector<string>> groups = {reds, middles, blues, others};
    for (const vector<string> &group : groups) {
        for (const string &color : group) {
            if (!first) {
                cout << ' ';
            }
            cout << color;
            first = false;
        }
    }
    if (!first) {
        cout << '\n';
    }
    return 0;
}

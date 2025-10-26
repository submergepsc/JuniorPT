#include <iostream>
#include <string>

using namespace std;

int main() {
    string mainStr;
    if (!getline(cin, mainStr)) {
        return 0;
    }
    string subStr;
    if (!getline(cin, subStr)) {
        return 0;
    }
    int pos;
    if (!(cin >> pos)) {
        pos = static_cast<int>(mainStr.size());
    }
    if (pos < 0) {
        pos = 0;
    }
    if (pos > static_cast<int>(mainStr.size())) {
        pos = static_cast<int>(mainStr.size());
    }
    mainStr.insert(static_cast<size_t>(pos), subStr);
    cout << mainStr << '\n';
    return 0;
}

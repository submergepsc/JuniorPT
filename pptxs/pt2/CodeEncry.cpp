#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    if (!(cin >> s) || s.size() != 4) {
        return 0;
    }
    for (char &ch : s) {
        if (!isdigit(static_cast<unsigned char>(ch))) {
            return 0;
        }
        int digit = (ch - '0' + 5) % 10;
        ch = static_cast<char>('0' + digit);
    }
    swap(s[0], s[3]);
    swap(s[1], s[2]);
    cout << s << '\n';
    return 0;
}

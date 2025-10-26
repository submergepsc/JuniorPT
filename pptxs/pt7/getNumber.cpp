#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string line;
    if (!getline(cin, line)) {
        return 0;
    }
    vector<long long> numbers;
    long long current = 0;
    bool in_number = false;
    for (char ch : line) {
        if (isdigit(static_cast<unsigned char>(ch))) {
            current = current * 10 + (ch - '0');
            in_number = true;
        } else if (in_number) {
            numbers.push_back(current);
            current = 0;
            in_number = false;
        }
    }
    if (in_number) {
        numbers.push_back(current);
    }
    for (size_t i = 0; i < numbers.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << numbers[i];
    }
    cout << '\n';
    return 0;
}

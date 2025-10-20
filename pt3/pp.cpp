#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<char> opponents = {'X', 'Y', 'Z'};
    do {
        bool ok = true;
        if (opponents[0] == 'X') ok = false; // A vs X
        if (opponents[2] == 'X' || opponents[2] == 'Z') ok = false; // C vs X or Z
        if (ok) {
            cout << "A vs " << opponents[0] << '\n';
            cout << "B vs " << opponents[1] << '\n';
            cout << "C vs " << opponents[2] << '\n';
            return 0;
        }
    } while (next_permutation(opponents.begin(), opponents.end()));
    cout << "No valid arrangement" << '\n';
    return 0;
}

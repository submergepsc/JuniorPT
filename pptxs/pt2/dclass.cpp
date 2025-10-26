#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main() {
    vector<int> ids;
    for (int id = 2020001; id <= 2020100; ++id) {
        ids.push_back(id);
    }
    unsigned seed;
    if (cin >> seed) {
        mt19937 rng(seed);
        shuffle(ids.begin(), ids.end(), rng);
    } else {
        mt19937 rng(random_device{}());
        shuffle(ids.begin(), ids.end(), rng);
    }
    vector<int> classA(ids.begin(), ids.begin() + 50);
    vector<int> classB(ids.begin() + 50, ids.end());

    cout << "Class A:\n";
    for (size_t i = 0; i < classA.size(); ++i) {
        cout << classA[i];
        if ((i + 1) % 8 == 0 || i + 1 == classA.size()) {
            cout << '\n';
        } else {
            cout << ' ';
        }
    }
    cout << "Class B:\n";
    for (size_t i = 0; i < classB.size(); ++i) {
        cout << classB[i];
        if ((i + 1) % 8 == 0 || i + 1 == classB.size()) {
            cout << '\n';
        } else {
            cout << ' ';
        }
    }
    return 0;
}

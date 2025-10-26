#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    if (!(cin >> n) || n <= 0) {
        return 0;
    }
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int x;
    cin >> x;
    size_t pos = 0;
    while (pos < a.size() && a[pos] <= x) {
        ++pos;
    }
    a.insert(a.begin() + static_cast<long long>(pos), x);
    for (size_t i = 0; i < a.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
    return 0;
}
 

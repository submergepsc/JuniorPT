#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    if (!(cin >> n) || n <= 0) {
        return 0;
    }
    vector<int> citations(n);
    for (int i = 0; i < n; ++i) {
        cin >> citations[i];
    }
    sort(citations.begin(), citations.end());
    int h = 0;
    for (int i = 0; i < n; ++i) {
        int papers_at_least = n - i;
        if (citations[i] >= papers_at_least) {
            h = papers_at_least;
            break;
        }
    }
    cout << h << '\n';
    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    if (!(cin >> n) || n < 2) {
        return 0;
    }
    vector<int> height(n);
    for (int i = 0; i < n; ++i) {
        cin >> height[i];
    }
    int left = 0;
    int right = n - 1;
    long long best = 0;
    while (left < right) {
        long long width = right - left;
        int h = height[left];
        if (height[right] < h) {
            h = height[right];
        }
        long long area = width * static_cast<long long>(h);
        if (area > best) {
            best = area;
        }
        if (height[left] < height[right]) {
            ++left;
        } else {
            --right;
        }
    }
    cout << best << '\n';
    return 0;
}

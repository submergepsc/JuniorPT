#include <deque>
#include <iostream>

using namespace std;

int main() {
    int n;
    if (!(cin >> n) || n <= 0) {
        return 0;
    }
    deque<int> q;
    for (int i = 1; i <= n; ++i) {
        q.push_back(i);
    }
    bool keep = false;
    while (q.size() > 1) {
        size_t size = q.size();
        deque<int> next;
        keep = false;
        for (size_t i = 0; i < size; ++i) {
            int person = q.front();
            q.pop_front();
            if (keep) {
                next.push_back(person);
            }
            keep = !keep;
        }
        q.swap(next);
    }
    cout << q.front() << '\n';
    return 0;
}

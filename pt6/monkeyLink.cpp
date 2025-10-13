#include <bits/stdc++.h>

struct Node {
    int id;
    Node *next;
    explicit Node(int value) : id(value), next(nullptr) {}
};

int main() {
    int n, m;
    if (!(std::cin >> n >> m) || n <= 0 || m <= 0) {
        return 0;
    }
    Node *head = new Node(1);
    Node *tail = head;
    for (int i = 2; i <= n; ++i) {
        tail->next = new Node(i);
        tail = tail->next;
    }
    tail->next = head;
    Node *prev = tail;
    Node *curr = head;
    while (curr->next != curr) {
        for (int count = 1; count < m; ++count) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        Node *tmp = curr;
        curr = curr->next;
        delete tmp;
    }
    std::cout << curr->id << '\n';
    delete curr;
    return 0;
}

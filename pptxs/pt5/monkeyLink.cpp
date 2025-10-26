#include <iostream>

using namespace std;

struct Node {
    int id;
    Node *next;
    explicit Node(int value) : id(value), next(nullptr) {}
};

int main() {
    int n, m;
    if (!(cin >> n >> m) || n <= 0 || m <= 0) {
        return 0;
    }
    Node *head = new Node(1);
    Node *prev = head;
    for (int i = 2; i <= n; ++i) {
        prev->next = new Node(i);
        prev = prev->next;
    }
    prev->next = head;
    Node *current = head;
    Node *before = prev;
    while (current->next != current) {
        for (int count = 1; count < m; ++count) {
            before = current;
            current = current->next;
        }
        before->next = current->next;
        Node *to_delete = current;
        current = current->next;
        delete to_delete;
    }
    cout << current->id << '\n';
    delete current;
    return 0;
}

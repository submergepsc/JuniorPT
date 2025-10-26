#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int value;
    Node *next;
    explicit Node(int v) : value(v), next(nullptr) {}
};

Node* build_list(const vector<int>& values) {
    if (values.empty()) {
        return nullptr;
    }
    Node *head = new Node(values[0]);
    Node *tail = head;
    for (size_t i = 1; i < values.size(); ++i) {
        tail->next = new Node(values[i]);
        tail = tail->next;
    }
    return head;
}

void append_list(Node *&heada, Node *headb) {
    if (!heada) {
        heada = headb;
        return;
    }
    Node *tail = heada;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = headb;
}

void print_list(Node *head) {
    bool first = true;
    while (head) {
        if (!first) {
            cout << ' ';
        }
        cout << head->value;
        first = false;
        head = head->next;
    }
    cout << '\n';
}

void free_list(Node *head) {
    while (head) {
        Node *next = head->next;
        delete head;
        head = next;
    }
}

int main() {
    int na;
    if (!(cin >> na) || na < 0) {
        return 0;
    }
    vector<int> a(na);
    for (int i = 0; i < na; ++i) {
        cin >> a[i];
    }
    int nb;
    if (!(cin >> nb) || nb < 0) {
        nb = 0;
    }
    vector<int> b(nb);
    for (int i = 0; i < nb; ++i) {
        cin >> b[i];
    }
    Node *heada = build_list(a);
    Node *headb = build_list(b);
    append_list(heada, headb);
    print_list(heada);
    free_list(heada);
    return 0;
}

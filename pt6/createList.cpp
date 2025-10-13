#include <bits/stdc++.h>

struct Node {
    int value;
    Node *next;
    explicit Node(int v) : value(v), next(nullptr) {}
};

Node* build_list(const std::vector<int>& values) {
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
            std::cout << ' ';
        }
        std::cout << head->value;
        first = false;
        head = head->next;
    }
    std::cout << '\n';
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
    if (!(std::cin >> na) || na < 0) {
        return 0;
    }
    std::vector<int> a(na);
    for (int i = 0; i < na; ++i) {
        std::cin >> a[i];
    }
    int nb;
    if (!(std::cin >> nb) || nb < 0) {
        nb = 0;
    }
    std::vector<int> b(nb);
    for (int i = 0; i < nb; ++i) {
        std::cin >> b[i];
    }
    Node *heada = build_list(a);
    Node *headb = build_list(b);
    append_list(heada, headb);
    print_list(heada);
    free_list(heada);
    return 0;
}

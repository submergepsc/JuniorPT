#include <bits/stdc++.h>

struct Node {
    char data;
    Node *next;
    explicit Node(char ch) : data(ch), next(nullptr) {}
};

Node* createList(const std::string &input) {
    Node *head = new Node('\0');
    Node *tail = head;
    for (char ch : input) {
        Node *node = new Node(ch);
        tail->next = node;
        tail = node;
    }
    return head;
}

void printList(Node *head) {
    bool first = true;
    while (head) {
        if (!first) {
            std::cout << ' ';
        }
        std::cout << head->data;
        first = false;
        head = head->next;
    }
    std::cout << '\n';
}

void reverse(Node *head) {
    Node *prev = nullptr;
    Node *curr = head->next;
    while (curr) {
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head->next = prev;
}

void freeList(Node *head) {
    while (head) {
        Node *next = head->next;
        delete head;
        head = next;
    }
}

int main() {
    std::string input;
    if (!std::getline(std::cin, input) || input.empty()) {
        return 0;
    }
    Node *head = createList(input);
    std::cout << "Original:" << '\n';
    printList(head->next);
    reverse(head);
    std::cout << "Reversed:" << '\n';
    printList(head->next);
    freeList(head);
    return 0;
}

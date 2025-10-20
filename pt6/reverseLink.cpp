#include <iostream>
#include <string>

using namespace std;

struct Node {
    char data;
    Node *next;
    explicit Node(char ch) : data(ch), next(nullptr) {}
};

Node* createList(const string &input) {
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
            cout << ' ';
        }
        cout << head->data;
        first = false;
        head = head->next;
    }
    cout << '\n';
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
    string input;
    if (!getline(cin, input) || input.empty()) {
        return 0;
    }
    Node *head = createList(input);
    cout << "Original:" << '\n';
    printList(head->next);
    reverse(head);
    cout << "Reversed:" << '\n';
    printList(head->next);
    freeList(head);
    return 0;
}

#include <iostream>
#include <stdexcept>

template <class T> struct Node {
  T data;
  Node *next;
};

template <class T> class List {
  Node<T> *head;

public:
  List() : head(nullptr) {}

  void add(T &value) {
    Node<T> *node = new Node<T>{value, head};
    head = node;
  }

  void remove(T &value) {
    Node<T> *prev = nullptr;
    Node<T> *curr = head;
    while (curr) {
      if (curr->data == value) {
        if (prev) {
          prev->next = curr->next;
        } else {
          head = curr->next;
        }
        delete curr;
        return;
      }
      prev = curr;
      curr = curr->next;
    }
    throw std::runtime_error("value not found");
  }

  Node<T> *find(T &value) {
    Node<T> *curr = head;
    while (curr) {
      if (curr->data == value) {
        return curr;
      }
      curr = curr->next;
    }
    return nullptr;
  }

  void showList() {
    Node<T> *curr = head;
    while (curr) {
      std::cout << curr->data << ' ';
      curr = curr->next;
    }
    std::cout << '\n';
  }

  ~List() {
    Node<T> *curr = head;
    while (curr) {
      Node<T> *next = curr->next;
      delete curr;
      curr = next;
    }
  }
};

int main() {
  List<int> list;
  for (int i = 1; i <= 5; ++i) {
    int v = i * 2;
    list.add(v);
  }
  std::cout << "Current list: ";
  list.showList();

  int target = 6;
  if (list.find(target)) {
    std::cout << "Found 6 in list, removing...\n";
    list.remove(target);
  }
  std::cout << "After removal: ";
  list.showList();
  return 0;
}

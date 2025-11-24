#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T>
class MyStack {
  std::vector<T> data;
  std::size_t cap;

public:
  explicit MyStack(std::size_t n) : cap(n) { data.reserve(n); }

  bool isFull() const { return data.size() >= cap; }
  bool isEmpty() const { return data.empty(); }

  void push(const T &value) {
    if (isFull()) {
      throw std::overflow_error("stack overflow");
    }
    data.push_back(value);
  }

  void pop() {
    if (isEmpty()) {
      throw std::underflow_error("stack underflow");
    }
    data.pop_back();
  }

  T &top() {
    if (isEmpty()) {
      throw std::underflow_error("stack is empty");
    }
    return data.back();
  }
};

int main() {
  MyStack<int> s(5);
  for (int i = 1; i <= 5; ++i) {
    s.push(i * 10);
  }
  std::cout << "Top element: " << s.top() << '\n';
  while (!s.isEmpty()) {
    std::cout << s.top() << ' ';
    s.pop();
  }
  std::cout << '\n';
  return 0;
}

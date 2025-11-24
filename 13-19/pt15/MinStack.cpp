#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

class MinStack {
  std::vector<int> data_;
  std::vector<int> min_history_;

public:
  explicit MinStack(int n) {
    data_.reserve(n);
    min_history_.reserve(n);
  }

  void push(int value) {
    data_.push_back(value);
    if (min_history_.empty()) {
      min_history_.push_back(value);
    } else {
      min_history_.push_back(std::min(value, min_history_.back()));
    }
  }

  void pop() {
    if (data_.empty()) {
      throw std::underflow_error("stack is empty");
    }
    data_.pop_back();
    min_history_.pop_back();
  }

  int top() const {
    if (data_.empty()) {
      throw std::underflow_error("stack is empty");
    }
    return data_.back();
  }

  int min() const {
    if (min_history_.empty()) {
      throw std::underflow_error("stack is empty");
    }
    return min_history_.back();
  }

  bool empty() const { return data_.empty(); }
};

int main() {
  MinStack st(10);
  for (int v : {5, 3, 7, 2, 6}) {
    st.push(v);
    std::cout << "push " << v << ", current min: " << st.min() << '\n';
  }

  while (!st.empty()) {
    std::cout << "pop " << st.top();
    st.pop();
    if (!st.empty()) {
      std::cout << ", new min: " << st.min();
    }
    std::cout << '\n';
  }
  return 0;
}

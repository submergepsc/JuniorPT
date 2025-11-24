#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T>
class Dataable {
public:
  virtual bool isFull() const = 0;
  virtual bool isEmpty() const = 0;
  virtual void addElement(T obj) = 0;
  virtual T removeElement() = 0;
  virtual ~Dataable() = default;
};

template <typename T>
class MyQueue : public Dataable<T> {
  std::unique_ptr<T[]> data;
  int capacity;
  int head;
  int tail;
  int count;

public:
  explicit MyQueue(int cap)
      : data(std::make_unique<T[]>(cap)), capacity(cap), head(0), tail(0),
        count(0) {}

  bool isFull() const override { return count == capacity; }
  bool isEmpty() const override { return count == 0; }

  void addElement(T obj) override {
    if (isFull()) {
      throw std::overflow_error("queue is full");
    }
    data[tail] = obj;
    tail = (tail + 1) % capacity;
    ++count;
  }

  T removeElement() override {
    if (isEmpty()) {
      throw std::underflow_error("queue is empty");
    }
    T value = data[head];
    head = (head + 1) % capacity;
    --count;
    return value;
  }
};

class Student {
  int no;
  std::string name;
  double score;

public:
  Student() : no(1000), name("NULL"), score(0) {}
  Student(int no, std::string name, double score)
      : no(no), name(std::move(name)), score(score) {}

  void show() const {
    std::cout << "学号：" << no << "，姓名：" << name << "，成绩：" << score
              << '\n';
  }
};

int main() {
  Dataable<std::string> *q1 = new MyQueue<std::string>(5);
  for (const auto &s : {"China", "Korea", "Japan", "USA", "Canda"}) {
    q1->addElement(s);
  }
  std::cout << "String queue output in FIFO order:\n";
  while (!q1->isEmpty()) {
    std::cout << q1->removeElement() << '\n';
  }
  delete q1;

  Dataable<Student> *q2 = new MyQueue<Student>(3);
  q2->addElement(Student(1001, "Smith", 78));
  q2->addElement(Student(1005, "Tom", 85));
  q2->addElement(Student(1008, "John", 92));

  std::cout << "\nStudent queue output in FIFO order:\n";
  while (!q2->isEmpty()) {
    Student s = q2->removeElement();
    s.show();
  }
  delete q2;
  return 0;
}

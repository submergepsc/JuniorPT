#include <iostream>
#include <stdexcept>

template <typename T> class DataStore {
  T dataElement[5];
  int loc;

public:
  DataStore() : loc(0) {}

  int Insert(T elt) {
    if (loc >= 5) {
      return 0;
    }
    dataElement[loc++] = elt;
    return 1;
  }

  int Find(T elt) {
    for (int i = 0; i < loc; ++i) {
      if (dataElement[i] == elt) {
        return i;
      }
    }
    return -1;
  }

  int NumElts(void) { return loc; }

  T &GetData(int n) {
    if (n < 0 || n >= loc) {
      throw std::out_of_range("index out of range");
    }
    return dataElement[n];
  }
};

int main() {
  DataStore<int> ds;
  for (int v : {3, 7, 11, 5, 9}) {
    ds.Insert(v);
  }

  std::cout << "Elements in store: " << ds.NumElts() << '\n';
  for (int i = 0; i < ds.NumElts(); ++i) {
    std::cout << ds.GetData(i) << ' ';
  }
  std::cout << "\nFind 11 at index: " << ds.Find(11) << '\n';
  std::cout << "Find 4 at index: " << ds.Find(4) << " (not found returns -1)\n";
  return 0;
}

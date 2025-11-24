#include <iostream>
#include <stdexcept>

class ModClass {
  int dataval;

  static int normalize(int v) {
    v %= 7;
    if (v < 0)
      v += 7;
    return v;
  }

public:
  explicit ModClass(int v = 0) : dataval(normalize(v)) {}

  ModClass operator+(const ModClass &x) const {
    return ModClass(dataval + x.dataval);
  }

  friend ModClass operator*(const ModClass &lhs, const ModClass &rhs) {
    return ModClass(lhs.dataval * rhs.dataval);
  }

  int GetValue() const { return dataval; }

  operator int() const { return dataval; }
};

ModClass Inverse(ModClass &x) {
  for (int v = 1; v <= 6; ++v) {
    ModClass candidate(v);
    if ((candidate * x).GetValue() == 1) {
      return candidate;
    }
  }
  throw std::runtime_error("no inverse exists");
}

void Solve(ModClass a, ModClass &x, ModClass b) {
  if (a.GetValue() == 0) {
    throw std::runtime_error("a is 0, equation has no unique solution");
  }
  ModClass inv = Inverse(a);
  x = inv * b;
}

int main() {
  ModClass a(10), b(6), c;
  c = a + b;
  std::cout << "(10 % 7) + (6 % 7) = " << static_cast<int>(c) << '\n';

  ModClass x;
  Solve(ModClass(3), x, ModClass(5));
  std::cout << "Solve 3 * x = 5 (mod 7), x = " << static_cast<int>(x) << '\n';

  ModClass inv = Inverse(b);
  std::cout << "Inverse of 6 mod 7 is " << static_cast<int>(inv) << '\n';
  return 0;
}

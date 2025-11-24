#include <iostream>
#include <cstring>
#include <stdexcept>

class MyString {
  char *data;
  int len;

  void copy_from(const char *src) {
    len = static_cast<int>(std::strlen(src));
    data = new char[len + 1];
    std::memcpy(data, src, len + 1);
  }

public:
  MyString() : data(nullptr), len(0) { copy_from(""); }

  MyString(const char *d) : data(nullptr), len(0) { copy_from(d ? d : ""); }

  MyString(const MyString &ms) : data(nullptr), len(0) { copy_from(ms.data); }

  ~MyString() { delete[] data; }

  int length() const { return len; }

  void show() const { std::cout << data; }

  MyString &operator=(const MyString &other) {
    if (this != &other) {
      delete[] data;
      copy_from(other.data);
    }
    return *this;
  }

  char &operator[](const int index) {
    if (index < 0 || index >= len) {
      throw std::out_of_range("index out of range");
    }
    return data[index];
  }

  const char &operator[](const int index) const {
    if (index < 0 || index >= len) {
      throw std::out_of_range("index out of range");
    }
    return data[index];
  }

  friend MyString operator+(const MyString &s1, const MyString &s2) {
    MyString result;
    delete[] result.data;
    result.len = s1.len + s2.len;
    result.data = new char[result.len + 1];
    std::memcpy(result.data, s1.data, s1.len);
    std::memcpy(result.data + s1.len, s2.data, s2.len + 1);
    return result;
  }

  friend bool operator==(const MyString &s1, const MyString &s2) {
    return std::strcmp(s1.data, s2.data) == 0;
  }

  friend bool operator!=(const MyString &s1, const MyString &s2) {
    return !(s1 == s2);
  }

  friend bool operator>(const MyString &s1, const MyString &s2) {
    return std::strcmp(s1.data, s2.data) > 0;
  }

  friend bool operator<=(const MyString &s1, const MyString &s2) {
    return std::strcmp(s1.data, s2.data) <= 0;
  }
};

int main() {
  MyString s1("Hello"), s2("World");
  std::cout << "s1: ";
  s1.show();
  std::cout << "\ns2: ";
  s2.show();

  MyString s3 = s1 + MyString(", ") + s2;
  std::cout << "\nconcatenate: ";
  s3.show();

  std::cout << "\nlength of s3: " << s3.length();
  std::cout << "\ncomparison s1 vs s2: " << (s1 > s2 ? ">" : "<=");

  s3[0] = 'h';
  std::cout << "\nmutated s3: ";
  s3.show();
  std::cout << '\n';
  return 0;
}

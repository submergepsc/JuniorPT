#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>

class Matrix {
  int **data;
  int row, col;

  void allocate(int r, int c) {
    row = r;
    col = c;
    data = new int *[row];
    for (int i = 0; i < row; ++i) {
      data[i] = new int[col]{};
    }
  }

  void copy_from(int **d) {
    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < col; ++j) {
        data[i][j] = d[i][j];
      }
    }
  }

public:
  Matrix() : data(nullptr), row(0), col(0) {}

  Matrix(int r, int c) : data(nullptr), row(0), col(0) {
    allocate(r, c);
  }

  Matrix(int **d, int r, int c) : data(nullptr), row(0), col(0) {
    allocate(r, c);
    copy_from(d);
  }

  Matrix(const Matrix &other) : data(nullptr), row(0), col(0) {
    allocate(other.row, other.col);
    copy_from(other.data);
  }

  virtual ~Matrix() {
    for (int i = 0; i < row; ++i) {
      delete[] data[i];
    }
    delete[] data;
  }

  Matrix &operator=(const Matrix &m) {
    if (this != &m) {
      this->~Matrix();
      allocate(m.row, m.col);
      copy_from(m.data);
    }
    return *this;
  }

  Matrix &operator=(int **d) {
    copy_from(d);
    return *this;
  }

  int getRow() const { return row; }
  int getCol() const { return col; }

  int &getElement(int r, int c) {
    if (r < 0 || r >= row || c < 0 || c >= col) {
      throw std::out_of_range("index out of range");
    }
    return data[r][c];
  }

  void print() {
    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < col; ++j) {
        std::cout << std::setw(4) << data[i][j];
      }
      std::cout << '\n';
    }
  }

  friend std::istream &operator>>(std::istream &is, Matrix &m) {
    for (int i = 0; i < m.row; ++i) {
      for (int j = 0; j < m.col; ++j) {
        is >> m.data[i][j];
      }
    }
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, Matrix &m) {
    for (int i = 0; i < m.row; ++i) {
      for (int j = 0; j < m.col; ++j) {
        os << m.data[i][j] << (j + 1 == m.col ? '\n' : ' ');
      }
    }
    return os;
  }

  friend Matrix operator+(const Matrix &m1, const Matrix &m2) {
    if (m1.row != m2.row || m1.col != m2.col) {
      throw std::invalid_argument("size mismatch");
    }
    Matrix res(m1.row, m1.col);
    for (int i = 0; i < res.row; ++i) {
      for (int j = 0; j < res.col; ++j) {
        res.data[i][j] = m1.data[i][j] + m2.data[i][j];
      }
    }
    return res;
  }

  friend Matrix operator-(const Matrix &m1, const Matrix &m2) {
    if (m1.row != m2.row || m1.col != m2.col) {
      throw std::invalid_argument("size mismatch");
    }
    Matrix res(m1.row, m1.col);
    for (int i = 0; i < res.row; ++i) {
      for (int j = 0; j < res.col; ++j) {
        res.data[i][j] = m1.data[i][j] - m2.data[i][j];
      }
    }
    return res;
  }

  Matrix &operator+=(const Matrix &b) {
    *this = *this + b;
    return *this;
  }

  Matrix &operator-=(const Matrix &b) {
    *this = *this - b;
    return *this;
  }

  Matrix transpose() const {
    Matrix t(col, row);
    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < col; ++j) {
        t.data[j][i] = data[i][j];
      }
    }
    return t;
  }

  bool isTriangular() {
    for (int i = 1; i < row; ++i) {
      for (int j = 0; j < i && j < col; ++j) {
        if (data[i][j] != 0) {
          return false;
        }
      }
    }
    return true;
  }

  void add(Matrix b) { *this += b; }
  Matrix plus(Matrix b) { return *this + b; }
};

int main() {
  Matrix a(2, 2), b(2, 2);
  std::cout << "Enter matrix A (2x2):\n";
  std::cin >> a;
  std::cout << "Enter matrix B (2x2):\n";
  std::cin >> b;

  Matrix c = a + b;
  std::cout << "A + B:\n";
  std::cout << c;

  Matrix d = a - b;
  std::cout << "A - B:\n";
  std::cout << d;

  Matrix t = a.transpose();
  std::cout << "Transpose of A:\n";
  std::cout << t;

  std::cout << "A is upper triangular? " << (a.isTriangular() ? "Yes" : "No")
            << '\n';
  return 0;
}

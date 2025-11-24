#include <cctype>
#include <functional>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>

int precedence(char op) {
  if (op == '+' || op == '-')
    return 1;
  if (op == '*' || op == '/')
    return 2;
  return 0;
}

int applyOp(int a, int b, char op) {
  switch (op) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    if (b == 0)
      throw std::runtime_error("division by zero");
    return a / b;
  default:
    throw std::runtime_error("invalid operator");
  }
}

int evaluateExpression(const std::string &expr) {
  std::stack<int> values;
  std::stack<char> ops;
  std::size_t i = 0;
  while (i < expr.size()) {
    if (std::isspace(static_cast<unsigned char>(expr[i]))) {
      ++i;
      continue;
    }
    if (std::isdigit(static_cast<unsigned char>(expr[i]))) {
      int value = 0;
      while (i < expr.size() && std::isdigit(static_cast<unsigned char>(expr[i]))) {
        value = value * 10 + (expr[i] - '0');
        ++i;
      }
      values.push(value);
      continue;
    }
    char op = expr[i];
    if (op == '=') {
      ++i;
      break;
    }
    while (!ops.empty() && precedence(ops.top()) >= precedence(op)) {
      int b = values.top();
      values.pop();
      int a = values.top();
      values.pop();
      char topOp = ops.top();
      ops.pop();
      values.push(applyOp(a, b, topOp));
    }
    ops.push(op);
    ++i;
  }

  while (!ops.empty()) {
    int b = values.top();
    values.pop();
    int a = values.top();
    values.pop();
    char op = ops.top();
    ops.pop();
    values.push(applyOp(a, b, op));
  }

  if (values.empty()) {
    throw std::runtime_error("no result");
  }
  return values.top();
}

int main() {
  std::cout << "请输入表达式（以=结束，例如 a+b*c-d/e=）：";
  std::string expr;
  std::getline(std::cin, expr);
  try {
    int result = evaluateExpression(expr);
    std::cout << "结果：" << result << '\n';
  } catch (const std::exception &e) {
    std::cerr << "计算错误: " << e.what() << '\n';
  }
  return 0;
}

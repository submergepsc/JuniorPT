#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Employee {
  int id;
  std::string name;
  int age;
  double salary;
};

int main() {
  std::vector<Employee> employees = {
      {1001, "Alice", 28, 12000}, {1002, "Bob", 32, 13000},
      {1003, "Carol", 30, 11000}, {1004, "David", 35, 15000},
      {1005, "Eve", 29, 12500}};

  std::sort(employees.begin(), employees.end(),
            [](const Employee &a, const Employee &b) { return a.id < b.id; });

  std::ofstream ofs("employees.txt");
  for (const auto &e : employees) {
    ofs << e.id << ' ' << e.name << ' ' << e.age << ' ' << e.salary << '\n';
  }
  ofs.close();

  std::cout << "请输入两条新员工记录(编号 姓名 年龄 薪资)，编号需大于现有编号：\n";
  for (int i = 0; i < 2; ++i) {
    Employee e{};
    std::cin >> e.id >> e.name >> e.age >> e.salary;
    employees.push_back(e);
  }

  std::ofstream ofs_append("employees.txt", std::ios::app);
  for (std::size_t i = 5; i < employees.size(); ++i) {
    const auto &e = employees[i];
    ofs_append << e.id << ' ' << e.name << ' ' << e.age << ' ' << e.salary
               << '\n';
  }
  ofs_append.close();

  std::cout << "\n文件中所有职工数据：\n";
  std::ifstream ifs("employees.txt");
  std::vector<Employee> loaded;
  Employee e{};
  while (ifs >> e.id >> e.name >> e.age >> e.salary) {
    loaded.push_back(e);
  }
  ifs.close();
  for (std::size_t i = 0; i < loaded.size(); ++i) {
    const auto &emp = loaded[i];
    std::cout << i + 1 << ": " << emp.id << ' ' << emp.name << ' ' << emp.age
              << ' ' << emp.salary << '\n';
  }

  while (true) {
    std::cout << "\n请输入要查询的职工号(输入0结束)：";
    int target;
    std::cin >> target;
    if (target == 0) {
      break;
    }
    auto it = std::find_if(loaded.begin(), loaded.end(),
                           [target](const Employee &emp) {
                             return emp.id == target;
                           });
    if (it == loaded.end()) {
      std::cout << "无此人\n";
    } else {
      auto idx = std::distance(loaded.begin(), it);
      std::cout << "第" << idx + 1 << "个职工：" << it->id << ' ' << it->name
                << ' ' << it->age << ' ' << it->salary << '\n';
    }
  }

  return 0;
}

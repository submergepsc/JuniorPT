#include "payroll_system.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

namespace {
std::string readNonEmptyLine(const std::string &prompt) {
    while (true) {
        std::cout << prompt;
        std::string value;
        std::getline(std::cin, value);
        if (!value.empty()) {
            return value;
        }
        std::cout << "输入不能为空，请重新输入。\n";
    }
}

double readNonNegativeDouble(const std::string &prompt) {
    while (true) {
        std::cout << prompt;
        double value = 0.0;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (value >= 0.0) {
                return value;
            }
            std::cout << "值不能为负，请重新输入。\n";
        } else {
            std::cout << "输入无效，请输入数字。\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

double readPositiveDouble(const std::string &prompt) {
    while (true) {
        std::cout << prompt;
        double value = 0.0;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (value > 0.0) {
                return value;
            }
            std::cout << "值必须大于 0，请重新输入。\n";
        } else {
            std::cout << "输入无效，请输入数字。\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int readIntInRange(const std::string &prompt, int minValue, int maxValue) {
    while (true) {
        std::cout << prompt;
        int value = 0;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (value >= minValue && value <= maxValue) {
                return value;
            }
            std::cout << "输入超出范围，请输入 " << minValue << " 到 " << maxValue << " 之间的数字。\n";
        } else {
            std::cout << "输入无效，请输入数字。\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void printMenu(const PayrollSystem &system) {
    std::cout << "\n=========== 公司人员薪酬管理系统 ===========\n"
              << "当前员工数量：" << system.employees().size() << "\n"
              << "1. 添加经理\n"
              << "2. 添加技术人员\n"
              << "3. 添加推销员\n"
              << "4. 添加销售经理\n"
              << "5. 结算本月薪资\n"
              << "6. 查看薪资报表\n"
              << "0. 退出系统\n"
              << "==========================================\n";
}

void handleAddEmployee(PayrollSystem &system, int type) {
    std::string name = readNonEmptyLine("请输入姓名：");
    Person *person = nullptr;

    switch (type) {
    case 1: {
        person = system.addManager(name);
        break;
    }
    case 2: {
        double hourlyRate = readPositiveDouble("请输入时薪（元/小时）：");
        double hoursWorked = readNonNegativeDouble("请输入当前累计工时（如暂无可输入 0）：");
        auto *technician = system.addTechnician(name, hourlyRate, hoursWorked);
        person = technician;
        break;
    }
    case 3: {
        double salesAmount = readNonNegativeDouble("请输入当前销售额（如暂无可输入 0）：");
        auto *salesperson = system.addSalesperson(name, salesAmount);
        person = salesperson;
        break;
    }
    case 4: {
        double departmentSales = readNonNegativeDouble("请输入当前部门销售总额（如暂无可输入 0）：");
        auto *salesManager = system.addSalesManager(name, departmentSales);
        person = salesManager;
        break;
    }
    default:
        std::cout << "未识别的员工类型，取消新增操作。\n";
        return;
    }

    if (!person) {
        std::cout << "新增员工失败，请重试。\n";
        return;
    }

    system.saveRecords();
    std::cout << "已添加员工：" << person->name() << " (" << person->roleName() << ", 工号"
              << person->id() << ")\n";
}

void capturePayrollDetails(Person &person) {
    if (auto *technician = dynamic_cast<Technician *>(&person)) {
        std::cout << "当前时薪：" << std::fixed << std::setprecision(2) << technician->hourlyRate()
                  << " 元/小时\n";
        double hours = readNonNegativeDouble("请输入本月工作小时数：");
        technician->setHoursWorked(hours);
    } else if (auto *salesperson = dynamic_cast<Salesperson *>(&person)) {
        double sales = readNonNegativeDouble("请输入本月销售额：");
        salesperson->setSalesAmount(sales);
    } else if (auto *salesManager = dynamic_cast<SalesManager *>(&person)) {
        double sales = readNonNegativeDouble("请输入本月部门销售总额：");
        salesManager->setDepartmentSales(sales);
    }
}

void settlePayroll(PayrollSystem &system) {
    auto &list = system.employees();
    if (list.empty()) {
        std::cout << "暂无员工信息，请先录入员工。\n";
        return;
    }

    std::cout << "\n------------- 薪资结算 -------------\n";
    double total = 0.0;
    for (auto &employee : list) {
        Person &person = *employee;
        std::cout << "\n[" << person.roleName() << "] " << person.name() << " (工号" << person.id()
                  << ")\n";
        capturePayrollDetails(person);
        double pay = system.processPayroll(person);
        std::cout << "本月薪资：" << std::fixed << std::setprecision(2) << pay << " 元\n";
        total += pay;
    }

    system.saveRecords();
    std::cout << "\n本月薪资结算完成，总支出：" << std::fixed << std::setprecision(2) << total << " 元\n";
}

void showPayroll(const PayrollSystem &system) {
    const auto &list = system.employees();
    if (list.empty()) {
        std::cout << "暂无员工信息。\n";
        return;
    }

    std::cout << "\n----------------- 薪资报表 -----------------\n"
              << std::left << std::setw(8) << "工号" << std::setw(10) << "姓名" << std::setw(12)
              << "角色" << std::setw(8) << "级别" << std::right << std::setw(12) << "最近薪资"
              << "\n"
              << "-------------------------------------------\n";

    for (const auto &employee : list) {
        const Person &person = *employee;
        std::cout << std::left << std::setw(8) << person.id() << std::setw(10) << person.name()
                  << std::setw(12) << person.roleName() << std::setw(8) << person.levelLabel()
                  << std::right << std::setw(12) << std::fixed << std::setprecision(2)
                  << person.lastPay() << "\n";
    }
    std::cout << "-------------------------------------------\n"
              << "提示：若薪资为 0，请先执行结算功能。\n";
}
} // namespace

int main() {
    PayrollSystem system;

    while (true) {
        printMenu(system);
        int choice = readIntInRange("请选择操作：", 0, 6);

        switch (choice) {
        case 0:
            system.saveRecords();
            std::cout << "程序结束，感谢使用！\n";
            return 0;
        case 1:
        case 2:
        case 3:
        case 4:
            handleAddEmployee(system, choice);
            break;
        case 5:
            settlePayroll(system);
            break;
        case 6:
            showPayroll(system);
            break;
        default:
            break;
        }
    }
}

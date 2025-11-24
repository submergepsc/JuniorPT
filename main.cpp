#include "payroll_system.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

string readNonEmptyLine(const string &prompt) {
    while (true) {
        cout << prompt;
        string value;
        getline(cin, value);
        if (!value.empty()) {
            return value;
        }
        cout << "输入不能为空，请重新输入。\n";
    }
}

double readNonNegativeDouble(const string &prompt) {
    while (true) {
        cout << prompt;
        double value = 0.0;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= 0.0) {
                return value;
            }
            cout << "值不能为负，请重新输入。\n";
        } else {
            cout << "输入无效，请输入数字。\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

double readPositiveDouble(const string &prompt) {
    while (true) {
        cout << prompt;
        double value = 0.0;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value > 0.0) {
                return value;
            }
            cout << "值必须大于 0，请重新输入。\n";
        } else {
            cout << "输入无效，请输入数字。\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int readIntInRange(const string &prompt, int minValue, int maxValue) {
    while (true) {
        cout << prompt;
        int value = 0;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= minValue && value <= maxValue) {
                return value;
            }
            cout << "输入超出范围，请输入 " << minValue << " 到 " << maxValue << " 之间的数字。\n";
        } else {
            cout << "输入无效，请输入数字。\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void printMenu(const PayrollSystem &system) {
    cout << "\n=========== 公司人员薪酬管理系统 ===========\n"
         << "当前员工数量：" << system.getEmployees().size() << "\n"
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
    string name = readNonEmptyLine("请输入姓名：");
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
        cout << "未识别的员工类型，取消新增操作。\n";
        return;
    }

    if (!person) {
        cout << "新增员工失败，请重试。\n";
        return;
    }

    system.saveRecords();
    cout << "已添加员工：" << person->getName() << " (" << person->getRoleName() << ", 工号" << person->getId()
         << ")\n";
}

void capturePayrollDetails(Person &person) {
    if (auto *technician = dynamic_cast<Technician *>(&person)) {
        cout << "当前时薪：" << fixed << setprecision(2) << technician->getHourlyRate() << " 元/小时\n";
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
    auto &list = system.getEmployees();
    if (list.empty()) {
        cout << "暂无员工信息，请先录入员工。\n";
        return;
    }

    cout << "\n------------- 薪资结算 -------------\n";
    double total = 0.0;
    for (auto employee : list) {
        Person &person = *employee;
        cout << "\n[" << person.getRoleName() << "] " << person.getName() << " (工号" << person.getId() << ")\n";
        capturePayrollDetails(person);
        double pay = system.processPayroll(person);
        cout << "本月薪资：" << fixed << setprecision(2) << pay << " 元\n";
        total += pay;
    }

    system.saveRecords();
    cout << "\n本月薪资结算完成，总支出：" << fixed << setprecision(2) << total << " 元\n";
}

void showPayroll(const PayrollSystem &system) {
    const auto &list = system.getEmployees();
    if (list.empty()) {
        cout << "暂无员工信息。\n";
        return;
    }

    cout << "\n----------------- 薪资报表 -----------------\n"
         << left << setw(8) << "工号" << setw(10) << "姓名" << setw(12) << "角色" << setw(8) << "级别"
         << right << setw(12) << "最近薪资" << "\n"
         << "-------------------------------------------\n";

    for (const auto employee : list) {
        const Person &person = *employee;
        cout << left << setw(8) << person.getId() << setw(10) << person.getName() << setw(12)
             << person.getRoleName() << setw(8) << person.getLevelLabel() << right << setw(12) << fixed
             << setprecision(2) << person.getSalary() << "\n";
    }
    cout << "-------------------------------------------\n" << "提示：若薪资为 0，请先执行结算功能。\n";
}

int main() {
    PayrollSystem system;

    while (true) {
        printMenu(system);
        int choice = readIntInRange("请选择操作：", 0, 6);

        switch (choice) {
        case 0:
            system.saveRecords();
            cout << "程序结束，感谢使用！\n";
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

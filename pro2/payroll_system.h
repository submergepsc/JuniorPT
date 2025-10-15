#ifndef PAYROLL_SYSTEM_H
#define PAYROLL_SYSTEM_H

#include <iomanip>
#include <iosfwd>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace std;

inline double readNonNegativeDouble(istream &in, ostream &out, const string &prompt) {
    while (true) {
        out << prompt;
        double value = 0.0;
        if (in >> value) {
            if (value >= 0.0) {
                in.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
            out << "值不能为负，请重新输入。\n";
        } else {
            out << "输入无效，请输入数字。\n";
            in.clear();
        }
        in.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

inline string readName(istream &in, ostream &out) {
    while (true) {
        out << "请输入姓名：";
        string name;
        getline(in, name);
        if (!name.empty()) {
            return name;
        }
        out << "姓名不能为空，请重新输入。\n";
    }
}

class Person {
public:
    Person(int id, string name, int level)
        : id_(id), name_(move(name)), level_(level), lastPay_(0.0) {}

    virtual ~Person() = default;

    int getId() const noexcept { return id_; }

    const string &getName() const noexcept { return name_; }

    int getLevel() const noexcept { return level_; }

    double getLastPay() const noexcept { return lastPay_; }

    string getLevelLabel() const { return to_string(level_) + "级"; }

    void captureDetails(istream &in, ostream &out) {
        lastPay_ = 0.0;
        readExtraInfo(in, out);
    }

    double processPayroll() {
        lastPay_ = computePay();
        return lastPay_;
    }

    virtual string roleName() const = 0;

protected:
    virtual void readExtraInfo(istream &in, ostream &out) = 0;
    virtual double computePay() const = 0;

private:
    int id_;
    string name_;
    int level_;
    double lastPay_;
};

class Manager : public Person {
public:
    explicit Manager(int id, const string &name)
        : Person(id, name, 4) {}

    string roleName() const override { return "经理"; }

protected:
    void readExtraInfo(istream &, ostream &) override {}
    double computePay() const override { return 18000.0; }
};

class Technician : public Person {
public:
    Technician(int id, const string &name, double hourlyRate = 100.0)
        : Person(id, name, 3), hourlyRate_(hourlyRate), hoursWorked_(0.0) {}

    string roleName() const override { return "技术人员"; }

protected:
    void readExtraInfo(istream &in, ostream &out) override {
        hoursWorked_ = readNonNegativeDouble(in, out, "请输入本月工作小时数：");
    }

    double computePay() const override { return hourlyRate_ * hoursWorked_; }

private:
    double hourlyRate_;
    double hoursWorked_;
};

class Salesperson : public Person {
public:
    explicit Salesperson(int id, const string &name)
        : Person(id, name, 1), salesAmount_(0.0) {}

    string roleName() const override { return "推销员"; }

protected:
    void readExtraInfo(istream &in, ostream &out) override {
        salesAmount_ = readNonNegativeDouble(in, out, "请输入本月销售额：");
    }

    double computePay() const override { return salesAmount_ * 0.04; }

private:
    double salesAmount_;
};

class SalesManager : public Person {
public:
    explicit SalesManager(int id, const string &name)
        : Person(id, name, 2), departmentSales_(0.0) {}

    string roleName() const override { return "销售经理"; }

protected:
    void readExtraInfo(istream &in, ostream &out) override {
        departmentSales_ = readNonNegativeDouble(in, out, "请输入本月部门销售总额：");
    }

    double computePay() const override { return 5000.0 + departmentSales_ * 0.02; }

private:
    double departmentSales_;
};

class PayrollSystem {
public:
    PayrollSystem() : nextId_(2001) {}

    void run();

private:
    void showMenu(ostream &out) const;
    void handleAddEmployee(istream &in, ostream &out);
    void handleProcessPayroll(ostream &out);
    void handleShowPayroll(ostream &out) const;
    unique_ptr<Person> createEmployee(int choice, istream &in, ostream &out);

    int nextId_;
    vector<unique_ptr<Person>> employees_;
};

inline void PayrollSystem::run() {
    auto &in = cin;
    auto &out = cout;

    while (true) {
        showMenu(out);
        int choice = -1;
        if (!(in >> choice)) {
            out << "输入无效，请输入数字指令。\n";
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 0:
            out << "程序结束，感谢使用！\n";
            return;
        case 1:
        case 2:
        case 3:
        case 4:
            handleAddEmployee(in, out);
            break;
        case 5:
            handleProcessPayroll(out);
            break;
        case 6:
            handleShowPayroll(out);
            break;
        default:
            out << "未识别的指令，请重新选择。\n";
            break;
        }
    }
}

inline void PayrollSystem::showMenu(ostream &out) const {
    out << "\n=========== 公司人员薪酬管理系统 ===========\n"
        << "当前员工数量：" << employees_.size() << "\n"
        << "1. 添加经理\n"
        << "2. 添加技术人员\n"
        << "3. 添加推销员\n"
        << "4. 添加销售经理\n"
        << "5. 结算本月薪资\n"
        << "6. 查看薪资报表\n"
        << "0. 退出系统\n"
        << "==========================================\n"
        << "请选择操作：";
}

inline void PayrollSystem::handleAddEmployee(istream &in, ostream &out) {
    out << "请选择员工类型 (1-经理, 2-技术人员, 3-推销员, 4-销售经理)：";
    int type = 0;
    if (!(in >> type)) {
        out << "输入无效，取消新增操作。\n";
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    in.ignore(numeric_limits<streamsize>::max(), '\n');

    auto employee = createEmployee(type, in, out);
    if (!employee) {
        out << "未创建员工。\n";
        return;
    }
    employee->captureDetails(in, out);
    out << "已添加员工：" << employee->getName() << " (" << employee->roleName()
        << ", 工号" << employee->getId() << ")\n";
    employees_.push_back(move(employee));
}

inline void PayrollSystem::handleProcessPayroll(ostream &out) {
    if (employees_.empty()) {
        out << "暂无员工信息，请先录入员工。\n";
        return;
    }

    double total = 0.0;
    for (auto &employee : employees_) {
        total += employee->processPayroll();
    }
    out << "本月薪资结算完成，总支出：" << fixed << setprecision(2) << total << " 元\n";
}

inline void PayrollSystem::handleShowPayroll(ostream &out) const {
    if (employees_.empty()) {
        out << "暂无员工信息。\n";
        return;
    }

    out << "\n----------------- 薪资报表 -----------------\n"
        << left << setw(8) << "工号" << setw(8) << "姓名" << setw(10) << "角色"
        << setw(8) << "级别" << right << setw(12) << "最近薪资" << "\n"
        << "-------------------------------------------\n";

    for (const auto &employee : employees_) {
        out << left << setw(8) << employee->getId() << setw(8) << employee->getName()
            << setw(10) << employee->roleName() << setw(8) << employee->getLevelLabel()
            << right << setw(12) << fixed << setprecision(2) << employee->getLastPay()
            << "\n";
    }
    out << "-------------------------------------------\n"
        << "提示：若薪资为 0，请先执行结算功能。\n";
}

inline unique_ptr<Person> PayrollSystem::createEmployee(int choice, istream &in, ostream &out) {
    if (choice < 1 || choice > 4) {
        out << "未识别的员工类型。\n";
        return nullptr;
    }

    out << "正在创建第" << employees_.size() + 1 << "位员工 (工号" << nextId_ << ")。\n";
    string name = readName(in, out);

    unique_ptr<Person> employee;
    switch (choice) {
    case 1:
        employee = make_unique<Manager>(nextId_, name);
        break;
    case 2:
        employee = make_unique<Technician>(nextId_, name);
        break;
    case 3:
        employee = make_unique<Salesperson>(nextId_, name);
        break;
    case 4:
        employee = make_unique<SalesManager>(nextId_, name);
        break;
    default:
        return nullptr;
    }

    ++nextId_;
    return employee;
}

#endif // PAYROLL_SYSTEM_H

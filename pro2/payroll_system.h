#ifndef PAYROLL_SYSTEM_H
#define PAYROLL_SYSTEM_H

#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person(int id, string name, int level);
    virtual ~Person();

    int getId() const noexcept;
    const string &getName() const noexcept;
    int getLevel() const noexcept;
    double getLastPay() const noexcept;
    string getLevelLabel() const;

    void captureDetails(istream &in, ostream &out);
    double processPayroll();

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
    explicit Manager(int id, const string &name);

    string roleName() const override;

protected:
    void readExtraInfo(istream &in, ostream &out) override;
    double computePay() const override;
};

class Technician : public Person {
public:
    Technician(int id, const string &name, double hourlyRate = 100.0);

    string roleName() const override;

protected:
    void readExtraInfo(istream &in, ostream &out) override;
    double computePay() const override;

private:
    double hourlyRate_;
    double hoursWorked_;
};

class Salesperson : public Person {
public:
    explicit Salesperson(int id, const string &name);

    string roleName() const override;

protected:
    void readExtraInfo(istream &in, ostream &out) override;
    double computePay() const override;

private:
    double salesAmount_;
};

class SalesManager : public Person {
public:
    explicit SalesManager(int id, const string &name);

    string roleName() const override;

protected:
    void readExtraInfo(istream &in, ostream &out) override;
    double computePay() const override;

private:
    double departmentSales_;
};

class PayrollSystem {
public:
    PayrollSystem();
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

#endif // PAYROLL_SYSTEM_H

#ifndef PAYROLL_SYSTEM_H
#define PAYROLL_SYSTEM_H

#include <fstream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class Person {
public:
    Person(int id, std::string name, int level);
    virtual ~Person() = default;

    int id() const noexcept;
    const std::string &name() const noexcept;
    int level() const noexcept;
    double lastPay() const noexcept;
    std::string levelLabel() const;

    double processPayroll();
    void restoreLastPay(double value);

    virtual std::string roleName() const = 0;
    virtual std::string typeCode() const = 0;

    virtual void writeExtra(std::ostream &out) const = 0;
    virtual void readExtra(std::istream &in) = 0;

protected:
    virtual double computePay() const = 0;

private:
    int id_;
    std::string name_;
    int level_;
    double lastPay_;
};

class Manager : public Person {
public:
    Manager(int id, std::string name);

    std::string roleName() const override;
    std::string typeCode() const override;

    void writeExtra(std::ostream &out) const override;
    void readExtra(std::istream &in) override;

protected:
    double computePay() const override;
};

class Technician : public Person {
public:
    Technician(int id, std::string name, double hourlyRate = 100.0, double hoursWorked = 0.0);

    double hourlyRate() const noexcept;
    double hoursWorked() const noexcept;
    void setHourlyRate(double rate);
    void setHoursWorked(double hours);

    std::string roleName() const override;
    std::string typeCode() const override;

    void writeExtra(std::ostream &out) const override;
    void readExtra(std::istream &in) override;

protected:
    double computePay() const override;

private:
    double hourlyRate_;
    double hoursWorked_;
};

class Salesperson : public Person {
public:
    Salesperson(int id, std::string name, double salesAmount = 0.0);

    double salesAmount() const noexcept;
    void setSalesAmount(double amount);

    std::string roleName() const override;
    std::string typeCode() const override;

    void writeExtra(std::ostream &out) const override;
    void readExtra(std::istream &in) override;

protected:
    double computePay() const override;

private:
    double salesAmount_;
};

class SalesManager : public Person {
public:
    SalesManager(int id, std::string name, double departmentSales = 0.0);

    double departmentSales() const noexcept;
    void setDepartmentSales(double amount);

    std::string roleName() const override;
    std::string typeCode() const override;

    void writeExtra(std::ostream &out) const override;
    void readExtra(std::istream &in) override;

protected:
    double computePay() const override;

private:
    double departmentSales_;
};

class PayrollSystem {
public:
    static std::string defaultRecordPath();

    explicit PayrollSystem(std::string recordPath = defaultRecordPath());

    const std::string &recordPath() const noexcept;
    void setRecordPath(std::string path);

    Manager *addManager(const std::string &name);
    Technician *addTechnician(const std::string &name, double hourlyRate, double hoursWorked);
    Salesperson *addSalesperson(const std::string &name, double salesAmount);
    SalesManager *addSalesManager(const std::string &name, double departmentSales);

    std::vector<std::unique_ptr<Person>> &employees() noexcept;
    const std::vector<std::unique_ptr<Person>> &employees() const noexcept;

    Person *findById(int id) noexcept;
    const Person *findById(int id) const noexcept;

    double processPayroll(Person &person);
    double processAllPayrolls();

    void loadRecords();
    void saveRecords() const;

    int nextId() const noexcept;

private:
    template <typename T, typename... Args>
    T *emplaceEmployee(Args &&...args);

    std::unique_ptr<Person> recreateEmployee(const std::string &type, int id, const std::string &name) const;

    int nextId_;
    std::vector<std::unique_ptr<Person>> employees_;
    std::string recordPath_;
};

inline Person::Person(int id, std::string name, int level)
    : id_(id), name_(std::move(name)), level_(level), lastPay_(0.0) {}

inline int Person::id() const noexcept { return id_; }

inline const std::string &Person::name() const noexcept { return name_; }

inline int Person::level() const noexcept { return level_; }

inline double Person::lastPay() const noexcept { return lastPay_; }

inline std::string Person::levelLabel() const { return std::to_string(level_) + "级"; }

inline double Person::processPayroll() {
    lastPay_ = computePay();
    return lastPay_;
}

inline void Person::restoreLastPay(double value) { lastPay_ = value; }

inline Manager::Manager(int id, std::string name)
    : Person(id, std::move(name), 4) {}

inline std::string Manager::roleName() const { return "经理"; }

inline std::string Manager::typeCode() const { return "Manager"; }

inline void Manager::writeExtra(std::ostream &out) const { (void)out; }

inline void Manager::readExtra(std::istream &in) { (void)in; }

inline double Manager::computePay() const { return 18000.0; }

inline Technician::Technician(int id, std::string name, double hourlyRate, double hoursWorked)
    : Person(id, std::move(name), 3), hourlyRate_(hourlyRate), hoursWorked_(hoursWorked) {}

inline double Technician::hourlyRate() const noexcept { return hourlyRate_; }

inline double Technician::hoursWorked() const noexcept { return hoursWorked_; }

inline void Technician::setHourlyRate(double rate) { hourlyRate_ = rate; }

inline void Technician::setHoursWorked(double hours) { hoursWorked_ = hours; }

inline std::string Technician::roleName() const { return "技术人员"; }

inline std::string Technician::typeCode() const { return "Technician"; }

inline void Technician::writeExtra(std::ostream &out) const { out << hourlyRate_ << ' ' << hoursWorked_; }

inline void Technician::readExtra(std::istream &in) {
    double rate = hourlyRate_;
    double hours = hoursWorked_;
    if (in >> rate) {
        if (!(in >> hours)) {
            hours = 0.0;
        }
        hourlyRate_ = rate;
        hoursWorked_ = hours;
    } else {
        hourlyRate_ = 100.0;
        hoursWorked_ = 0.0;
    }
}

inline double Technician::computePay() const { return hourlyRate_ * hoursWorked_; }

inline Salesperson::Salesperson(int id, std::string name, double salesAmount)
    : Person(id, std::move(name), 1), salesAmount_(salesAmount) {}

inline double Salesperson::salesAmount() const noexcept { return salesAmount_; }

inline void Salesperson::setSalesAmount(double amount) { salesAmount_ = amount; }

inline std::string Salesperson::roleName() const { return "推销员"; }

inline std::string Salesperson::typeCode() const { return "Salesperson"; }

inline void Salesperson::writeExtra(std::ostream &out) const { out << salesAmount_; }

inline void Salesperson::readExtra(std::istream &in) {
    double value = salesAmount_;
    if (in >> value) {
        salesAmount_ = value;
    } else {
        salesAmount_ = 0.0;
    }
}

inline double Salesperson::computePay() const { return salesAmount_ * 0.04; }

inline SalesManager::SalesManager(int id, std::string name, double departmentSales)
    : Person(id, std::move(name), 2), departmentSales_(departmentSales) {}

inline double SalesManager::departmentSales() const noexcept { return departmentSales_; }

inline void SalesManager::setDepartmentSales(double amount) { departmentSales_ = amount; }

inline std::string SalesManager::roleName() const { return "销售经理"; }

inline std::string SalesManager::typeCode() const { return "SalesManager"; }

inline void SalesManager::writeExtra(std::ostream &out) const { out << departmentSales_; }

inline void SalesManager::readExtra(std::istream &in) {
    double value = departmentSales_;
    if (in >> value) {
        departmentSales_ = value;
    } else {
        departmentSales_ = 0.0;
    }
}

inline double SalesManager::computePay() const { return 5000.0 + departmentSales_ * 0.02; }

inline std::string PayrollSystem::defaultRecordPath() { return "record.txt"; }

inline PayrollSystem::PayrollSystem(std::string recordPath)
    : nextId_(2001), recordPath_(std::move(recordPath)) {
    loadRecords();
}

inline const std::string &PayrollSystem::recordPath() const noexcept { return recordPath_; }

inline void PayrollSystem::setRecordPath(std::string path) {
    recordPath_ = std::move(path);
}

inline Manager *PayrollSystem::addManager(const std::string &name) {
    return emplaceEmployee<Manager>(name);
}

inline Technician *PayrollSystem::addTechnician(const std::string &name, double hourlyRate, double hoursWorked) {
    return emplaceEmployee<Technician>(name, hourlyRate, hoursWorked);
}

inline Salesperson *PayrollSystem::addSalesperson(const std::string &name, double salesAmount) {
    return emplaceEmployee<Salesperson>(name, salesAmount);
}

inline SalesManager *PayrollSystem::addSalesManager(const std::string &name, double departmentSales) {
    return emplaceEmployee<SalesManager>(name, departmentSales);
}

inline std::vector<std::unique_ptr<Person>> &PayrollSystem::employees() noexcept { return employees_; }

inline const std::vector<std::unique_ptr<Person>> &PayrollSystem::employees() const noexcept { return employees_; }

inline Person *PayrollSystem::findById(int id) noexcept {
    for (auto &employee : employees_) {
        if (employee->id() == id) {
            return employee.get();
        }
    }
    return nullptr;
}

inline const Person *PayrollSystem::findById(int id) const noexcept {
    for (const auto &employee : employees_) {
        if (employee->id() == id) {
            return employee.get();
        }
    }
    return nullptr;
}

inline double PayrollSystem::processPayroll(Person &person) { return person.processPayroll(); }

inline double PayrollSystem::processAllPayrolls() {
    double total = 0.0;
    for (auto &employee : employees_) {
        total += employee->processPayroll();
    }
    return total;
}

inline void PayrollSystem::loadRecords() {
    employees_.clear();
    if (recordPath_.empty()) {
        return;
    }

    std::ifstream file(recordPath_);
    if (!file.is_open()) {
        return;
    }

    int storedNextId = nextId_;
    if (!(file >> storedNextId)) {
        return;
    }

    int recordCount = 0;
    if (!(file >> recordCount)) {
        return;
    }
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    nextId_ = storedNextId;
    for (int i = 0; i < recordCount; ++i) {
        std::string type;
        if (!(file >> type)) {
            break;
        }
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        int id = 0;
        if (!(file >> id)) {
            break;
        }
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string name;
        if (!std::getline(file, name)) {
            break;
        }

        double lastPay = 0.0;
        if (!(file >> lastPay)) {
            break;
        }
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string extraLine;
        if (!std::getline(file, extraLine)) {
            extraLine.clear();
        }

        auto employee = recreateEmployee(type, id, name);
        if (!employee) {
            continue;
        }
        employee->restoreLastPay(lastPay);
        std::istringstream extraStream(extraLine);
        employee->readExtra(extraStream);
        if (id >= nextId_) {
            nextId_ = id + 1;
        }
        employees_.push_back(std::move(employee));
    }
}

inline void PayrollSystem::saveRecords() const {
    if (recordPath_.empty()) {
        return;
    }

    std::ofstream file(recordPath_);
    if (!file.is_open()) {
        return;
    }

    file << nextId_ << '\n';
    file << employees_.size() << '\n';
    for (const auto &employee : employees_) {
        file << employee->typeCode() << '\n';
        file << employee->id() << '\n';
        file << employee->name() << '\n';
        file << employee->lastPay() << '\n';
        employee->writeExtra(file);
        file << '\n';
    }
}

inline int PayrollSystem::nextId() const noexcept { return nextId_; }

template <typename T, typename... Args>
inline T *PayrollSystem::emplaceEmployee(Args &&...args) {
    auto employee = std::make_unique<T>(nextId_, std::forward<Args>(args)...);
    T *raw = employee.get();
    employees_.push_back(std::move(employee));
    ++nextId_;
    return raw;
}

inline std::unique_ptr<Person> PayrollSystem::recreateEmployee(const std::string &type, int id, const std::string &name) const {
    if (type == "Manager") {
        return std::make_unique<Manager>(id, name);
    }
    if (type == "Technician") {
        return std::make_unique<Technician>(id, name);
    }
    if (type == "Salesperson") {
        return std::make_unique<Salesperson>(id, name);
    }
    if (type == "SalesManager") {
        return std::make_unique<SalesManager>(id, name);
    }
    return nullptr;
}

#endif // PAYROLL_SYSTEM_H

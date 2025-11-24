#ifndef PAYROLL_SYSTEM_H
#define PAYROLL_SYSTEM_H

#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person(string name, int level);
    virtual ~Person() = default;
    
    int getId() const;
    string getName() const;
    int getLevel() const;
    double getSalary() const;
    string getLevelLabel() const;
    void setLevel(int level);
    
    virtual void pay() = 0;
    virtual string getRoleName() const = 0;
    virtual string getTypeCode() const = 0;
    virtual void writeExtra(ostream &out) const = 0;
    virtual void readExtra(istream &in) = 0;
    
    static int getCount();
    static int count;

protected:
    int id;
    string name;
    int level;
    double salary;
    
    friend class PayrollSystem;
};

class Manager : public virtual Person {
public:
    Manager(string name);
    void pay() override;
    string getRoleName() const override;
    string getTypeCode() const override;
    void writeExtra(ostream &out) const override;
    void readExtra(istream &in) override;
};

class Technician : public Person {
public:
    Technician(string name, double hourlyRate = 100.0, double hoursWorked = 0.0);
    double getHourlyRate() const;
    double getHoursWorked() const;
    void setHourlyRate(double rate);
    void setHoursWorked(double hours);
    void pay() override;
    string getRoleName() const override;
    string getTypeCode() const override;
    void writeExtra(ostream &out) const override;
    void readExtra(istream &in) override;
protected:
    double hourlyRate;
    double hoursWorked;
};

class Salesperson : public virtual Person {
public:
    Salesperson(string name, double salesAmount = 0.0);
    double getSalesAmount() const;
    void setSalesAmount(double amount);
    void pay() override;
    string getRoleName() const override;
    string getTypeCode() const override;
    void writeExtra(ostream &out) const override;
    void readExtra(istream &in) override;
protected:
    double salesAmount;
};

class SalesManager : public Manager, public Salesperson {
public:
    SalesManager(string name, double departmentSales = 0.0);
    double getDepartmentSales() const;
    void setDepartmentSales(double amount);
    void pay() override;
    string getRoleName() const override;
    string getTypeCode() const override;
    void writeExtra(ostream &out) const override;
    void readExtra(istream &in) override;
protected:
    double departmentSales;
};

class PayrollSystem {
public:
    static string defaultRecordPath();
    explicit PayrollSystem(string recordPath = defaultRecordPath());
    ~PayrollSystem();
    
    const string &getRecordPath() const;
    void setRecordPath(string path);
    
    Manager *addManager(const string &name);
    Technician *addTechnician(const string &name, double hourlyRate, double hoursWorked);
    Salesperson *addSalesperson(const string &name, double salesAmount);
    SalesManager *addSalesManager(const string &name, double departmentSales);
    
    vector<Person *> &getEmployees();
    const vector<Person *> &getEmployees() const;
    
    Person *findById(int id);
    const Person *findById(int id) const;
    
    double processPayroll(Person &person);
    double processAllPayrolls();
    
    void loadRecords();
    void saveRecords() const;

private:
    Person *recreateEmployee(const string &type, int id, const string &name);
    vector<Person *> employees;
    string recordPath;
};

int Person::count = 2001;

// ========== Person 实现 ==========

inline Person::Person(string name, int level)
    : id(count++), name(name), level(level), salary(0.0) {}

inline int Person::getId() const { return id; }
inline string Person::getName() const { return name; }
inline int Person::getLevel() const { return level; }
inline double Person::getSalary() const { return salary; }
inline string Person::getLevelLabel() const { return to_string(level) + "级"; }
inline void Person::setLevel(int level) { this->level = level; }
inline int Person::getCount() { return count; }

// ========== Manager 实现 ==========
inline Manager::Manager(string name) : Person(name, 4) {}
inline void Manager::pay() { salary = 18000.0; }
inline string Manager::getRoleName() const { return "经理"; }
inline string Manager::getTypeCode() const { return "Manager"; }
inline void Manager::writeExtra(ostream &out) const { (void)out; }
inline void Manager::readExtra(istream &in) { (void)in; }

// ========== Technician 实现 ==========
inline Technician::Technician(string name, double hourlyRate, double hoursWorked)
    : Person(name, 3), hourlyRate(hourlyRate), hoursWorked(hoursWorked) {}

inline double Technician::getHourlyRate() const { return hourlyRate; }
inline double Technician::getHoursWorked() const { return hoursWorked; }
inline void Technician::setHourlyRate(double rate) { hourlyRate = rate; }
inline void Technician::setHoursWorked(double hours) { hoursWorked = hours; }
inline void Technician::pay() { salary = hourlyRate * hoursWorked; }
inline string Technician::getRoleName() const { return "技术人员"; }
inline string Technician::getTypeCode() const { return "Technician"; }
inline void Technician::writeExtra(ostream &out) const { out << hourlyRate << ' ' << hoursWorked; }
inline void Technician::readExtra(istream &in) {
    double rate = hourlyRate, hours = hoursWorked;
    if (in >> rate) {
        if (!(in >> hours)) hours = 0.0;
        hourlyRate = rate; hoursWorked = hours;
    } else { hourlyRate = 100.0; hoursWorked = 0.0; }
}

// ========== Salesperson 实现 ==========
inline Salesperson::Salesperson(string name, double salesAmount)
    : Person(name, 1), salesAmount(salesAmount) {}

inline double Salesperson::getSalesAmount() const { return salesAmount; }
inline void Salesperson::setSalesAmount(double amount) { salesAmount = amount; }
inline void Salesperson::pay() { salary = salesAmount * 0.04; }
inline string Salesperson::getRoleName() const { return "推销员"; }
inline string Salesperson::getTypeCode() const { return "Salesperson"; }
inline void Salesperson::writeExtra(ostream &out) const { out << salesAmount; }
inline void Salesperson::readExtra(istream &in) {
    double value = salesAmount_;
    if (in >> value) {
        salesAmount_ = value;
    } else {
        salesAmount_ = 0.0;
    }
}

inline double Salesperson::computePay() const { return salesAmount_ * 0.04; }

inline SalesManager::SalesManager(int id, string name, double departmentSales)
    : Person(id, move(name), 2), departmentSales_(departmentSales) {}

inline double SalesManager::departmentSales() const noexcept { return departmentSales_; }

inline void SalesManager::setDepartmentSales(double amount) { departmentSales_ = amount; }

inline string SalesManager::roleName() const { return "销售经理"; }

inline string SalesManager::typeCode() const { return "SalesManager"; }

inline void SalesManager::writeExtra(ostream &out) const { out << departmentSales_; }

inline void SalesManager::readExtra(istream &in) {
    double value = departmentSales_;
    if (in >> value) {
        departmentSales_ = value;
    } else {
        departmentSales_ = 0.0;
    }
}

inline double SalesManager::computePay() const { return 5000.0 + departmentSales_ * 0.02; }

inline string PayrollSystem::defaultRecordPath() { return "record.txt"; }

inline PayrollSystem::PayrollSystem(string recordPath) : recordPath(recordPath) {
    loadRecords();
}

inline PayrollSystem::~PayrollSystem() {
    for (Person *emp : employees) delete emp;
}

inline const string &PayrollSystem::getRecordPath() const { return recordPath; }
inline void PayrollSystem::setRecordPath(string path) { recordPath = path; }

inline Manager *PayrollSystem::addManager(const string &name) {
    Manager *mgr = new Manager(name);
    employees.push_back(mgr);
    return mgr;
}

inline Technician *PayrollSystem::addTechnician(const string &name, double hourlyRate, double hoursWorked) {
    Technician *tech = new Technician(name, hourlyRate, hoursWorked);
    employees.push_back(tech);
    return tech;
}

inline Salesperson *PayrollSystem::addSalesperson(const string &name, double salesAmount) {
    Salesperson *sales = new Salesperson(name, salesAmount);
    employees.push_back(sales);
    return sales;
}

inline SalesManager *PayrollSystem::addSalesManager(const string &name, double departmentSales) {
    SalesManager *smgr = new SalesManager(name, departmentSales);
    employees.push_back(smgr);
    return smgr;
}

inline vector<Person *> &PayrollSystem::getEmployees() { return employees; }
inline const vector<Person *> &PayrollSystem::getEmployees() const { return employees; }

inline Person *PayrollSystem::findById(int id) {
    for (Person *emp : employees) {
        if (emp->getId() == id) return emp;
    }
    return nullptr;
}

inline const Person *PayrollSystem::findById(int id) const {
    for (const Person *emp : employees) {
        if (emp->getId() == id) return emp;
    }
    return nullptr;
}

inline double PayrollSystem::processPayroll(Person &person) {
    person.pay();
    return person.getSalary();
}

inline double PayrollSystem::processAllPayrolls() {
    double total = 0.0;
    for (Person *emp : employees) {
        emp->pay();
        total += emp->getSalary();
    }
    return total;
}

inline void PayrollSystem::loadRecords() {
    for (Person *emp : employees) delete emp;
    employees.clear();
    
    if (recordPath.empty()) return;
    
    ifstream file(recordPath);
    if (!file.is_open()) return;
    
    int storedCount = Person::count;
    if (!(file >> storedCount)) return;
    
    int recordCount = 0;
    if (!(file >> recordCount)) return;
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    
    Person::count = storedCount;
    for (int i = 0; i < recordCount; ++i) {
        string type;
        if (!(file >> type)) break;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        
        int id = 0;
        if (!(file >> id)) break;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        
        string name;
        if (!getline(file, name)) break;
        
        double lastSalary = 0.0;
        if (!(file >> lastSalary)) break;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        
        string extraLine;
        if (!getline(file, extraLine)) extraLine.clear();
        
        Person *employee = recreateEmployee(type, id, name);
        if (!employee) continue;
        employee->salary = lastSalary;
        istringstream extraStream(extraLine);
        employee->readExtra(extraStream);
        if (id >= Person::count) Person::count = id + 1;
        employees.push_back(employee);
    }
}

inline void PayrollSystem::saveRecords() const {
    if (recordPath.empty()) return;
    
    ofstream file(recordPath);
    if (!file.is_open()) return;
    
    file << Person::count << '\n';
    file << employees.size() << '\n';
    for (const Person *emp : employees) {
        file << emp->getTypeCode() << '\n';
        file << emp->getId() << '\n';
        file << emp->getName() << '\n';
        file << emp->getSalary() << '\n';
        emp->writeExtra(file);
        file << '\n';
    }
}

inline Person *PayrollSystem::recreateEmployee(const string &type, int id, const string &name) {
    Person *emp = nullptr;
    if (type == "Manager") emp = new Manager(name);
    else if (type == "Technician") emp = new Technician(name);
    else if (type == "Salesperson") emp = new Salesperson(name);
    else if (type == "SalesManager") emp = new SalesManager(name);
    
    if (emp) emp->id = id;
    return emp;
}

#endif // PAYROLL_SYSTEM_H

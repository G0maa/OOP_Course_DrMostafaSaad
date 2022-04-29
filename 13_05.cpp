#include <bits/stdc++.h>
using namespace std;

// Couldn't solve this one, Compare() in particular.

// Problem: as shown, I can't have different pointer from the parent as in class
//          Compareable, the compare() has refrence to Parent class,
//          while rest of children has refrence to child classes, which can't be done
//          because child can't point to parent.

// Solution: As in Doc's solution => Downcasting.

class Cloneable {
public:
    Cloneable() {

    }

    virtual Cloneable* Clone() const = 0;

    ~Cloneable() {

    }
};

class Printable {
public:
    Printable() {

    }

    virtual void Print() const = 0;

    ~Printable() {

    }
};

class Comparable {
public:
    Comparable() {

    }

    virtual bool Compare(const Comparable *other) const = 0;

    ~Comparable() {

    }
};

class Sortable {
public:
    Sortable() {

    }
    // ??? STOPPED HERE.
    virtual void Sort() = 0;

    ~Sortable() {

    }
};

class Payable : public Cloneable, public Printable, public Comparable {
public:
    Payable() {

    }

    virtual Payable* Clone() const override = 0;
    virtual void Print() const override = 0;
    virtual bool Compare(const Payable *other) const = 0;
    virtual int GetType() const = 0;
    ~Payable() {

    }
};

class Employee : public Payable {
private:
    string name;
    int salary;
public:
    Employee(const string &name, const int &salary) : name(name), salary(salary) {

    }

    virtual Employee* Clone() const override {
        return new Employee(*this);
    }

    virtual bool Compare(const Employee *other) const {
        other->salary;
    }

    virtual void Print() const override {
        ostringstream oss;
        oss << "Employee: " << name << ' ' << salary;
        cout << oss.str();
    }

    virtual int GetType() const {
        return 1;
    }
};

class Invoice : public Payable {
private:
    string name;
    int cost;

public:
    Invoice(const string &name, const int &cost) : name(name), cost(cost) {

    }

    virtual Invoice* Clone() const override {
        return new Invoice(*this);
    }

    virtual bool Compare(const Invoice *other) const {

    }

    virtual void Print() const override {
        ostringstream oss;
        oss << "Invoice: " << name << ' ' << cost;
        cout << oss.str();
    }

    virtual int GetType() const {
        return 2;
    }
};

class CompanyParoll : public Printable, public Sortable {
private:
    vector<Payable*> payable_vec;
public:
    void AddPayable(const Payable &payable) {
        payable_vec.push_back(payable.Clone());
    }

    // Sort two times, once for object, second for cost.
    // The way I'd do it is by overloading < operator twice, once for object type, second for object key.
    // ^ O(2nlogn)
    virtual void Sort() override {
        int arr[50];

        // Yikes, No DRY, O(2n^2) .-.
        for(int i = 0; i < (int)payable_vec.size() - 1; i++) {
            for(int j = 0; j < (int)payable_vec.size() - 1; j++) {
                if(payable_vec[i]->GetType() > payable_vec[i + 1]->GetType())
                    swap(payable_vec[i], payable_vec[i + 1]);
            }
        }

        for(int i = 0; i < (int)payable_vec.size() - 1; i++) {
            for(int j = 0; j < (int)payable_vec.size() - 1; j++) {
                if(payable_vec[i]->Compare(payable_vec[i + 1]))
                    swap(payable_vec[i], payable_vec[i + 1]);
            }
        }
    }

    virtual void Print() const override {
        int total = 0;
        for(int idx = 0; idx < (int) payable_vec.size(); idx++) {
            payable_vec[idx]->Print();
            cout << '\n';
            // total += payable_vec.GetCost();
        }
        cout << "Total: " << total << '\n';
    }
};


int main() {
    CompanyParoll payroll;
    payroll.AddPayable(Employee("mostafa", 50));
    payroll.AddPayable(Invoice("Deserts", 100));
    payroll.AddPayable(Employee("ziad", 10));
    payroll.AddPayable(Invoice("Groceries", 200));
    payroll.AddPayable(Employee("belal", 30));
    payroll.AddPayable(Invoice("Petrol", 300));
    
    payroll.Sort();
    payroll.Print();

}
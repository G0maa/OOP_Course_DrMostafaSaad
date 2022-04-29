#include <bits/stdc++.h>
using namespace std;

// If payables get too many, I guess you'd  eventually need to create this,
// I think a better solution would be an interface?
// class Payables {

// };

// Missing few constructors here and there.

class WorkingPeople {
protected:
    string name { };
    int age { };
    // Address adress; etc...

    // You can't just have some random `Working Someone`.
    WorkingPeople() { }
public:

    virtual int GetSalary() const {
        cout << "\nYou screwed up m8!\n";
        assert(false);
    }

    ~WorkingPeople() { }
};


class Volutneer : public WorkingPeople {
private:
    int volunteer_hours { };

public:
    virtual int GetSalary() const override {
        return 0;
    }
};

class Employee : public WorkingPeople {
protected:
    Employee() { }; // again don't want Employee without a specified Paying scheme.
};

// Answer to question... I guess wait for a purpose to show itself?
// then un-final this class, and create new class `Labourer Employee`             <
// although in a real situation you might need to indetify employees of that type ^.
class HourlyBasedEmployee final : public WorkingPeople {
private:
    int hours_worked { };
    int pay_per_hour { };
public:

    virtual int GetSalary() const override{ 
        return hours_worked * pay_per_hour;
    }
};

class SalaryBasedEmployee : public WorkingPeople {
private:
    int salary { };

public:
    virtual int GetSalary() const override {
        return salary;
    }
};

class CommissonBasedEmployee final : public SalaryBasedEmployee {
private:
    int commison_in_precent { };
    int total_commisons { };

public:
    virtual int GetSalary() const override {
        return SalaryBasedEmployee::GetSalary() + ((total_commisons) * commison_in_precent);
    }
};

// I thought of making constructor of this object private,
// as in, it's too generaly you can't make an instance of it,
// but... meh.
// Even ploymorphism here isn't useful, GetItemPrice() will get you itme_price that is in every object
// doesn't need to be virtual... unless some item has different opinion of implmenting item_price.
class Item {
protected:
    // I thought of haveing something like class OtherItmes : public Item { };
    // And remove those, but I went with current desiegn.
    string item_name { };
    int item_price { };

public:

    Item(const string &item_name, const int &item_price) : item_name(item_name), item_price(item_price) {

    }

    // If in future some new class implements this function differently => will need to add `virtual`.
    int GetItemPrice() const {
        return item_price;
    }
};

// Nothing inherits from `Invoice`... well unless you have more than one invoice type.
class Invoice final{
private:
    vector<Item> items;
public:
    Invoice() {

    }


    int GetInvoicePrice() const {
        int total = 0;
        for(int idx = 0; idx < (int) items.size(); idx++)
            total += items[idx].GetItemPrice();
    }
};


class Book final : public Item {
private:
    string book_author { };
    int page_count { };
public:

    Book(const string &item_name, const int &item_price, const string &book_author, const int &page_count) :
     Item(item_name, item_price), book_author(book_author), page_count(page_count) {

    }
};


class Food final : public Item {
private:
    // Date manufacturing_date;
    // Date expiring_date;

public:
    using Item::Item;
};


class PayrollSys final {
private:
    vector<WorkingPeople> working_people;
    vector<Invoice> invoices;

public:

    PayrollSys() {
        // Maybe test it here? create bunch of objects and push_back() them.
    }

    int GetPayroll() const {
        // I thought of grouping `WorkingPeople` and `Invoices` togheter 
        //  to something like `Payments` but it didn't sit right with me.
        int total = 0;
        for(int idx = 0; idx < (int) working_people.size(); idx++)
            total += working_people[idx].GetSalary();

        for(int idx = 0; idx < (int) invoices.size(); idx++)
            total += invoices[idx].GetInvoicePrice();

        return total;
    }
};


class CompanySys final {
private: 
    PayrollSys pay_roll;
public:

    CompanySys() {

    }

    int GetPayroll() const {
        pay_roll.GetPayroll();
    }
};


int main() {
    // CompanySys instance;
    // cout << instance.GetPayroll();

    Book obj("ArdElnefaq", 123, "Subi3i", 200);
    cout << obj.GetItemPrice();
    cout << "\n\n Bye :) \n\n";
}
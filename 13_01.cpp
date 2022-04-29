#include <bits/stdc++.h>
using namespace std;

class Payable {
public:
	virtual double GetAmountToPay() const {}
	virtual ~Payable() {
	}
};

class StaffMember: public Payable {
private:
	string name;
	string address;
public:
};

class Employee: public StaffMember {
private:
	int day_to_pay;
public:

};

class HourlyEmployee: public Employee {
private:
	int total_working_hours;
	double salary_per_hour;
public:
	virtual double GetAmountToPay() const override {
		cout << "HourlyEmployee\n";
		return total_working_hours * salary_per_hour;
	}
};

class SalariedEmployee: public Employee {
private:
	double monthly_salary;
public:
	virtual double GetAmountToPay() const override {
		cout << "SalariedEmployee\n";
		return monthly_salary;
	}
};

class CommisionSalariedEmployee: public SalariedEmployee {
private:
	double commision_rate;
	double current_month_sales;
public:
	virtual double GetAmountToPay() const override {
		cout << "CommisionSalariedEmployee\n";
		return SalariedEmployee::GetAmountToPay() + current_month_sales * commision_rate;
	}
};

class Volunteer: public StaffMember {
private:
	int current_payment;
public:
	virtual double GetAmountToPay() const override {
		return current_payment;
	}
};

class Item {
private:
	string desc;
	double price;
	int quantity;
public:
	double GetPrice() const {
		return price * quantity;
	}
};

class Book: public Item {
private:
	string author;
};

class Food: public Item {
private:
	string expiration_date;
};

class Invoice: public Payable {
private:
	int invoice_id = -1;
	vector<Item*> items;
public:
	void AddItem(Item* item) {
		items.push_back(item);
	}

	virtual double GetAmountToPay() const override {
		cout << "Invoice\n";

		double sum = 0;
		for (const Item* item_ptr : items)
			sum += item_ptr->GetPrice();
		return sum;
	}
};

class Payroll {
private:
	vector<Payable*> payables;

public:
	void AddPayable(Payable* payable) {
		payables.push_back(payable);	// we should add copy
	}
	void Pay() {
		cout << "Payroll::Pay\n";
		;
		for (const auto payable : payables) {
			// Logic to choose from validator groups or something.
			// after that:
			MandatoryValidatorGroup obj;
			if(obj.Run(payable)) // either down-cast, or make a function in Invoice to check if it's valid or not.
				payable->GetAmountToPay();
			// else some warning logic and show where it is not validated, will need object outside if condition.
		}
			
	}
};

class Company {
private:
	Payroll payroll;
public:
	Company() {
	}

	void Run() {
		payroll.AddPayable(new Volunteer());
		payroll.AddPayable(new HourlyEmployee());
		payroll.AddPayable(new SalariedEmployee());
		payroll.AddPayable(new CommisionSalariedEmployee());

		Invoice* invoice = new Invoice();
		invoice->AddItem(new Book());
		invoice->AddItem(new Food());

		payroll.AddPayable(invoice);

		payroll.Pay();
	}
};

// Goal is to have object of invoice shomehow, either in Payroll function,
// or in a function in class invoice itself,
// rest is the same.
// I guess I was lost in this one :)

// After reviewing dr solution:
// 		- Not too bad on my part.
// 		- Gouped ValidatorConditions AND ValidatorGroups.
// 		- Function of Validation is inside class invoice itself.

// 	So: Invoice has pointer of ValidatorGroup, ValidatorGroup is divided to (Manadatory - Complete - etc...)
//      which is not specified obviously (polymorphism), aka in function of validation inside invoice something like this
// 		ValidatorGroup = new CompleteGroup();
// 		each group has set of ValidatorRules, which again can be (TaxRule - DateRule - etc...)
// 		So when uoi run ValidatorGroup -> It sees which Group it is (let's say manadatorygroup),
// 		push_back needed Ruels, then runs each rule.
// 		run each rule -> finds which rule is added.

class ValidatorGroups { // Might be a bit better. *like here

};


// Problem: I claim that some validators maay be used with many groups.'
// 			also you will need many Getters(), or use some Compare() to compre with a valid invoice?
class MandatoryValidatorGroup {
private:
	vector<ValidatingConditions*> valid_qs;
public:

	bool Run(const Invoice &invoice) {
		// Too many push backs because I don't know how to make the function run in all of them.
		valid_qs.push_back(new ValidatorA());
		valid_qs.push_back(new ValidatorB());
		valid_qs.push_back(new ValidatorC());
		for(int i = 0; i < valid_qs.size(); i++)
			if(valid_qs[i]->Run(invoice))
				cout << "something";
	}
};

class CompleteValidatorGroup {

};

class ItemSpecificValidatorGroup {

};

class ValidatingConditions {
public:
	virtual bool Run(const Invoice &invoice) {

	}
};

// Let's say expiry date of invoice.
class ValidatorA : public ValidatingConditions {
public:
	virtual bool Run(const Invoice &invoice) {
		// do something.
	}
};

// let's say tax rules
class ValidatorB : public ValidatingConditions {

};

// Let's say validates invoice_id against data base records.
class ValidatorC : public ValidatingConditions {

};

// is food expired? (not useful I guess?)
class ValidatorD : public ValidatingConditions {

};


int main() {
	Company company;
	company.Run();

	return 0;
}

/*

Payroll::Pay
HourlyEmployee
SalariedEmployee
CommisionSalariedEmployee
SalariedEmployee
Invoice

 */

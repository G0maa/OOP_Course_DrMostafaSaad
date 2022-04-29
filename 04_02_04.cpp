#include <bits/stdc++.h>
using namespace std;

class invoice {
    private:
    string name;
    int item_number;
    double price;
    int quantity;
public:
    invoice(string name, int item_number, int price, int quantity);
    string getName();
    int getItemNumber();
    double getPrice();
    int getQuantity();
    void setName(string name_);
    void setItemNumber(int item_number_);
    void setPrice(double price_);
    void setQuantity(int quantity_);
    double GetTotalPrice();
    void print();
    string ToString();
};


invoice::invoice(string name, int item_number, int price, int quantity) :
name(name), item_number(item_number), price(price), quantity(quantity) {}

string invoice::getName() {
    return name;
}

int invoice::getItemNumber() {
        return item_number;
}

double invoice::getPrice() {
    return price;
}

int invoice::getQuantity() {
    return quantity;
}

void invoice::setName(string name_) {
    name = name_;
}

void invoice::setItemNumber(int item_number_) {
    item_number = item_number_;
}

void invoice::setPrice(double price_) {
    price = price_;
}

void invoice::setQuantity(int quantity_) {
        quantity = quantity_;
}

double invoice::GetTotalPrice() {
    return (double) price * quantity;
}

void invoice::print() {
    cout << item_number << ' ' << name << ' ' << price << ' ' << quantity << '\n';
}

string invoice::ToString() {
        string ans = "";
        while(item_number != 0) {
            ans += (item_number % 10) + 48;
            item_number /= 10;
        }
        ans += ',';
        for(int i = 0; i < (int) name.length(); i++)
            ans += name[i];
        
        while(item_number != 0) { // same for rest too lazy to write, won't work with double
            ans += (item_number % 10) + 48; // just use built-in to string instead.
            item_number /= 10;
        }

        while(item_number != 0) {
            ans += (item_number % 10) + 48;
            item_number /= 10;
        } 
};
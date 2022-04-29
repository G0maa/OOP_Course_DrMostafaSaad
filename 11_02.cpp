#include <bits/stdc++.h>
using namespace std;

// Notice how doc used private not protectd for most/all data members in his solution.


// Too lazy to make it a class.
// lmao I got the same name :D
struct PaymentCard {
    string card_number;
    string vcc;

    PaymentCard() {
        cout << "Enter card number - vcc:\n";
        cin >> card_number >> vcc;
    }

    PaymentCard(const string &card_number, const string &vcc) : card_number(card_number), vcc(vcc) {

    }

    string ToString() const {
        ostringstream oss;
        oss << card_number << " " << vcc;
        return oss.str();
    }
};

// Too lazy to make it a class.
struct Address {
    string name { };
    string city { };
    string phone_number { };

    Address (const string &title) { 
        cout << "Address of " << title << '\n';
        cout << "Enter name:";
        cin >> name;
        cout << "Enter city: ";
        cin >> city;
        cout << "Enter phone number: ";
        cin >> phone_number;
    }

    Address (const string &name, const string &city, const string &phone_number) :
    name(name), city(city), phone_number(phone_number) { 

    }

    string ToString () const {
        ostringstream oss;
        oss << "Name: " << name << "\nCity: " << city << "\nPhone Number: " << phone_number;
        return oss.str();
    }
};



class StandardPackage {
protected:
    Address sender_address;
    Address receiver_address;
    double weight_per_kg { };
    double price_per_kg { }; // dunno if this should be aconstant value.

    const double& GetWeightPerKg() const {
        return weight_per_kg;
    }

    const double& GetPricePerKg() const {
        return price_per_kg;
    }


public:
    StandardPackage() : sender_address(Address("Sender")), receiver_address(Address("Receiver")) { 
        cout << "Enter weight of the package in kg: ";
        cin >> weight_per_kg;
        cout << "Enter price per kg: ";
        cin >> price_per_kg;
    }

    StandardPackage(const Address &sender_address, const Address &receiver_address, const double &weight_per_kg, const double &price_per_kg) :
    sender_address(sender_address), receiver_address(receiver_address), weight_per_kg(weight_per_kg), price_per_kg(price_per_kg) {

    }

    int TotalCost() const { // use of ceil is intentional.
        return ceil(GetPricePerKg() * GetWeightPerKg()); 
    }

    string ToString() const {
        ostringstream oss;
        oss << "Receiver Address:\n" << receiver_address.ToString() 
        << "\nSender Address: " << sender_address.ToString() << "\n Total Cost: " << TotalCost();
        return oss.str();
    }
};

class TwoDayPackage : public StandardPackage{
protected:
    int added_fixed_fee { };
public:
    TwoDayPackage() : StandardPackage() { 
        cout << "Enter the added fee: ";
        cin >> added_fixed_fee;
    }

    //           this here is just for the sake of simplicity rn.
    TwoDayPackage(const StandardPackage &obj, int added_fixed_fee) : StandardPackage(obj), added_fixed_fee(added_fixed_fee) {

    }

    // override, how to call parent function from here?
    int TotalCost() const {
        return (GetPricePerKg() * GetWeightPerKg()) + added_fixed_fee;
    }
};

class HeavyPackage : public StandardPackage {
protected:
    int price_extra { };
public:
    HeavyPackage() : StandardPackage() {
        cout << "Enter extra price per kg:";
        cin >> price_extra;
    }

    HeavyPackage(const StandardPackage &obj) : StandardPackage(obj), price_extra(price_extra){

    }

    int TotalCost() const {
        if(GetWeightPerKg() > 100)
            return (GetPricePerKg() * GetWeightPerKg()) + ((100 - GetWeightPerKg()) * price_extra);
        else
            return (GetPricePerKg() * GetWeightPerKg());
    }
};

class Shipment {
protected:
    vector<StandardPackage> standard_package;
    vector<TwoDayPackage> two_day_package;
    vector<HeavyPackage> heavy_package;
    PaymentCard payment_card;

public:

    Shipment(const vector<PaymentCard> payment_cards) : payment_card("0", "0") {
        cout << "Choose which payment card:\n";
        for(int idx = 0; idx < (int) payment_cards.size(); idx++)
            cout << idx + 1 << ": " << payment_cards[idx].ToString() << '\n';

        int n;
        cin >> n;
        payment_card = payment_cards[n - 1];

        cout << "Enter number of packages, then their info: ";
        cin >> n;
        while(n--) {
            cout << "1: Heavy Package, 2: Standard Package, 3: Two day Package\n";
            int choice;
            cin >> choice;
            if(choice == 1)
                heavy_package.push_back(HeavyPackage());
            else if(choice == 2)
                standard_package.push_back(StandardPackage());
            else
                two_day_package.push_back(TwoDayPackage());
        }
    }

    int GetTotalPrice() {
        int total = 0;
        for(int idx = 0; idx < (int) standard_package.size(); idx++)
            total += standard_package[idx].TotalCost();

        for(int idx = 0; idx < (int) heavy_package.size(); idx++)
            total += heavy_package[idx].TotalCost();

        for(int idx = 0; idx < (int) two_day_package.size(); idx++)
            total += two_day_package[idx].TotalCost();
    }
};

// Assuming trivial info: name, etc...
class Customer {
protected:
    vector<Shipment> shipments;
    vector<PaymentCard> payment_cards;

public:
    Customer() { 
        cout << "Please add you payment count of your payment cards: ";
        int n;
        cin >> n;
        while(n--)
            payment_cards.push_back(PaymentCard());
        
        cout << "Please add count of your shipments: ";
        cin >> n;
        while(n--)
            shipments.push_back(Shipment(payment_cards));

    }

    vector<Shipment> GetShipments() {
        cout << "Sending shipments to system....\n";
        return shipments;
    }
};


class GomaaEx {
protected:
    vector<Shipment> shipments_to_send;
public:
    GomaaEx() {

    }

    // Takes a copy, not by refrence.
    void AddShipments(vector<Shipment> new_shipments) {
        for(int idx = 0; idx < (int) new_shipments.size(); idx++) {
            cout << "Shipment cost:\n";
            cout << new_shipments[idx].GetTotalPrice() << '\n';
            shipments_to_send.push_back(new_shipments[idx]);
        }
            

        SendShipments();
    }

    void SendShipments() {
        cout << "Shipments are on their way! Don't expect a reply from us soon!\n";
        shipments_to_send.clear();
    }
};

// Cut few edges here and there.
// Not tested.
// I revised the solution of doc after coding, I think I didn't really solve the question given as intended :)
// But I got the idea, if that holds any value.
// Major difference, dr added bunch of getters/setters, and the few functions he asked for, I coded some logic,
// which is.... not really OO by the book :/
int main() {
    GomaaEx Service;
    Customer Mo;
    Service.AddShipments(Mo.GetShipments());
    cout << "\n Bye :) \n";
}
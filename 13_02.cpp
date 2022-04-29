#include <bits/stdc++.h>
using namespace std;

// I know that we were told to create extensible design,
// I think class car should be 'abstracted' to class 'Veicle', but I'll ignore that for now,
// same for class 'Hotel' to someting like 'Accomedation', 
// which containts, Hotel, Hostel, FamilyHouse, something like that.
// *Tried* not to cut as much corners as I nromally do this time.
class ItineraryItem {

public:
    ItineraryItem() { } // I think this should be private?

    virtual int GetCost() = 0;

    virtual ItineraryItem* Cloner() const = 0;

    ~ItineraryItem() { }
};

class Flight : public ItineraryItem {
private:
    string from;
    string to;
    string date; // Date date;
    int cost;

public:
    Flight(const string &from, const string &to, const string &date, const int &cost) : from(from), to(to), date(date), cost(cost) { 

    }

    virtual int GetCost() {
        return cost;
    }

    virtual ItineraryItem* Cloner() const override { 
        return new Flight(*this);
    }
};

class Hotel : public ItineraryItem {
private:
    string hotel_name;
    int reservation_days;
    int cost_per_day;
    // Address address;
    // Date date;
    // Room - Floor - etc...
public:
    Hotel(const string &hotel_name, const int &reservation_days, const int &cost_per_day) : hotel_name(hotel_name), reservation_days(reservation_days), cost_per_day(cost_per_day) {

    }

    virtual int GetCost() {
        return cost_per_day * reservation_days;
    }

    virtual ItineraryItem* Cloner() const override { 
        return new Hotel(*this);
    }
};

class Car : public ItineraryItem {
private:
    string model;
    string car_id;
    // Date date;
    int num_days_rented;
    int cost_per_day;
public:
    Car(const string &model, const string &car_id, const int &num_days_rented, const int &cost_per_day) : model(model), car_id(car_id), num_days_rented(num_days_rented), cost_per_day(cost_per_day) {
        
    }

    virtual int GetCost() {
        return num_days_rented * cost_per_day;
    }

    virtual ItineraryItem* Cloner() const override{ 
        return new Car(*this);
    }
};

// This will probably need object of user who "reserved" it.
class Itinerary final {
private:
    vector<ItineraryItem*> itinerary_items;
public:
    Itinerary() { }
    
    void AddItem(const ItineraryItem *new_item) { 
        itinerary_items.push_back(new_item->Cloner());
    }

    int GetCost() {
        int total = 0;
        for(auto itinerary_item : itinerary_items) 
            total += itinerary_item->GetCost();

        return total;
    }
};

// This also works like "Reservation manager".
class ItineraryManager final {
private:
    vector<Itinerary> itinerary_vec;
public:
    ItineraryManager() {

    }

    void AddItinerary(const Itinerary &new_itinerary) {
        itinerary_vec.push_back(new_itinerary);
    }

    void GetCost() {
        for(auto itinerary : itinerary_vec) {
            cout << "Cost of itinerary: " << itinerary.GetCost() << '\n';
        }
    }
};


class ExpediaTravelSys final {
private:
    ItineraryManager itinerary_mngr;
public:
    ExpediaTravelSys() {
        Itinerary mo_res;
        mo_res.AddItem(new Car("Toyota", "ABC-123", 4, 150));
        mo_res.AddItem(new Flight("Egypt", "Saudi", "2022, 2, 17", 3250));
        mo_res.AddItem(new Hotel("Continental", 3, 325));

        itinerary_mngr.AddItinerary(mo_res);
        itinerary_mngr.GetCost();
    }

    void Run() {

    }
};

int main() {
    ExpediaTravelSys service;
    service.Run();
    cout << "\n\n Bye :) \n\n";
}
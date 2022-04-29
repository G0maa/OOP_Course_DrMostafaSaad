#include <bits/stdc++.h>
#include "HelperFunctions.h"
#include "Date_class.h"

using namespace std;

// Private:
// If I have extra-time I'll add month day array.
void Date::SetDay(int &day_) {
    if(day_ < day)
        day_ = day;
    else if(day_ > 31)
        day_ = 31;
    day = day_;
}

void Date::SetMonth(int &month_) {
    if(month_ < month)
        month_ = month;
    else if(month_ > 12)
        month_ = 12;
    
    month = month_;
}

void Date::SetYear(int &year_) {
    if(year_ < year)
        year_ = year;
    else if(year_ > 2050) // My prophecy for the future.
        year_ = 2050;

    year = year_;
}

// Public:
Date::Date(const bool &is_default) {
    if(!is_default)
        UpdateDate();
}


Date::Date(const vector<string>& lines) {
    int year_ = StringToInt(lines[0]);
    int month_ = StringToInt(lines[1]);
    int day_ = StringToInt(lines[2]);

    SetYear(year);
    SetMonth(month);
    SetDay(day);
}


void Date::UpdateDate() {
    PrintLine("Enter date for session: ");

    PrintLine("Enter year (1-2050): ");
    int year_ = -1;
    cin >> year_;
    SetYear(year_);

    PrintLine("Enter month (1-12): ");
    int month_ = -1;
    cin >> month_;
    SetMonth(month_);

    PrintLine("Enter day (1-31): ");
    int day_ = -1;
    cin >> day_;
    SetDay(day_);
}


const string Date::ToString() const {
    ostringstream oss;
    oss << year << '\t' << month << '\t'<< day;
    return oss.str();
}
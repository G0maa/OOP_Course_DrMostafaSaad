#ifndef DATECLASS_CLASS_H_
#define DATECLASS_CLASS_H_

#include <string>
#include <vector>
using namespace std;

class Date {
private:
    int day {1};
    int month {1};
    int year {1};

    void SetDay(int &day_); 
    void SetMonth(int &month_);
    void SetYear(int &year_);

public:

    Date(const bool &is_default = 0);
    Date(const vector<string>& lines);

    void UpdateDate();
    const string ToString() const;

    // Date(const Date&) = delete;
    void operator=(const Date&) = delete;
};

#endif
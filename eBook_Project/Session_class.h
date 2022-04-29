#ifndef SESSION_CLASS_H_
#define SESSION_CLASS_H_

#include <string>
#include <vector>
#include "HelperFunctions.h"
#include "Book_class.h"
#include "Date_class.h"

using namespace std;

class Session {
private:
    int user_id { };
    int cur_page { -1 };
    Book session_book;
    Date seession_date;

    void GoNextPage();
    void GoPrevPage();
    void ViewSessionDetails() const;
    void PrintCurPage() const;

public:

    Session(const vector<string> &session_line, const Book &book_obj, const Date &date_obj);
    Session(const int &user_id, const int &cur_page, const Book &book_obj);

    void Run();
    const string ToString() const;
    bool CompareUserID(const Session &other) const;
    int GetUserID() const;
    bool CompareSessionBook(const Book &other_session_book) const;

    // If in distress, allow copy for push_back() in vectors.
    // Session(const Session&) {
    //     cout << "!!COPY FOR CLASS `SESSION` HAPPENED!!";
    // }
    void operator=(const Session&) = delete;
};

#endif
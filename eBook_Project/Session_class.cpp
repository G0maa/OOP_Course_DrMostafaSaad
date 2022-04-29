#include "Session_class.h"

using namespace std;

// Private:
void Session::GoNextPage() {
    if(session_book.ComparePageCount(cur_page + 1))
        cur_page++;
    else
        PrintLine("Book finished!");
    
    PrintCurPage();
}


void Session::GoPrevPage() {
    if(session_book.ComparePageCount(cur_page - 1))
        cur_page--;
    else
        PrintLine("No previous page!");
    
    PrintCurPage();
}


void Session::ViewSessionDetails() const {
    session_book.ViewBook();
    PrintCurPage();
}


void Session::PrintCurPage() const {
    string print_me = "Current Page: " + IntToString(cur_page);
    PrintLineHashed(print_me);
}

// Public:
// Sessions.txt => user_id - cur_page | name - author - page_count | year - month - day
Session::Session(const vector<string> &session_line, const Book &book_obj, const Date &date_obj) :
                user_id(StringToInt(session_line[0])), cur_page(StringToInt(session_line[1])), 
                session_book(book_obj), seession_date(date_obj) { 
                    // cout << "\n\n Session Constructor works! \n\n";
                }

Session::Session(const int &user_id, const int &cur_page, const Book& book_obj) :
                user_id(user_id), cur_page(cur_page), session_book(book_obj), seession_date(Date(1)) {

}


bool Session::CompareUserID(const Session &other) const {
    if(GetUserID() == other.GetUserID())
        return true;
    else
        return false;
}


int Session::GetUserID() const {
    return user_id;
}


bool Session::CompareSessionBook(const Book &other_session_book) const {
    return session_book.CompareBook(other_session_book);
}


void Session::Run() {
    vector<string> session_menu {"View session details", "Go next page", "Go previous page", "Return to previous menu"};
    
    int choice = 0;
    while(choice != -1) {
        PrintMenu(session_menu, "Session Managerr Menu");
        PrintLine("Choose an option: ");
        VerifyChoice(choice, 1, 4);
        if(choice == 1)
            ViewSessionDetails();
        else if(choice == 2)
            GoNextPage();
        else if(choice == 3)
            GoPrevPage();
        else {
            seession_date.UpdateDate();
            return;
        }
    }
}


const string Session::ToString() const {
    ostringstream oss;
    oss << user_id << '\t' << cur_page << '\t'<< session_book.ToString() << '\t' << seession_date.ToString();
    return oss.str();
}

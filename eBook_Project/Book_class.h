#ifndef BOOK_CLASS_H_
#define BOOK_CLASS_H_

#include <string>
#include <vector>
using namespace std;

class Book {
private:
    string name { };
    string author { };
    int page_count { };
    string GetBookName() const;
    
public:
    Book();
    Book(const bool &flag);
    Book(const string& line);
    Book(const vector<string>& lines);

    void ViewBook() const;
    const string ToString() const;
    bool ComparePageCount(const int &other_page_count) const;
    bool CompareBook(const Book &other) const;

    
    // Book(const Book&) = delete;
    void operator=(const Book&) = delete;
};

#endif /* BOOK_CLASS_H_ */
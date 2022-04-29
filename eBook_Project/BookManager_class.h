#ifndef BOOKMANAGER_CLASS_H_
#define BOOKMANAGER_CLASS_H_

#include <vector> 
#include "Book_class.h"
using namespace std;

class BookManager {
private:
    vector<Book> book_vec;

    void LoadBooks();
    void SaveBooks() const;
    int GetBooksCount() const;
public:

    BookManager();
    void AddBook();
    void ViewBooks() const;
    const Book ChooseBook() const;

    BookManager(const BookManager&) = delete;
    void operator=(const BookManager&) = delete;
};

#endif
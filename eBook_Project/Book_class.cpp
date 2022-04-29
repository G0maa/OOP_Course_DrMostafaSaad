#include "Book_class.h"

// Tried to include specific libraries, but "ostringstream" showed an "incomplete type error", then I stopped trying.
#include <bits/stdc++.h> 
#include "HelperFunctions.h"
using namespace std;

// Public:
Book::Book() { }

Book::Book(const bool &flag) { 
    PrintLineHashed("Enter book details");
    PrintLine("Enter book name: ");
    cin >> name;
    PrintLine("Enter book author: ");
    cin >> author;
    PrintLine("Enter book page count: ");
    cin >> page_count;
}


Book::Book(const string& line) {
    vector<string> out;
    SplitString(out, line);
    // Books.txt => name - author - page_count
    name = out[0];
    author = out[1];
    page_count = StringToInt(out[2]);
}


Book::Book(const vector<string>& lines) {
    name = lines[0];
    author = lines[1];
    page_count = StringToInt(lines[2]);
}

// false => outside range, true => inside range.
bool Book::ComparePageCount(const int &other_page_count) const {
    if(other_page_count >= 1 && other_page_count <= page_count)
        return true;

    return false;
}

// Lazy compare.
bool Book::CompareBook(const Book &other) const {
    if(GetBookName() == other.GetBookName())
        return true;
    else
        return false;
}


string Book::GetBookName() const {
    return name;
}


void Book::ViewBook() const {
    vector<string> pair_a {"Book Name", "Book author", "Page count"};
    vector<string> pair_b {name, author, IntToString(page_count)};
    PrintPairs(pair_a, pair_b, "Book Details");
}


const string Book::ToString() const {
    ostringstream oss;
    oss << name << '\t' << author << '\t' << page_count;
    return oss.str();
}
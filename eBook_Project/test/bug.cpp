#include <bits/stdc++.h>
using namespace std;

// Before solution:
// Notice, `eBookSystemIO` calls function of `Book` in `PrintViewBook()`
// also, `Book` creates a pointer to the static object `eBookSystemIO, then
//       calls the function `GetInstance()`, which results in a deadlock.

class eBookSystemIO {
private:
    eBookSystemIO();
    static eBookSystemIO* IO;
public:
  void eBookSystemIO::PrintViewBook(const Book &object) const {
    cout << "##### Book Details #####\n";
    cout << object.ToString() << '\n';
  }
  //functions
};

class Book {
private:
    string name { };
    string author { };
    int page_count { };

public:

    void ViewBook() {
    eBookSystemIO* IO = eBookSystemIO::GetInstance();
    IO->PrintViewBook(*this);
    }
    // Functions...
};

// Just don't use functions of classes before giving them at least a declaration.
// This can be solved in two ways:

// 1- Mine: 
// I declared the function, then definde them elsewhere.
class Book;

class eBookSystemIO {
private:
    eBookSystemIO() { };
    static eBookSystemIO* IO;
public:

    static eBookSystemIO* GetInstance();
    void PrintViewBook(const Book &object) const;
};
eBookSystemIO* eBookSystemIO::IO = GetInstance(); // Gonna need to delete that, the static one.
eBookSystemIO* IO1 = eBookSystemIO::GetInstance(); // The global one.


class Book {
private:
    string name { };
    string author { };
    int page_count { };

public:
    Book() { };

    Book(const string& name, const string& author, const int& page_count) :
    name(name), author(author), page_count(page_count) { }


    void ViewBook() {
        IO1->PrintViewBook(*this);
    }

    const string ToString() const {
        ostringstream oss;
        oss << name << '\t' << author << '\t' << page_count;
        return oss.str();
    }
};


eBookSystemIO* eBookSystemIO::GetInstance() {
        if(IO == nullptr)
            IO = new eBookSystemIO();
        return IO;
}

void eBookSystemIO::PrintViewBook(const Book &object) const {
        cout << "##### Book Details #####\n";
        cout << object.ToString() << '\n';
}

// 2- Not eniterly mine, but better:
// Basicall didn't use the class functions before declaring them asln.
class Book;

class eBookSystemIO {
private:
    eBookSystemIO() { };
    static eBookSystemIO* IO;
public:

    static eBookSystemIO* GetInstance() {
        if(IO == nullptr)
            IO = new eBookSystemIO();
        return IO;
    }

    void PrintObject(const string& line) const {
        cout << "##### Book Details #####\n";
        cout << line << '\n';
    }
};
eBookSystemIO* eBookSystemIO::IO = GetInstance(); // Gonna need to delete that, the static one.
eBookSystemIO* IO_Global = eBookSystemIO::GetInstance(); // The global one.


class Book {
private:
    string name { };
    string author { };
    int page_count { };

    const string ToString() const {
        ostringstream oss;
        oss << name << '\t' << author << '\t' << page_count;
        return oss.str();
    }

public:
    Book() { };

    Book(const string& name, const string& author, const int& page_count) :
    name(name), author(author), page_count(page_count) { }


    void ViewBook() {
        string line = ToString();
        IO_Global->PrintObject(line);
    }

};


int main() {

    Book test("City of Nefaq", "Subai3i", 230);
    test.ViewBook();
    return 0;
}

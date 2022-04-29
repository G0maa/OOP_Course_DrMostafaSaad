#include "BookManager_class.h"
#include "HelperFunctions.h"

// Private:
void BookManager::LoadBooks() {
    vector<string> lines;
    ReadFile(lines, "Books.txt");
    for(int idx = 0; idx < (int) lines.size(); idx++)
        book_vec.push_back(Book(lines[idx]));
}

int BookManager::GetBooksCount() const {
    return (int) book_vec.size();
}

// Warning: No functions calls SaveBooks()!
void BookManager::SaveBooks() const {
    vector<string> out_lines;
    for(int idx = 0; idx < GetBooksCount(); idx++)
        out_lines.push_back(book_vec[idx].ToString());
    
    WriteFile(out_lines, "Books.txt");
}

// Public:
BookManager::BookManager() {
    LoadBooks();
}


void BookManager::AddBook() {
    Book new_book(0);
    for(int idx = 0; idx < GetBooksCount(); idx++) {
        if(book_vec[idx].CompareBook(new_book)) {
            PrintLineHashed("Book already exists!");
            return;
        }
    }
    book_vec.push_back(new_book);
    SaveBooks();
}


void BookManager::ViewBooks() const {
    PrintLineHashed("Book List");

    if(GetBooksCount() == 0) {
        PrintLineHashed("There aren't any books!");
        return;
    }

    cout << "\n\n####" << GetBooksCount() << "####\n\n";
    for(int idx = 0; idx < GetBooksCount(); idx++)
        cout << (idx + 1) << ": " << book_vec[idx].ToString() << '\n';
}


const Book BookManager::ChooseBook() const {
    ViewBooks();

    if(GetBooksCount() == 0)
        return Book();

    PrintLine("Choose a book: ");
    int choice = -1;
    VerifyChoice(choice, 1, GetBooksCount());

    if(choice == -1)
        return Book();

    return book_vec[choice - 1];
}


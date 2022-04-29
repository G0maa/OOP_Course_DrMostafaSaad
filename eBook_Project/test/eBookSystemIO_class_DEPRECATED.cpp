#include "eBookSystemIO_class.h"

#include <iostream>
#include <string>
#include <vector>
// #include "Book_class.h"
// #include "CustomerUser_class.h"
// #include "AdminUser_class.h"
using namespace std;

eBookSystemIO::eBookSystemIO() { }

// a set of Input Verification functions.
eBookSystemIO* eBookSystemIO::GetInstance() {
    if(IO == nullptr)
        IO = new eBookSystemIO();
    return IO;
}

void eBookSystemIO::PrintObject(const string& obj_name, const string &line) const {
    PrintLineHashed(obj_name);
    PrintLine(line);
}

void eBookSystemIO::PrintMenu(const vector<string> &lines) const {
    cout << "Choose an option:\n";
    for(int i = 1 ; i <= (int) lines.size(); i++)
        cout << i << ' ' << lines[i - 1] << '\n';
}

const int eBookSystemIO::VerifyChoice(const int &start, const int &end) const { // removed the &
    int choice = -1;
    cin >> choice;
    while(choice < start || choice > end || choice != -1) {
        cout << "Wrong choice! Try Again! Enter -1 To go back.";
        cin >> choice;
    }
    return choice;
}


void eBookSystemIO::PrintLineHashed(const string &line) const {
    cout << "##### " << line << " #####\n";
}

// I wonder if this is useful?
void eBookSystemIO::PrintLine(const string &line) const {
    cout << line;
}

// Ignore supposed verifications, also be warned of the copy.
AdminUser eBookSystemIO::InputAdmin() {
    string name;
    string password;
    PrintLineHashed("Enter Login Credntials: ");
    PrintLine("Enter Name: ");
    cin >> name;
    PrintLine("Enter Password: ");
    cin >> password;
    return AdminUser(name, password);
}

CustomerUser eBookSystemIO::InputCustomer() {
    string name;
    string password;
    PrintLineHashed("Enter Login Credntials: ");
    PrintLine("Enter name: ");
    cin >> name;
    PrintLine("Enter password: ");
    cin >> password;
    return CustomerUser(name, password);
}

AdminUser eBookSystemIO::RegisterAdmin(const int &admin_id) {
    string name { };
    string password { };
    char gender { };
    int age { };
    PrintLineHashed("Enter register details: ");
    PrintLine("Enter name: ");
    cin >> name;
    PrintLine("Enter password: ");
    cin >> password;
    PrintLine("Enter gender (M/F): ");
    cin >> gender;
    PrintLine("Enter age: ");
    cin >> age;
    return AdminUser(admin_id, name, password, gender, age);
}

CustomerUser eBookSystemIO::RegisterCustomer(const int &customer_id) {
    string name { };
    string password { };
    char gender { };
    int age { };
    PrintLineHashed("Enter register details: ");
    PrintLine("Enter name: ");
    cin >> name;
    PrintLine("Enter password: ");
    cin >> password;
    PrintLine("Enter gender (M/F): ");
    cin >> gender;
    PrintLine("Enter age: ");
    cin >> age;
    return CustomerUser(customer_id, name, password, gender, age);
}



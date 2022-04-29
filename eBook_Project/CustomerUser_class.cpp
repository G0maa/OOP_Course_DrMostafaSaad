#include "CustomerUser_class.h"

// Private:
void CustomerUser::SetLoginCredntials() {
    PrintLineHashed("Enter customer Login Credntials: ");
    PrintLine("Enter Name: ");
    cin >> name;
    PrintLine("Enter Password: ");
    cin >> password;
}


void CustomerUser::SetRegisterCredntials(const int &id_) {
    customer_id = id_;
    PrintLineHashed("Enter customer register details: ");
    PrintLine("Enter name: ");
    cin >> name;
    PrintLine("Enter password: ");
    cin >> password;
    PrintLine("Enter gender (M/F): ");
    cin >> gender;
    PrintLine("Enter age: ");
    cin >> age;
}


void CustomerUser::ViewProfile() const {
    // What does the { } do?
    vector<string> lines_a = {IntToString(customer_id), name, {"****"}, {gender}, IntToString(age)};
    vector<string> lines_b = {"Customer ID", "Name", "Password", "Gender", "Age"};
    PrintPairs(lines_b, lines_a, "Customer Profile");
}


const string& CustomerUser::GetName() const {
    return name;
}


const string& CustomerUser::GetPassword() const {
    return password;
}

CustomerUser::CustomerUser(const bool &is_login, const int &id_) {
    if(is_login == 1)
        SetLoginCredntials();
    else if(is_login == 0)
        SetRegisterCredntials(id_);
}


CustomerUser::CustomerUser(const vector<string> &splitted_line) {
    // In CustomerUsers.txt => customer_id - name - password - gender - age
    customer_id = StringToInt(splitted_line[0]);
    name = splitted_line[1];
    password = splitted_line[2];
    gender = splitted_line[3][0];
    age = StringToInt(splitted_line[4]);
}


void CustomerUser::Run() {
    vector<string> customer_menu {"View Profile", "Manage Sessions", "Logout"};
    
    sess_mngr = new SessionManager(customer_id);
    book_mngr = new BookManager();

    int choice = 0;
    while(choice != -1) {
        PrintMenu(customer_menu, "Customer Menu");
        PrintLine("Choose an option: ");
        VerifyChoice(choice, 1, 3);

        if(choice == 1)
            ViewProfile();
        else if(choice == 2)
            sess_mngr->Run(*book_mngr);
        else
            return;
    }
}


bool CustomerUser::CompareCustomer(const CustomerUser &other) const {
    if(GetName() == other.GetName() && GetPassword() == other.GetPassword())
        return true;
    else
        return false;
}


bool CustomerUser::IsLoggedIn() const {
    return (customer_id != -1);
}


const string CustomerUser::ToString() const {
    ostringstream oss;
    oss << customer_id << '\t' << name << '\t'<< password << '\t' << gender << '\t' << age;
    return oss.str();
}


CustomerUser::~CustomerUser() {
    if(book_mngr != nullptr) {
        delete book_mngr;
        book_mngr = nullptr;
    }

    if(sess_mngr != nullptr) {
        delete sess_mngr;
        sess_mngr = nullptr;
    }   
}

// Will be called in Load() only, so will set pointers of this to null.
// Even if in future a copy happens, Run() will create sess_mngr & book_mngr anyway :)
CustomerUser::CustomerUser(const CustomerUser& other) {
    this->customer_id = other.customer_id;
    this->name = other.name;
    this->password = other.password;
    this->gender = other.gender;
    this->age = other.age;
    this->sess_mngr = nullptr;
    this->book_mngr = nullptr;
}
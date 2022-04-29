#include "AdminUser_class.h" 

// Private:
void AdminUser::ViewProfile() const {
    // What does the { } do?
    vector<string> lines_a = {IntToString(admin_id), name, {"****"}, {gender}, IntToString(age)};
    vector<string> lines_b = {"Admin ID", "Name", "Password", "Gender", "Age"};
    PrintPairs(lines_b, lines_a, "Admin Profile");
}

// Only temporary => If add more functions will move to Run() in 'Book'.
void AdminUser::AddBook() {
    book_mngr->AddBook();
}

void AdminUser::SetLoginCredentials() {
    PrintLineHashed("Enter admin Login Credntials: ");
    PrintLine("Enter Name: ");
    cin >> name;
    PrintLine("Enter Password: ");
    cin >> password;
}

void AdminUser::SetRegisterCredentials(const int &id_) {
    admin_id = id_;
    PrintLineHashed("Enter admin register details: ");
    PrintLine("Enter name: ");
    cin >> name;
    PrintLine("Enter password: ");
    cin >> password;
    PrintLine("Enter gender (M/F): ");
    cin >> gender;
    PrintLine("Enter age: ");
    cin >> age;
}

const string& AdminUser::GetName() const {
    return name;
}

const string& AdminUser::GetPassword() const {
    return password;
}


AdminUser::AdminUser(const bool &is_login, const int &id) { 
    if(is_login)
        SetLoginCredentials();
    else
        SetRegisterCredentials(id);
}


AdminUser::AdminUser(const vector<string> &splitted_line) {
    // In AdminUsers.txt => admin_id - name - password - gender - age
    admin_id = StringToInt(splitted_line[0]);
    name = splitted_line[1];
    password = splitted_line[2];
    gender = splitted_line[3][0];
    age = StringToInt(splitted_line[4]);
}


void AdminUser::Run() {
    vector<string> admin_menu {"Add Book", "View Profile", "Logout"};
    
    book_mngr = new BookManager();
    int choice = 0;
    while(choice != -1) {
        PrintMenu(admin_menu, "Admin Menu");
        PrintLine("Chooce an option: ");
        VerifyChoice(choice, 1, 3);
        
        if(choice == 1)
            AddBook();
        else if(choice == 2)
            ViewProfile();
        else
            return;
    }
}


bool AdminUser::CompareAdmin(const AdminUser &other) const {
    if(GetName() == other.GetName() && GetPassword() == other.GetPassword())
        return true;
    else
        return false;
}


bool AdminUser::IsLoggedIn() const {
    return (admin_id != -1);
}

// Won't create getters for all of those.
const string AdminUser::ToString() const {
    ostringstream oss;
    oss << admin_id << '\t' << name << '\t'<< password <<  '\t' << gender << '\t' << age;
    return oss.str();
}

AdminUser::AdminUser(const AdminUser& other) {
    this->admin_id = other.admin_id;
    this->name = other.name;
    this->password = other.password;
    this->gender = other.gender;
    this->age = other.age;
    this->book_mngr = nullptr;
}

AdminUser::~AdminUser() {
    if(book_mngr != nullptr) {
        delete book_mngr;
        book_mngr = nullptr;
    }
}
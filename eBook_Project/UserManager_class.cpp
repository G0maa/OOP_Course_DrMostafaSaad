#include "UserManager_class.h"

// Private:
// For CustomerUser & AdminUser constructors: 1 for login, 0 for register.
void UserManager::LoginAdmin() {
    cur_admin = new AdminUser(1); 

    for(int idx = 0; idx < (int) admin_vec.size(); idx++)
        if(cur_admin->CompareAdmin(admin_vec[idx]))
            cur_admin = &admin_vec[idx]; // Does assignment opeartor in this case does a copy?
}

void UserManager::LoginCustomer() {
    cur_customer = new CustomerUser(1);

    for(int idx = 0; idx < (int) customer_vec.size(); idx++)
        if(cur_customer->CompareCustomer(customer_vec[idx]))
            cur_customer = &customer_vec[idx];
}

void UserManager::RegisterAdmin() {
    admin_vec.push_back(AdminUser(0, NewAdminID()));
    cur_admin = &admin_vec.back();
}

void UserManager::RegisterCustomer() {
    customer_vec.push_back(CustomerUser(0, NewCustomerID()));
    cur_customer = &customer_vec.back();
}

// Use ReadFile() or ReadFileSplit()?
void UserManager::LoadUsers() {
    vector<vector<string>> lines_vec;
    ReadFileSplit(lines_vec, "AdminUsers.txt");
    for(int idx = 0; idx < (int) lines_vec.size(); idx++)
        admin_vec.push_back(AdminUser(lines_vec[idx]));

    lines_vec.clear();

    ReadFileSplit(lines_vec, "CustomerUsers.txt");
    for(int idx = 0; idx < (int) lines_vec.size(); idx++)
        customer_vec.push_back(CustomerUser(lines_vec[idx]));
}

// Not very efficient.
void UserManager::SaveUsers() const {
    vector<string> out_lines;
    for(int idx = 0; idx < (int) admin_vec.size(); idx++)
        out_lines.push_back(admin_vec[idx].ToString());
    
    WriteFile(out_lines, "AdminUsers.txt");

    out_lines.clear();

    for(int idx = 0; idx < (int) customer_vec.size(); idx++)
        out_lines.push_back(customer_vec[idx].ToString());
    
    WriteFile(out_lines, "CustomerUsers.txt");
}

const int UserManager::NewAdminID() const {
    return (int) admin_vec.size();
}

const int UserManager::NewCustomerID() const {
    return (int) customer_vec.size();
}

// Public:
UserManager::UserManager() { }

// I think this function could have been split to different functions.
// Consider: If user enters -1, as in VerifyChoice(), program will terminate.
// Consider: Turning this to while instead of using recursion.
void UserManager::Run() {
    customer_vec.clear();
    admin_vec.clear();

    vector<string> main_menu {"Login", "Register"};

    PrintMenu(main_menu, "Main Menu");
    PrintLine("Chooce an option: "); 
    int choice = -1;
    VerifyChoice(choice, 1, 2);

    LoadUsers();
    if(choice == 1) {
        vector<string> login_menu {"Login Customer", "Login Admin"};
        PrintMenu(login_menu, "Login Menu");
        PrintLine("Chooce an option: ");

        choice = -1;
        VerifyChoice(choice, 1, 2);

        if(choice == 1)
            LoginCustomer();
        else if(choice == 2)
            LoginAdmin();

    } 
    else if(choice == 2) {
        vector<string> register_menu {"Register Custoemr", "Register Admin"};
        PrintMenu(register_menu, "Register Menu");
        PrintLine("Chooce an option: ");

        int choice = -1;
        VerifyChoice(choice, 1, 2);

        if(choice == 1)
            RegisterCustomer();
        else if(choice == 2)
            RegisterAdmin();
    }

    // first condition because I didn't inititalize them in the constructor
    if(cur_admin && cur_admin->IsLoggedIn())
        cur_admin->Run();
    else if(cur_customer && cur_customer->IsLoggedIn())
        cur_customer->Run();
    else {
        PrintLineHashed("Login or Register Failed! Enter 1 to try again: ");
        choice = -1;
        VerifyChoice(choice, 1, 1);
        if(choice == 1)
            Run();
    }
        
    SaveUsers(); // slightly inefficient.
}

UserManager::~UserManager() {
    if(cur_admin != nullptr) {
        delete cur_admin;
        cur_admin = nullptr;
    }

    if(cur_customer != nullptr) {
        delete cur_customer;
        cur_customer = nullptr;
    }
}

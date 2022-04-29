#ifndef CUSTOMERUSER_CLASS_H_
#define CUSTOMERUSER_CLASS_H_

#include "SessionManager_class.h"
#include "BookManager_class.h"

class CustomerUser {
private:
    int customer_id { -1 };
    string name { };
    string password { };
    char gender { };
    int age { };

    SessionManager *sess_mngr { };
    BookManager *book_mngr { };

    void ViewProfile() const;
    void SetLoginCredntials();
    void SetRegisterCredntials(const int &id_);
    const string& GetName() const;
    const string& GetPassword() const;

public:
    CustomerUser(const bool &is_login, const int &id_ = -1);
    CustomerUser(const vector<string> &splitted_line);
    CustomerUser(const CustomerUser& other);
    
    void Run();
    bool IsLoggedIn() const;
    bool CompareCustomer(const CustomerUser &other) const;
    const string ToString() const;

    ~CustomerUser();
    
    // CustomerUser(const CustomerUser&) = delete;
    void operator=(const CustomerUser&) = delete;
};

#endif
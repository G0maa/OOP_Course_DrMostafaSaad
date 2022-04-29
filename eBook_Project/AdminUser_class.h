#ifndef ADMINUSER_CLASS_H_
#define ADMINUSER_CLASS_H_

#include <string>
#include "HelperFunctions.h"
#include "BookManager_class.h"

using namespace std;

class AdminUser {
private:
    int admin_id { -1 };
    string name { };
    string password { };
    char gender { };
    int age { };

    BookManager *book_mngr { };

    void ViewProfile() const;
    void AddBook();
    void SetLoginCredentials();
    void SetRegisterCredentials(const int &id_);
    const string& GetName() const;
    const string& GetPassword() const;
    
public:

    AdminUser(const bool &is_login, const int &id = -1);
    AdminUser(const vector<string> &splitted_line);
    AdminUser(const AdminUser &other);

    void Run();
    bool CompareAdmin(const AdminUser &other) const;
    bool IsLoggedIn() const;
    const string ToString() const;

    // AdminUser(const AdminUser&) = delete;
    void operator=(const AdminUser&) = delete;

    ~AdminUser();
};

#endif /* ADMINUSER_CLASS_H_ */
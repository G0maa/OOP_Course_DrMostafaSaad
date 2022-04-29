#ifndef USERMANAGER_CLASS_H_
#define USERMANAGER_CLASS_H_

#include <string>
#include "HelperFunctions.h"
#include "AdminUser_class.h"
#include "CustomerUser_class.h"

using namespace std;

class UserManager {
private:
    AdminUser *cur_admin { };
    CustomerUser *cur_customer { };
    vector<AdminUser> admin_vec;
    vector<CustomerUser> customer_vec;

    void LoginAdmin();

    void LoginCustomer();

    void RegisterAdmin();

    void RegisterCustomer();

    void LoadUsers();

    void SaveUsers() const;

    const int NewAdminID() const;

    const int NewCustomerID() const;
    
public:
    UserManager();

    void Run();

    ~UserManager();

    UserManager(const UserManager&) = delete;
    void operator=(const UserManager&) = delete;
};

#endif /* USERMANAGER_CLASS_H_ */
#include <bits/stdc++.h>
using namespace std;

// I tried really hard to make the idea of separating Model from View work,
// but I couldn't, more information can be found in Notes.txt.
// #include "eBookSystemIO_class.h"

#include "HelperFunctions.h"
#include "Date_class.h"
#include "Book_class.h"
#include "Session_class.h"
#include "SessionManager_class.h"
#include "BookManager_class.h"
#include "CustomerUser_class.h"
#include "AdminUser_class.h"
#include "UserManager_class.h"


class eBookSystem {
private:
    UserManager usr_mngr;
public:
    eBookSystem() { }

    void Run() {
        usr_mngr.Run();
    }

    eBookSystem(const eBookSystem&) = delete;
    void operator=(const eBookSystem&) = delete;
};


int main() {
    eBookSystem service;
    service.Run();

    cout << "Bye :)\n";
    return 0;
}
#ifndef EBOOKSYSTEMIO_CLASS_H_
#define EBOOKSYSTEMIO_CLASS_H_

// Should I include these here too? or is the .cpp enough?
#include <iostream>
#include <string>
#include <vector>
#include "Book_class.h"
#include "CustomerUser_class.h"
#include "AdminUser_class.h"

using namespace std;

// I wonder if I did that right, separating Model from View.
class eBookSystemIO {
private:
    eBookSystemIO();
    static eBookSystemIO* IO;
public:
    // a set of Input Verification functions.
    static eBookSystemIO* GetInstance();
    void PrintObject(const string&obj_name, const string&line) const;
    void PrintMenu(const vector<string> &lines) const;
    const int VerifyChoice(const int &start, const int &end) const;
    void PrintLineHashed(const string &line) const;

    // I wonder if this is useful?
    void PrintLine(const string &line) const;

    // Ignore supposed verifications, also be warned of the copy.
    AdminUser InputAdmin();
    CustomerUser InputCustomer();
    AdminUser RegisterAdmin(const int &admin_id);
    CustomerUser RegisterCustomer(const int &customer_id);
};

#endif /* EBOOKSYSTEMIO_CLASS_H_ */
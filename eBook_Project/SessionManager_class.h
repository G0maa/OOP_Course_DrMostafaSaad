#ifndef SESSIONMANAGER_CLASS_H_
#define SESSIONMANAGER_CLASS_H_

#include <bits/stdc++.h>
#include "HelperFunctions.h"
#include "Session_class.h"
#include "Book_class.h"
#include "BookManager_class.h"

using namespace std;

class SessionManager {
private:
    int user_id { -1 };
    Session *cur_sess { };
    map<int, vector<Session>> user_id_to_user_sessions;

    void NewSession(const BookManager &book_mngr);
    void ChooseSession();
    void ViewSessions() const;
    void LoadSessions();
    void SaveSessions();
    vector<Session>& GetSessionVector(const int& user_id);
    const vector<Session>& IsExistSessionVector(const int &user_id) const;
public:

    SessionManager(const int &user_id);
    void Run(const BookManager &book_mngr);
    
    ~SessionManager();

    SessionManager(const SessionManager&) = delete;
    void operator=(const SessionManager&) = delete;
};

#endif
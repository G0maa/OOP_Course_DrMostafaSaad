#include "SessionManager_class.h"
#include <bits/stdc++.h>
// Private:
void SessionManager::NewSession(const BookManager &book_mngr) {
    const Book book_obj(book_mngr.ChooseBook());
    
    if(book_obj.CompareBook(Book())) // aka if nothing.
        return;

    vector<Session> &temp = GetSessionVector(user_id);
    for(int idx = 0; idx < (int) temp.size(); idx++) {
        if(temp[idx].CompareSessionBook(book_obj)) {
            cout << "A session of this book alreay exists!\n";
            return;
        }
    }

    temp.push_back(Session(user_id, 1, book_obj));
    cur_sess = &temp.back();
}

// I got to learn templates.
void SessionManager::ChooseSession() {
    PrintLineHashed("Old Sessions");

    vector<Session> &temp = GetSessionVector(user_id);
    if(temp.size() == 0) {
        PrintLineHashed("No old sessions!");
        return;
    }
    
    ViewSessions();
    
    int choice = -1;
    PrintLine("Choose a Session ID: ");
    VerifyChoice(choice, 1, (int) temp.size());

    if(choice == -1)
        return;

    cur_sess = &temp[choice - 1];
}

void SessionManager::ViewSessions() const{
    PrintLine("# SessionID - Stopped at Page - Book Details(Book Name - Book Author - Page Count) - Last Read at (Year - Month - day) #");
    PrintLine("\n");

    const vector<Session> &temp = IsExistSessionVector(user_id);

    // Might not work correctly, find() returns map::end.
    if(temp.size() == 0)
        PrintLineHashed("Sessions are embty!");

    for(int idx = 0; idx < (int) temp.size(); idx++)
        cout << (idx + 1) << '\t' << temp[idx].ToString() << '\n';
    
}

// Note: It loads all sessions, even if it's not of that particular user.
void SessionManager::LoadSessions() {
    vector<string> lines;
    ReadFile(lines, "Sessions.txt");
    for(int idx = 0; idx < (int) lines.size(); idx++) {

        // Sessions.txt => user_id - cur_page | name - author - page_count | year - month - day
        vector<string> splitted_string;
        SplitString(splitted_string, lines[idx]);

        vector<string> session_line;
        session_line.push_back(splitted_string[0]);
        session_line.push_back(splitted_string[1]);

        vector<string> book_line;
        book_line.push_back(splitted_string[2]);
        book_line.push_back(splitted_string[3]);
        book_line.push_back(splitted_string[4]);

        vector<string> date_line;
        date_line.push_back(splitted_string[5]);
        date_line.push_back(splitted_string[6]);
        date_line.push_back(splitted_string[7]);

        Session temp(session_line, Book(book_line), Date(date_line));

        vector<Session> &it = GetSessionVector(temp.GetUserID());
        it.push_back((temp));
    }
}


vector<Session>& SessionManager::GetSessionVector(const int &user_id) {
    pair<int, vector<Session>> temp = {user_id, vector<Session>()};

    map<int, vector<Session>>::iterator it = user_id_to_user_sessions.insert(temp).first;

    return it->second;    
}


const vector<Session>& SessionManager::IsExistSessionVector(const int &user_id) const{
    map<int, vector<Session>>::const_iterator it = user_id_to_user_sessions.find(user_id);
    return it->second;    
}

// Important Note: Sessions.txt has redundency, book object is saved once in Books.txt, and once again in Sessions.txt
// Couldn't make this one without const. even when using const_iterator.
void SessionManager::SaveSessions() {
    vector<string> out_lines;

    map<int, vector<Session>>::iterator it;
    for(it = user_id_to_user_sessions.begin(); it != user_id_to_user_sessions.end(); it++)
        for(int idx = 0; idx < it->second.size(); idx++)
            out_lines.push_back(it->second[idx].ToString());
            
    WriteFile(out_lines, "Sessions.txt");
}


SessionManager::SessionManager(const int &user_id) : user_id(user_id) { }

void SessionManager::Run(const BookManager &book_mngr) {
    vector<string> session_mngr_menu {"View/Choose Session", "New Session", "Resume Session", "Go back"};

    user_id_to_user_sessions.clear();
    LoadSessions();

    int choice = 0;
    while(choice != -1) {
        PrintMenu(session_mngr_menu, "Session Manager Menu");
        PrintLine("Choose an option: ");
        VerifyChoice(choice, 1, 4);

        if(choice == 1)
            ChooseSession();
        else if(choice == 2)
            NewSession(book_mngr);
        else if(choice == 3) {
            if(cur_sess != nullptr)
                cur_sess->Run();
            else
                PrintLineHashed("!ERROR!: Please Choose a session from #1 first!");
        }
        else {
            SaveSessions();
            return;
        }
    }
}

SessionManager::~SessionManager() {
    if(cur_sess != nullptr) {
        delete cur_sess;
        cur_sess = nullptr;
    }
}

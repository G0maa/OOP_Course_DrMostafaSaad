#include <bits/stdc++.h>
using namespace std;

// I think this is an abnormal number of constants.
const int DUMMY_VALUE = -1;
const int THREAD_END = -10;
const int QUESTION_NOT_FOUND = -1;
const int GET_ALL_QUESTIONS = -10;
const int GET_ALL_THREADS = -11;

const string EMPTY_STRING = "";

const int QUESTION_ID_COL = 0;
const int ASKER_ID_COL = 1;
const int ASKED_ID_COL = 2;
const int QUESTION_DATA_COL = 3;
const int ANSWER_DATA_COL = 4;
const int IS_AQ_COL = 5;
const int NEXT_QUESTION_COL = 6;

const int USER_ID = 0;
const int USER_NAME = 1;
const int USER_USERNAME = 3;
const int USER_PASSWORD = 4;
const int USER_AQ = 5;


struct UserDetails {
        int uid = { DUMMY_VALUE };
        string name = { EMPTY_STRING };
        string email = { EMPTY_STRING };
        string username = { EMPTY_STRING };
        string password = { EMPTY_STRING };
        bool anonymous = { };
        

        UserDetails() { }
        UserDetails(int uid, string name, string email, string username, string password, bool anonymous) :
            uid(uid), name(name), email(email), username(username), password(password), anonymous(anonymous) { }

        UserDetails(const string &record) {
        string word;
        stringstream sep(record);
        vector<string> db_userdetails;

        while(getline(sep, word, '\t'))
            db_userdetails.push_back(word);

        uid = stoi(db_userdetails[USER_ID]);
        username =  db_userdetails[USER_NAME];
        anonymous = stoi(db_userdetails[USER_AQ]);
    }
};

// QuestionID - AskerID - AskedID - Question - Answer - isAQ - Next Question
struct QuestionDetails {
    int question_id = { DUMMY_VALUE };
    int asker_id = { DUMMY_VALUE };
    int asked_id = { DUMMY_VALUE };
    int next_question = { DUMMY_VALUE }; // for threaded questions.
    bool is_aq = { };
    string question_data = { EMPTY_STRING };
    string answer_data = { EMPTY_STRING };
    QuestionDetails() { }

    // Ah... doesnt' look pretty.
    QuestionDetails(int question_id, int asker_id, int asked_id, string question_data, string answer_data, bool is_aq, int next_question) : 
                    question_id(question_id), asker_id(asker_id), asked_id(asked_id), 
                    question_data(question_data), answer_data(answer_data), is_aq(is_aq), next_question(next_question) { }

    QuestionDetails(const string &record) {
        string word;
        stringstream sep(record);
        vector<string> db_questiondetails;

        while(getline(sep, word, '\t'))
            db_questiondetails.push_back(word);

        // Can't delegate to the other constructor, will create another object that is lost instead.
        question_id = stoi(db_questiondetails[QUESTION_ID_COL]);
        asker_id = stoi(db_questiondetails[ASKER_ID_COL]);
        asked_id = stoi(db_questiondetails[ASKED_ID_COL]);
        question_data = db_questiondetails[QUESTION_DATA_COL];
        answer_data = db_questiondetails[ANSWER_DATA_COL];
        is_aq = stoi(db_questiondetails[IS_AQ_COL]);
        next_question = stoi(db_questiondetails[NEXT_QUESTION_COL]);
    }

    const int& GetCol(const int& col) const {
        if(col == 1)
            return asker_id;
        else // col == 2
            return asked_id;
    }
};

class Searcher {
public:
    Searcher() { }

    UserDetails SearchUser(int &id) const {
        fstream ReadThis;
        ReadThis.open("users.csv", fstream::in);
        
        string record;
        // first row in the csv.
        getline(ReadThis, record);
        while(getline(ReadThis, record)) {
            UserDetails searched_user(record);
            
            if(id == searched_user.uid) {
                ReadThis.close();
                return searched_user;
            }
        }
        ReadThis.close();
        return UserDetails(); // has -1 by defualt.
    }

    void SearchQuestion(QuestionDetails &question) const {
        fstream ReadThis; // #repeated2 KINDA SOLVED
        ReadThis.open("questions.txt", fstream::in);
        string record;

        // getting rid of first row
        getline(ReadThis, record);

        while(getline(ReadThis, record)) {
            QuestionDetails searched_question(record);
            
            if(question.question_id == searched_question.question_id) {
                question = searched_question; // !!! COPY WARNING !!!
                ReadThis.close();
                return;
            }
        }
        question.question_id = DUMMY_VALUE; // not found
        ReadThis.close();
        return;
    }

    void GetQuestions(vector<QuestionDetails> &questions, int user_id, bool get_from_me, bool get_threads = false) const {
        fstream ReadThis;
        ReadThis.open("questions.txt", fstream::in);
        string record;

        // getting rid of first row
        getline(ReadThis, record);

        while(getline(ReadThis, record)) {
            QuestionDetails question(record);

            if(user_id == GET_ALL_QUESTIONS && question.next_question == DUMMY_VALUE)
                questions.push_back(question);
            else if(user_id == GET_ALL_THREADS && question.next_question != DUMMY_VALUE)
                questions.push_back(question);
            else if(get_from_me && get_threads && user_id == question.asker_id && question.next_question != DUMMY_VALUE)
                questions.push_back(question);
            else if(get_from_me && !get_threads && user_id == question.asker_id && question.next_question == DUMMY_VALUE)
                questions.push_back(question);
            else if(!get_from_me && get_threads && user_id == question.asked_id && question.next_question != DUMMY_VALUE)
                questions.push_back(question);
            else if(!get_from_me && !get_threads && user_id == question.asked_id && question.next_question == DUMMY_VALUE)
                questions.push_back(question);
        }
        ReadThis.close();
        return;
    }

    // Get me all threads of said user, sort them using the already existing function,
    // Search for the question given in the sorted threads, push_back everything before it until you reach
    // a question.next_question == THREAD_END.
    void SearchThread(vector<QuestionDetails> &thread, QuestionDetails &question) {
        vector<QuestionDetails> all_user_threads;
        GetQuestions(all_user_threads, question.asked_id, false, true); // get_from_me, get_threads
        SortThreads(all_user_threads);

        int end_index = SearchThreadsVector(all_user_threads, question.question_id); // no error handling whatsoever

        // Not limiting users by entering last question in thread, but this will add another O(nlogn).
        while(all_user_threads[end_index].next_question != THREAD_END)
            end_index = SearchThreadsVector(all_user_threads, all_user_threads[end_index].next_question);
            
        thread.push_back(all_user_threads[end_index]);
        end_index--;
        while(end_index >= 0 && all_user_threads[end_index].next_question != THREAD_END) {
            thread.push_back(all_user_threads[end_index]);
            end_index--;
        }
    }

    int SearchThreadsVector(const vector<QuestionDetails> &threads, const int &target) const {
        int start = 0, end = threads.size() - 1, mid = -1; // @OmarNobel
        while(start <= end) {
            mid = (start + end) / 2; // << not-recommended
            if(threads[mid].question_id == target)
                return mid;
            else if(threads[mid].question_id > target)
                end = mid - 1;
            else
                start = mid + 1;
        }
        return -1;
    }

    // O(nlogn)?
    // This function bugged for about 4 times now.
    void SortThreads(vector<QuestionDetails> &threads) { 
        // sort those threads... Pure problem sovling :D I am finally using binary search.
        vector<QuestionDetails> sorted_threads;
        int num_threads = threads.size();
        bool visited_questions[num_threads] = {0}; // too many. num_threads / 2
        
        for(int idx = 0; idx < num_threads; idx++) {
            if(!visited_questions[idx]) {
                sorted_threads.push_back(threads[idx]);
                visited_questions[idx] = 1;
                int next_idx = SearchThreadsVector(threads, threads[idx].next_question);
                
                while(threads[next_idx].next_question != THREAD_END) {
                    visited_questions[next_idx] = 1;
                    sorted_threads.push_back(threads[next_idx]);
                    next_idx = SearchThreadsVector(threads, threads[next_idx].next_question);
                }
                // Revise this Spaghittti
                visited_questions[next_idx] = 1;
                sorted_threads.push_back(threads[next_idx]);
            }
        }
        threads = sorted_threads; // !!! swap and delete old one? !!!
    }
};


class Questions {
private:
    Searcher searcherObj;
    int user_id = { };    
    bool anon_q { };

    void AddQuestion(QuestionDetails &newQuestion) const {
        fstream ReadThis;
        ReadThis.open("questions.txt", fstream::app);

        newQuestion.question_id = IncrementQuestions() - 1;

        ReadThis << newQuestion.question_id << '\t' << newQuestion.asker_id << '\t' 
                 << newQuestion.asked_id << '\t' << newQuestion.question_data << '\t' << newQuestion.answer_data<< '\t'
                 << newQuestion.is_aq << '\t' << newQuestion.next_question << '\n';

        ReadThis.close();
    }

    int IncrementQuestions() const {
        string file_in;
        fstream Reader;
        Reader.open("question_num.txt", fstream::in);

        getline(Reader, file_in);
        int question_num = stoi(file_in);
        question_num++;
        
        Reader.close();
        remove("question_num.txt");
        
        Reader.open("question_num2.txt", fstream::out);
        Reader << question_num;
        Reader.close();

        rename("question_num2.txt", "question_num.txt");
        return question_num;
    }

    void DeleteFoundQuestion(QuestionDetails &question, bool virtual_delete = false) const {
        fstream WriteThis;
        WriteThis.open("questions2.txt", fstream::out);

        fstream ReadThis;
        ReadThis.open("questions.txt", fstream::in);
        string record, word;

        // adding the first row
        getline(ReadThis, record);
        WriteThis << record << '\n';

        while(getline(ReadThis, record)) {
            QuestionDetails found_question(record);
            
            if(question.question_id != found_question.question_id)
                WriteThis << record << '\n';
            else if(virtual_delete) { // for threads only, I was too lazy to copy same function only for this purpose
                WriteThis << found_question.question_id << '\t' << found_question.asker_id << '\t' << found_question.asked_id << '\t' <<
                "DELETED QUESTION" << '\t' << "DELETED ANSWER" << '\t' << 
                found_question.is_aq << '\t' << found_question.next_question << '\n';
            }
        }

        ReadThis.close();
        WriteThis.close();
        remove("questions.txt");
        rename("questions2.txt", "questions.txt");
        return;
    }

    void DeleteFoundThread(QuestionDetails question) {
        vector<QuestionDetails> thread;
        searcherObj.SearchThread(thread, question);
        int thread_len = thread.size();

        // a bit slow, although *kinda* sorted (reversed),
        // would need a better DeleteFoundQuestion(), or new function.
        for(int idx = 0; idx < thread_len; idx++) 
            DeleteFoundQuestion(thread[idx]);
    }

    QuestionDetails ThreadHandler(const int &asked_uid) {
        QuestionDetails thread;
        cout << "Enter Thread ID: ";
        cin >> thread.question_id;

        searcherObj.SearchQuestion(thread);
        if(thread.question_id == DUMMY_VALUE)
            cout << "!!ERROR!! Thread ID does not exist.\n";
        else if(thread.asked_id != thread.asked_id) {
            cout << "!!ERROR!! Thread does not belong to the same asked user!\n";    
            thread.question_id = DUMMY_VALUE;
        }
        else if(thread.next_question != DUMMY_VALUE && thread.next_question != THREAD_END) {
            vector<QuestionDetails> entire_thread;
            searcherObj.SearchThread(entire_thread, thread);
            thread = entire_thread[0]; // !!! COPY WARNING !!!
        }
        return thread;
    }

    void AddQuestionInOrder(const QuestionDetails &thread) const {
        fstream WriteThis, ReadThis;  // #repeated2
        WriteThis.open("questions2.txt", fstream::out);
        ReadThis.open("questions.txt", fstream::in);
        string record;
       
        // adding the first row
        getline(ReadThis, record);
        WriteThis << record << '\n';

        while(getline(ReadThis, record)) {
            QuestionDetails question(record);

            if(thread.question_id == question.question_id)
                WriteThis << thread.question_id << '\t' << thread.asker_id << '\t' << thread.asked_id
                          << '\t' << thread.question_data<< '\t' << thread.answer_data << '\t' << thread.is_aq << '\t' << thread.next_question << '\n';
            else
                WriteThis << record << '\n';

        }
        ReadThis.close();
        WriteThis.close();
        remove("questions.txt");
        rename("questions2.txt", "questions.txt");
        return;
    }
    
    void CoutQuestions(vector<QuestionDetails> &questions) const {
        int len = (int) questions.size();
        for(int idx = 0; idx < len; idx++) {
            cout << "Question ID (" << questions[idx].question_id << ") ";

            if(questions[idx].is_aq)
                cout << "From User ID (\?\?\?)";
            else
                cout << "From User ID (" << questions[idx].asker_id << ")";

            cout << " To User ID (" << questions[idx].asked_id << ")\n";
            cout << "\tQuestion: " << questions[idx].question_data << '\n';
            cout << "\t\tAnswer: " << questions[idx].answer_data << '\n';
        }
    }

    void CoutThreads(vector<QuestionDetails> &threads) const {
        int len = (int) threads.size();
        for(int idx = 0; idx < len; idx++) {
            if(idx == 0 || threads[idx - 1].next_question == THREAD_END)
                cout << "Thread Parent: ";
            else
                cout << "Thread Question: ";

            cout << "Question ID (" << threads[idx].question_id << ") from user ID ("; // repeated.
            if(threads[idx].is_aq)
                cout << "???";
            else
                cout << threads[idx].asker_id;

            cout << ") To user ID (" << threads[idx].asked_id << ")\n\tQuestion: " << threads[idx].question_data 
            << "\n\t\tAnswer: " << threads[idx].answer_data << '\n';

            // if(threads[idx].next_question == -10) Not needed really.
            //     cout << "Thread ID (" << threads[idx].question_id << ").\n";
        }
    }

    // This function can be improved by overloading << operator and just general logic improvement.
    void UpdateAnswer(const QuestionDetails &question) const { 
        int cur_id = question.question_id;
        int last_id = 0;
        int after_id = 0;
        bool inserted = false;
        fstream WriteThis, ReadThis;  // #repeated2
        WriteThis.open("questions2.txt", fstream::out);
        ReadThis.open("questions.txt", fstream::in);
        string record;
       
        // adding the first row .-.
        getline(ReadThis, record);
        WriteThis << record << '\n';

        while(getline(ReadThis, record)) {
            QuestionDetails parsed_question(record);
            
            after_id = parsed_question.question_id;
            if(question.question_id == after_id) {
                cout << "Warning: Answer has been overwritten.\n";
                WriteThis << question.question_id << '\t' << question.asker_id << '\t' 
                          << question.asked_id << '\t' << question.question_data 
                          << '\t'<< question.answer_data << '\t' << question.is_aq 
                          << '\t' << question.next_question << '\n';
                inserted = true;
            }
            else if(question.question_id > last_id && question.question_id <= after_id) { // = for cases. 0 0 0
                WriteThis << question.question_id << '\t' << question.asker_id << '\t' 
                          << question.asked_id << '\t' << question.question_data 
                          << '\t'<< question.answer_data << '\t' << question.is_aq 
                          << '\t' << question.next_question << '\n';
                WriteThis << record << '\n';
                inserted = true;
            }
            else
                WriteThis << record << '\n';

            last_id = after_id;
        }
        
        if(!inserted)
            WriteThis << question.question_id << '\t' << question.asker_id << '\t' 
                << question.asked_id << '\t' << question.question_data 
                << '\t'<< question.answer_data << '\t' << question.is_aq 
                << '\t' << question.next_question << '\n';
        ReadThis.close();
        WriteThis.close();
        remove("questions.txt");
        rename("questions2.txt", "questions.txt");
        return;
    }

    const int& GetUserID() {
        return user_id;
    }

public:
    Questions() { }

    void setQuestions(int &userID, bool &anon_q_) {
        user_id = userID;
        anon_q = anon_q_;
    }

    void PrintQuestions(const bool &get_from_me, const bool &get_feed = false) {
        vector<QuestionDetails> questions;
        vector<QuestionDetails> threads;

        if(get_feed) {
            searcherObj.GetQuestions(questions, GET_ALL_QUESTIONS, get_feed);
            searcherObj.GetQuestions(threads, GET_ALL_THREADS, get_feed, true);
        }
        else {
            searcherObj.GetQuestions(questions, user_id, get_from_me);
            searcherObj.GetQuestions(threads, user_id, get_from_me, true);
        }

        CoutQuestions(questions); // Printing questions normally

        if(!get_from_me || get_feed) { // Threads from me are not to be sorted.
            searcherObj.SortThreads(threads);
            CoutThreads(threads);
        }
        else {
            cout << "\n||These next Questions are parts of threads, to see complete thread go to Feed.||\n";
            CoutQuestions(threads);
        }
    }

    // Again this function can be improved.
    void AskQuestion() {
        QuestionDetails newQuestion;
        int asked_uid = DUMMY_VALUE;
        cout << "Enter User id or -1 to cancel: ";
        cin >> asked_uid;
        if(asked_uid == DUMMY_VALUE)
            return;
        
        UserDetails asked_userdetails = searcherObj.SearchUser(asked_uid);
        if(asked_userdetails.uid == DUMMY_VALUE) {
            cout << "!!ERROR!! This User ID does not exist!\n";
            return;
        }

        bool isAQ = 0; // is bad?
        if(asked_userdetails.anonymous == 0)
            cout << "Note: This user doesn't accept anonymous questions!\n";
        else {
            cout << "Is this questions anonymous? (0: NO 1: YES) ";
            cin >> isAQ;
        }

        QuestionDetails thread;
        int is_thread = -1;
        cout << "Is this a follow-up quesiton? (thread) (0: NO 1: YES) ";
        cin >> is_thread;
        if(is_thread) {
            thread = ThreadHandler(asked_uid); // kinda bad.
            if(thread.question_id == DUMMY_VALUE)
                return;
        }

        string question;
        cout << "Enter your question: \n";
        getline(cin >> ws, question);

        newQuestion.asker_id = GetUserID();
        newQuestion.asked_id = asked_uid;
        newQuestion.question_data = question;
        newQuestion.is_aq = isAQ;
        if(is_thread)
            newQuestion.next_question = THREAD_END;
        AddQuestion(newQuestion);

        if(is_thread) {
            thread.next_question = newQuestion.question_id;
            AddQuestionInOrder(thread);
        }
    }

    void AnswerQuestion() {
        QuestionDetails SearchedQusetion;
        cout << "Enter quesiton id or -1 to cancel: ";
        cin >> SearchedQusetion.question_id;
        cout << '\n';
        
        searcherObj.SearchQuestion(SearchedQusetion);
        if(SearchedQusetion.question_id == DUMMY_VALUE || SearchedQusetion.asked_id != GetUserID()) {
            cout << "Question does not exist, or wrong ID.\n";
            return;
        }

        // If overwritten -> Delete then insert
        // Complexity wise this adds more n iterations.
        if(SearchedQusetion.answer_data != "") {
            int choice = 0;
            cout << "Warning: There's an answer already for said question, it will be overwritten (1:OK, Other: Return)";
            cin >> choice;
            if(choice != 1)
                return;
        }
        
        string answer;
        cout << "Enter you answer: ";
        getline(cin >> ws, answer);
        SearchedQusetion.answer_data = answer;

        UpdateAnswer(SearchedQusetion);
    }

    void DeleteQuestion() {
        QuestionDetails question;
        cout << "Enter Questiond ID or -1 to cancel: ";
        cin >> question.question_id;
        cout << '\n';

        searcherObj.SearchQuestion(question);
        if(question.question_id == DUMMY_VALUE || question.asked_id != GetUserID()) {
            cout << "!!ERROR!! Question not found or wrong ID.\n";
            return;
        }

        if(question.next_question == DUMMY_VALUE)
            DeleteFoundQuestion(question);
        else {
            int choice = 0;
            cout << "This question is part of thread, delete this question only or entire thread?\n";
            cout << "1- This Question Only\n2- Entire thread (other to cancel): ";
            cin >> choice;
            if(choice == 1)
                DeleteFoundQuestion(question, true); // "virtual" delete
            else if(choice == 2)
                DeleteFoundThread(question);
            else
                return;
        }
        
    }
};


class User {
private:
    int user_id = {DUMMY_VALUE};
    bool anon_q = { };
    Questions questionsObj;

    User(User &another) {
        cout << "\n WARNING: THERE HAPPEND A COPY FOR CLASS: 'USER'\n";
    }

    void UserSetter(const int &user_id_, const int &anon_q_) {
        user_id = user_id_;
        anon_q = anon_q_;
        questionsObj.setQuestions(user_id, anon_q); // !!! Setter !!!
    }

    bool VerifyLogin(string is_username, string is_password){
        fstream ReadThis;
        ReadThis.open("users.csv", fstream::in);
        string record, word;

        while(getline(ReadThis, record)) {
            // This was not parsed because I need password & username which the parsing function doesn't give.
            vector<string> db_userdetails;
            stringstream sep(record);
            while(getline(sep, word, '\t'))
                db_userdetails.push_back(word);
            
            if(is_username == db_userdetails[USER_USERNAME] && is_password == db_userdetails[USER_PASSWORD]) {
                int user_id_ = stoi(db_userdetails[USER_ID]);
                int anon_q_ = db_userdetails[5][0] - '0'; // anonymous question
                UserSetter(user_id_, anon_q_);
                ReadThis.close();
                return true;
            }
        }
        ReadThis.close();
        return false;
    }

    int IncrementUsers() const {
        string file_in;
        fstream Reader;

        Reader.open("users_num.txt", fstream::in);

        getline(Reader, file_in);
        int users_num = stoi(file_in);
        users_num++;

        Reader.close();
        remove("users_num.txt");
        
        Reader.open("users_num2.txt", fstream::out);
        Reader << users_num;
        Reader.close();

        rename("users_num2.txt", "users_num.txt");
        return users_num;
    }

    void AddToDatabse(const UserDetails &user_details) const {
        fstream ReadFile;
        ReadFile.open("users.csv", fstream::app);

        ReadFile << user_details.uid << '\t' << user_details.name << '\t' << user_details.email << '\t' << user_details.username << '\t'
        << user_details.password << '\t' << user_details.anonymous << "\n";
        ReadFile.close();
    }

public:
    User() {
        int choice = 0;
        while(choice != -1) {
            if(IsLoggedIn())
                return;

            cout << "Menu:\n";
            cout << "\t1: Login\n";
            cout << "\t2: Sign Up\n";
            cout << "Enter number in range 1 - 2: ";
            cin >> choice;
            if(choice == 1)
                Login();
            else if(choice == 2)
                Register();
            else if(choice != -1) {
                cout << "\n!!ERROR!! Please enter a valid choice.\n";
                cout << "Enter number in range 1 - 2: ";
            } 
        }
    }

    void Login() {
        string is_username;
        string is_password;

        cout << "\nEnter Username & Password: ";
        cin >> is_username >> is_password;

        if(VerifyLogin(is_username, is_password))
            cout << "Credentials have been verified; you are logged in.\n";
        else
            cout << "Invalid username or password.\n";
    }

    void Register() {
        // There's no input validation here.
        UserDetails user_details;
        cout << "\nEnter Username: ";
        cin >> user_details.username;
        cout << "\nEnter Password: ";
        cin >> user_details.password;
        cout << "\nEnter Email: ";
        cin >> user_details.email;
        cout << "\nEnter Name: ";
        cin >> user_details.name;
        cout << "\nAllow anonymous questions?:(0:NO 1:YES) ";
        cin >> user_details.anonymous;

        int user_id_ = user_details.uid = IncrementUsers() - 1;
        int anon_q_ = user_details.anonymous;

        UserSetter(user_id_, anon_q_);
        AddToDatabse(user_details);
    }

    void PrintQuestions(const bool &get_from_me, const bool &get_feed = false) {
        questionsObj.PrintQuestions(get_from_me, get_feed);
    }

    void AskQuestion() {
        questionsObj.AskQuestion();
    }

    void AnswerQuestion() {
        questionsObj.AnswerQuestion();
    }

    void DeleteQuestion() {
        questionsObj.DeleteQuestion();
    }

    void ListSystemUsers() const {
        fstream ReadThis;
        ReadThis.open("users.csv", fstream::in);
        
        string record;
        // first row in the csv.
        getline(ReadThis, record);
        while(getline(ReadThis, record)) {
            UserDetails user(record);
            
            cout << "ID: " << user.uid << "\tName: " << user.name << '\n';
        }
        ReadThis.close();
    }

    bool IsLoggedIn() const {
        return user_id != DUMMY_VALUE;
    }
};


int main() {
    // Delcaration user = aka starting the login/register sequence.
    User usr;

    int choice = 0;
    while(usr.IsLoggedIn()) {
        
        cout << "_____________________________\n";
        cout << "|Menu:\n";
        cout << "|\t1: Print questions to me\n";
        cout << "|\t2: Print questions from me\n";
        cout << "|\t3: Answer question\n";
        cout << "|\t4: Delete question\n";
        cout << "|\t5: Ask question\n";
        cout << "|\t6: List system users\n";
        cout << "|\t7: Feed\n";
        cout << "|\t8: Logout\n";
        cout << "| Enter number in range 1-8: ";
        
        cin >> choice;
        cout << "|_____________________________\n";

        if(choice == 1) { // PrintQuestinsToMe
            usr.PrintQuestions(0, 0);
        }
        else if(choice == 2) { // PrintQuestinsFromMe
            usr.PrintQuestions(1, 0);
        }
        else if(choice == 3) {
            usr.AnswerQuestion();
        }
        else if(choice == 4) {
            usr.DeleteQuestion();
        }
        else if(choice == 5) {
            usr.AskQuestion();
        }
        else if(choice == 6) {
            usr.ListSystemUsers();
        }
        else if(choice == 7) { // PrintFeed
            usr.PrintQuestions(0, 1);
        }
        else if(choice == 8)
            break;
    }
    cout << "\n\n Bye <3 \n\n";
    return 0;
}
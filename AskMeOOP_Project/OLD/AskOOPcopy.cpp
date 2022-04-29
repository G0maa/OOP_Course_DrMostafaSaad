#include <bits/stdc++.h>
using namespace std;

struct UserDetails {
        string username = { "" };
        string password = { "" };
        string name = { "" };
        string email = { "" };
        bool anonymous = { };
        int uid = {-1 };

        UserDetails() { }
        UserDetails(string username, string password, string name, string email, bool anonymous, int uid) :
        username(username), password(password), name(name), email(email), anonymous(anonymous), uid(uid) { }
};

// QuestionID - AskerID - AskedID - Question - Answer - isAQ - Next Question
struct QuestionDetails {
    int question_id = { -1 };
    int asker_id = { -1 };
    int asked_id = { -1 };
    int next_question = { -1 }; // for threaded questions.
    bool is_aq = { };
    string question_data = { "" };
    string answer_data = { "" };
    QuestionDetails() { }

    // Ah... doesnt' look pretty.
    QuestionDetails(int question_id, int asker_id, int asked_id, string question_data, string answer_data, bool is_aq, int next_question) : 
                    question_id(question_id), asker_id(asker_id), asked_id(asked_id), 
                    question_data(question_data), answer_data(answer_data), is_aq(is_aq), next_question(next_question) { }

};

class Searcher {
public:
    Searcher() { }

    // There are ~4 functions hear, I'd suggest (again) getting rid of some repitive stuff
    // and maybe put more responsabilities here, like errors or wrong input etc... better than dealing with that in the
    // calling fucntion (class which calls SearchUser(), SearchQuestion(), etc..)
    UserDetails SearchUser(int &id) {
        UserDetails searched_user;
        fstream ReadThis;
        ReadThis.open("users.csv", fstream::in);
        
        string record, word;
        // first row in the csv.
        getline(ReadThis, record);
        while(getline(ReadThis, record)) {
            vector<string> db_userdetails;
            stringstream sep(record);
            while(getline(sep, word, '\t'))
                db_userdetails.push_back(word);
            
            if(id == stoi(db_userdetails[0])) {
                 // id,name,email,username,password,aq 
                searched_user.uid = stoi(db_userdetails[0]);
                searched_user.name = db_userdetails[1];
                // searched_user.email = db_userdetails[2];
                // searched_user.username = db_userdetails[3];
                // No privacy whatsoever.
                // searched_user.password = db_userdetails[4];
                searched_user.anonymous = stoi(db_userdetails[5]);
                ReadThis.close();
                return searched_user;
            }
        }
        ReadThis.close();
        return searched_user;
    }

    // One job: Search of the given question id. NO VALIDATION.
    // O(num_questions + num_answers)
    // I think you can move needed data (numbers) to memory and do some BinarySearch?
    void SearchQuestion(QuestionDetails &question) {
        fstream ReadThis; // #repeated2
        ReadThis.open("questions.txt", fstream::in);
        string record, word;
        // getting rid of first row
        getline(ReadThis, record);

        while(getline(ReadThis, record)) {
            vector<string> db_questiondetails;
            stringstream sep(record);
            while(getline(sep, word, '\t'))
                db_questiondetails.push_back(word);
            
            if(question.question_id == stoi(db_questiondetails[0])) {
                question.question_id = stoi(db_questiondetails[0]);
                question.asker_id = stoi(db_questiondetails[1]);
                question.asked_id = stoi(db_questiondetails[2]);
                question.question_data = db_questiondetails[3];
                question.answer_data = db_questiondetails[4];
                question.is_aq = db_questiondetails[5][0] - '0';
                question.next_question = stoi(db_questiondetails[6]);
                ReadThis.close();
                return;
            }
        }
        question.question_id = -1; // if not found
        ReadThis.close();
        return;
    }

    void GetQuestions(vector<QuestionDetails> &questions, int user_id, int col, bool get_threads = false) {
        fstream ReadThis; // #repeated2
        ReadThis.open("questions.txt", fstream::in);
        string record, word;
        // getting rid of first row
        getline(ReadThis, record);

        while(getline(ReadThis, record)) {
            vector<string> db_questiondetails;
            stringstream sep(record);
            while(getline(sep, word, '\t'))
                db_questiondetails.push_back(word);
            
            // This is a very bad design I admit. #Question 1
            if(get_threads && stoi(db_questiondetails[6]) != -1) { // -11 => get me everything, that is part of a thread
                if(user_id == stoi(db_questiondetails[col]) || user_id == -11) {
                    QuestionDetails newQuestion;
                    newQuestion.question_id = stoi(db_questiondetails[0]); // Questioon ID
                    newQuestion.asker_id = stoi(db_questiondetails[1]); // Asker ID
                    newQuestion.asked_id = stoi(db_questiondetails[2]); // Asked ID
                    newQuestion.question_data = db_questiondetails[3]; // Question
                    newQuestion.answer_data = db_questiondetails[4]; // Answer
                    newQuestion.is_aq = db_questiondetails[5][0] - '0'; // AQ
                    newQuestion.next_question = stoi(db_questiondetails[6]); // Next Question
                    questions.push_back(newQuestion);
                }
            }
            else if(!get_threads && stoi(db_questiondetails[6]) == -1) {
                if(user_id == stoi(db_questiondetails[col]) || user_id == -10)  { // -10 => get me everything that is not part of a thread
                    QuestionDetails newQuestion;
                    newQuestion.question_id = stoi(db_questiondetails[0]); // Questioon ID
                    newQuestion.asker_id = stoi(db_questiondetails[1]); // Asker ID
                    newQuestion.asked_id = stoi(db_questiondetails[2]); // Asked ID
                    newQuestion.question_data = db_questiondetails[3]; // Question
                    newQuestion.answer_data = db_questiondetails[4]; // Answer
                    newQuestion.is_aq = db_questiondetails[5][0] - '0'; // AQ
                    newQuestion.next_question = stoi(db_questiondetails[6]); // Next Question
                    questions.push_back(newQuestion);
                }
            }
        }
        ReadThis.close();
        return;
    }

    // Get me all threads of said user, sort them using the already existing function,
    // Search for the question given in the sorted threads, push_back everything before it until you reach
    // a question.next_question == -10.
    // This function only works when giving it Thread ID

    // What I am going to do:
    // Add feature to this function to allow, getting thread from any question in that thread
    // therefore => No Thread ID anymore, can ask using any Question ID, and can delete using any Question ID in thread,
    // also QuestionsFormMe will not have to care about putting Thread ID, then
    // tell them to see feed if you want to read all remaining questioons in thread.
    // Effected Functions: QuestionsFromMe, DeleteQuestion, and AskQuestion:
    // DeleteQuestion total O(2nlogn) #1
    // QuestionsFromMe (No change in complexity, just print questions and tell them it's part of thread) #2
    // AskQuestion O(2nlogn + n) #3
    void SearchThread(vector<QuestionDetails> &thread, QuestionDetails &question) {
        vector<QuestionDetails> all_user_threads;
        GetQuestions(all_user_threads, question.asked_id, 2, true);
        SortThreads(all_user_threads);

        // Here, if given question isn't end of thread => search for end of thread using some function,
        // it's goign to be O(nlogn), because you already have your threads sorted.

        int end_index = SearchThreadsVector(all_user_threads, question.question_id); // no error handling whatsoever
        thread.push_back(all_user_threads[end_index]);
        end_index--;
        while(end_index >= 0 && all_user_threads[end_index].next_question != -10) {
            thread.push_back(all_user_threads[end_index]);
            end_index--;
        }
    }

    int SearchThreadsVector(const vector<QuestionDetails> &threads, const int &target) {
        int start = 0, end = threads.size() - 1, mid = -1; // @OmarNobel
        cout << ">>>" << end << "<<<";
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

    // Complexity of this one is: O(n/2 * log(n)) where n is threads.size(), 
    // divided by two bucause it is certain that a thread at least has 2 questions. => O(n log n) ?
    void SortThreads(vector<QuestionDetails> &threads) { 
        // This again should be extended to allow/give the ability to getThreads for given user id.
        // sort those threads... Pure problem sovling :D I am finally using binary search.
        vector<QuestionDetails> sorted_threads;
        int num_threads = threads.size();

        bool visited_questions[num_threads] = {0}; // too many. num_threads / 2
        // cout << num_threads << '\n';
        for(int idx = 0; idx < num_threads; idx++) {
            if(!visited_questions[idx]) {

                sorted_threads.push_back(threads[idx]);
                visited_questions[idx] = 1;

                int next_idx = SearchThreadsVector(threads, threads[idx].next_question);
                while(threads[next_idx].next_question != -10) {
                    // >>> infinite loop here. <<<
                    visited_questions[next_idx] = 1;
                    sorted_threads.push_back(threads[next_idx]);
                    next_idx = SearchThreadsVector(threads, threads[next_idx].next_question);
                }
                // reviison this spaghitti
                visited_questions[next_idx] = 1;
                sorted_threads.push_back(threads[next_idx]);
            }
        }
        threads = sorted_threads; // <<<<<< swap and delete old one?
    }
};


class Questions {
private:
    Searcher searcherObj;
    int user_id = { };    
    bool anon_q { };

    void AddQuestion(QuestionDetails &newQuestion) {
        fstream ReadThis;
        ReadThis.open("questions.txt", fstream::app); // #repeated2
        // From name to name question
        int qid = IncrementQuestions() - 1;
        newQuestion.question_id = qid;
        // QuestionID - AskerID - AskedID - QuestionData - AnswerData (in separate file)
        // No getters... AND REVERSE OREDER IN HRERE #here
        // isAQ Feature edit 1
        ReadThis << newQuestion.question_id << '\t' << newQuestion.asker_id << '\t' 
                 << newQuestion.asked_id << '\t' << newQuestion.question_data << '\t' << newQuestion.answer_data<< '\t'
                 << newQuestion.is_aq << '\t' << newQuestion.next_question << '\n';

        ReadThis.close();
    }

    int IncrementQuestions() {
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

    void DeleteFoundQuestion(QuestionDetails &question) {
        fstream WriteThis;
        WriteThis.open("questions2.txt", fstream::out);

        fstream ReadThis; // #repeated2
        ReadThis.open("questions.txt", fstream::in);
        string record, word;
        // adding the first row .-.
        getline(ReadThis, record);
        WriteThis << record << '\n';
        while(getline(ReadThis, record)) {
            vector<string> db_questiondetails;
            stringstream sep(record);
            while(getline(sep, word, '\t'))
                db_questiondetails.push_back(word);
            
            if(question.question_id != stoi(db_questiondetails[0]))
                WriteThis << record << '\n';
        }

        ReadThis.close();
        WriteThis.close();
        remove("questions.txt");
        rename("questions2.txt", "questions.txt");
        // DeleteFoundAnswer(question); Deprecated
        return;
    }

    // This could be more easily done if we set differend IDs for each thread.
    void DeleteFoundThread(QuestionDetails question) {
        vector<QuestionDetails> thread;
        searcherObj.SearchThread(thread, question);
        int thread_len = thread.size();

        // a bit slow, although *kinda* sorted (reversed), would need a better DeleteFoundQuestion(), 
        // or new function.
        for(int idx = 0; idx < thread_len; idx++) 
            DeleteFoundQuestion(thread[idx]);
    }

    QuestionDetails ThreadHandler(const int &asked_uid) {
        QuestionDetails thread;
        cout << "Enter Thread ID: ";
        cin >> thread.question_id;

        searcherObj.SearchQuestion(thread);
        if(thread.question_id == -1)
            cout << "!!ERROR!! Thread ID does not exist.\n";
        else if(thread.asked_id != thread.asked_id) {
            cout << "!!ERROR!! Thread does not belong to the same asked user!\n";    
            thread.question_id = -1;
        }
        else if(thread.next_question != -1 && thread.next_question != -10) { // many magical numbers <<
            cout << "!!ERROR!! Wrong Thread ID.\n";
            thread.question_id = -1;
        }
        return thread;
    }

    void AddQuestionInOrder(const QuestionDetails &thread) {
        fstream WriteThis, ReadThis;  // #repeated2
        WriteThis.open("questions2.txt", fstream::out);
        ReadThis.open("questions.txt", fstream::in);
        string record, word;
       
        // adding the first row .-.
        getline(ReadThis, record);
        WriteThis << record << '\n';

        while(getline(ReadThis, record)) {
            vector<string> db_questiondetails; // I think those 4 lines can be moved to separate function.
            stringstream sep(record);
            while(getline(sep, word, '\t'))
                db_questiondetails.push_back(word);
            // YOU FORGOT TO PRINT thread.NextQusetions IN ALL FUNCTIONS.
            if(thread.question_id == stoi(db_questiondetails[0])) // I do not like this.
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
    
    void CoutQuestions(vector<QuestionDetails> &questions) {
        int len = (int) questions.size();
        for(int idx = 0; idx < len; idx++) {
            cout << "Quesiton ID (" << questions[idx].question_id;
            if(!anon_q) // anon_q == 1 => accepts anonymous questions.. This one kinda useless, because if user is !anon_q the question will be anonymous in AskQuestion() anyway.
                cout << ") From User ID (" << questions[idx].asker_id << ")\n";
            else if(questions[idx].is_aq) // this one has two options, either it is anonymous or not. #revise1
                cout << " From User ID (???" << ")\n";
            else
                cout << " From User ID (" << questions[idx].asker_id << ")\n";

            cout << "\tQuestion: " << questions[idx].question_data << '\n';
            cout << "\t\tAnswer: " << questions[idx].answer_data << '\n';
        }
    }

    void CoutThreads(vector<QuestionDetails> &threads) {
        int len = (int) threads.size();
        for(int idx = 0; idx < len; idx++) {
            if(idx == 0 || threads[idx - 1].next_question == -10)
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

            if(threads[idx].next_question == -10)
                cout << "Thread ID (" << threads[idx].question_id << ").\n";
        }
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
            searcherObj.GetQuestions(questions, -10, 2); // magical numbers, -10 get all questions,
            searcherObj.GetQuestions(threads, -11, 2, true); // -11 get all threads.
        }
        else if(get_from_me) {
            searcherObj.GetQuestions(questions, user_id, 1); // another magical number, this is number of column
            // cout << questions.size() << '\n';
            searcherObj.GetQuestions(threads, user_id, 1, true); //  the function matches with. See QuestionDetails.
            // cout << threads.size() << '\n';
        }
        else {
            searcherObj.GetQuestions(questions, user_id, 2);
            searcherObj.GetQuestions(threads, user_id, 2, true);

        }

        // Questions from me can be part of different threads, so sorting them will lead to errors.
        if(!get_from_me) 
            searcherObj.SortThreads(threads);

        CoutQuestions(questions);
        CoutThreads(threads);
    }


    void AskQuestion() { // maybe bool & return true and false.
        QuestionDetails newQuestion;
        int asked_uid = -1;
        cout << "Enter User id or -1 to cancel: ";
        cin >> asked_uid;
        if(asked_uid == -1)
            return;
        
        UserDetails asked_userdetails = searcherObj.SearchUser(asked_uid);
        if(asked_userdetails.uid == -1) {
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
            if(thread.question_id == -1) // bad
                return;
        }

        string question;
        cout << "Enter your question: \n";
        getline(cin >> ws, question);

        newQuestion.asker_id = user_id; // no getter
        newQuestion.asked_id = asked_uid;
        newQuestion.question_data = question;
        newQuestion.is_aq = isAQ;
        if(is_thread)
            newQuestion.next_question = -10; // marks the end of a thread with -10 for now.
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
        if(SearchedQusetion.question_id == -1 || SearchedQusetion.asked_id != user_id) { // no getters again. return??
            cout << "Question does not exist, or wrong ID.\n";
            return;
        }

        // If overwritten -> Delete then insert
        // Complexity wise this adds more n iterations. which can be dealt with #here2
        if(SearchedQusetion.answer_data != "") {
            int choice = 0;
            cout << "Warning: There's an answer already for said question, it will be overwrited. -1 to return to main menu:";
            cin >> choice;
            if(choice == -1)
                return;
        }
        
        string answer;
        cout << "Enter you answer: ";
        getline(cin >> ws, answer);
        SearchedQusetion.answer_data = answer;
        // Because we need our answers to be sorted to allow 'faster' location of answers of a group of questions
        // O(n^2) vs O(n), a separate funciton was created to update the answer in its correct place.
        // as if we append directly we can't be certain that it will result in a sorted file (qid).
        UpdateAnswer(SearchedQusetion);
    }

    void UpdateAnswer(const QuestionDetails &question) { // const
        int cur_id = question.question_id;
        int last_id = 0;
        int after_id = 0;
        bool inserted = false;
        fstream WriteThis, ReadThis;  // #repeated2
        WriteThis.open("questions2.txt", fstream::out);
        ReadThis.open("questions.txt", fstream::in);
        string record, word;
       
        // adding the first row .-.
        getline(ReadThis, record);
        WriteThis << record << '\n';

        while(getline(ReadThis, record)) {
            vector<string> db_questiondetails; // I think those 4 lines can be moved to separate function.
            stringstream sep(record);
            while(getline(sep, word, '\t'))
                db_questiondetails.push_back(word);
            
            after_id = stoi(db_questiondetails[0]);
            if(question.question_id == after_id) { // I do not like this.
                cout << "Warning: Answer has been overwritten.\n"; // <<< #here2
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
    // I was confused on whcich questions to delete, questios that myself asked,
    // or questions that are sent to me... went with the latter as it was the one demonstrated in the video.

    void DeleteQuestion() {
        QuestionDetails question;
        cout << "Enter Questiond ID or -1 to cancel: ";
        cin >> question.question_id;
        cout << '\n';
        searcherObj.SearchQuestion(question);
        if(question.question_id == -1 || question.asked_id != user_id) { // no getter.
            cout << "!!ERROR!! Question not found or wrong ID.\n";
            return;
        }

        if(question.next_question == -1)
            DeleteFoundQuestion(question);
        else {
            bool del = false;
            if(question.next_question == -10) {
                cout << "You have entered a Thread ID, are you sure you want to delete this thread? (0:NO 1:YES): ";
                cin >> del;
                cout << '\n';
                if(del)
                    DeleteFoundThread(question);
            }
            else
                cout << "!!ERROR!! The entered QuestionID is part of thread, but not thread ID.\n";
        }
        
    }
};


class User {
private:
    int user_id = {-1};
    bool anon_q = { };
    Questions questionsObj;

    User(User &another) {
        cout << "\n WARNING: THERE HAPPEND A COPY FOR CLASS: 'USER'\n";
    }

    void UserSetter(const int &user_id_, const int &anon_q_) {
        user_id = user_id_;
        anon_q = anon_q_;
        questionsObj.setQuestions(user_id, anon_q); // first use of setter... a public setter *sweats*
    }

    // This function is supposed to do the verificaiton but it also calls Setter.
    bool VerifyLogin(string is_username, string is_password) {
        fstream ReadThis; // #repeated2
        ReadThis.open("users.csv", fstream::in);
        string record, word;

        while(getline(ReadThis, record)) {
            vector<string> db_userdetails;
            stringstream sep(record);
            while(getline(sep, word, '\t'))
                db_userdetails.push_back(word);
            
            if(is_username == db_userdetails[3] && is_password == db_userdetails[4]) {
                const int user_id_ = stoi(db_userdetails[0]);
                const int anon_q_ = db_userdetails[5][0] - '0';
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
        fstream Reader; // #repeated2
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

    void AddToDatabse(UserDetails user_details) const {
        fstream ReadFile;
        ReadFile.open("users.csv", fstream::app); // #repeated2
        // ID - NAME - EMAIL - USERNAME - PASSWORD - ANONYMOUS
        ReadFile << user_details.uid << '\t' << user_details.name << '\t' << user_details.email << '\t' << user_details.username << '\t'
        << user_details.password << '\t' << user_details.anonymous << "\n";
        ReadFile.close();
    }

public:
    // I think this constructor should not exist in real-world scinario,
    // Imagine if this is a website, once you open it, you will be asked to login/register, if not
    // the site will clsoe itself, but if there exists no constructor, you can surf what's allowed of the site,
    // until you press some button or do some action that needs you to be logged in.
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
        const int user_id_ = user_details.uid = IncrementUsers() - 1;
        const int anon_q_ = user_details.anonymous;
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

    void ListSystemUsers() {
        // This was repeated a lot... parsing stuff and getting info from some file. #repeated2
        fstream ReadThis;
        ReadThis.open("users.csv", fstream::in);
        
        string record, word;
        // first row in the csv.
        getline(ReadThis, record);
        while(getline(ReadThis, record)) {
            vector<string> db_userdetails;
            stringstream sep(record);
            while(getline(sep, word, '\t'))
                db_userdetails.push_back(word);
            
            cout << "ID: " << db_userdetails[0] << "    Name: " << db_userdetails[1] << '\n';
        }
        ReadThis.close();
    }

    bool IsLoggedIn() {
        return user_id != -1;
    }
};

// #main
int main() {
    // Initializing user, aka starting the login/register sequence.
    User usr;

    // There should be some kind of way to know if function returned was executed successfully or not,
    // and cout something based on that.
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
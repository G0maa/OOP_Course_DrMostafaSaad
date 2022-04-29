#include <bits/stdc++.h>
using namespace std;

// I need some input validation and after function execution reply.



// I thougt of making this one using singelton pattern,
// but I prefered not to becuase: Too much code that it defies the point. 
// This way I get
// - Because I can create many objects of Printer while I only need one.
// + I won't need to make a new pointer each time I need Printer Object
// + the Class::Staticmember looks ugly.
// I don't think this is the correct answer either though.

// There was a class Printer here to simplifiy cout-ing, but it proved to be useless. rip.

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

// QuestionID - AskerID - AskedID - QuestionData  - (answer in separate file tho) - isAnonymousQ
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
    // NextQuestion doesn't exist in the constructor
    QuestionDetails(int question_id, int asker_id, int asked_id, string question_data, string answer_data, bool is_aq) : 
                    question_id(question_id), asker_id(asker_id), asked_id(asked_id), 
                    question_data(question_data), answer_data(answer_data), is_aq(is_aq) { }

};

class Searcher {
public:
    Searcher() { }

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
                question.asker_id = stoi(db_questiondetails[1]);
                question.asked_id = stoi(db_questiondetails[2]);
                question.question_data = (db_questiondetails[3]);
                question.is_aq = db_questiondetails[4][0] - '0';
                question.next_question = stoi(db_questiondetails[5]);
                ReadThis.close();
                SearchAnswer(question);
                return;
            }
        }
        question.question_id = -1; // if not found
        ReadThis.close();
        return;
    }

    // One job: Search of the given answer id. NO VALIDATION.
    void SearchAnswer(QuestionDetails &question) {
        fstream ReadThis; // #repeated2
        ReadThis.open("answers.txt", fstream::in);
        string record, word;
        // Getting rid of first row.
        getline(ReadThis, record);

        while(getline(ReadThis, record)) {
            vector<string> db_questiondetails;
            stringstream sep(record);
            while(getline(sep, word, '\t'))
                db_questiondetails.push_back(word);
            
            if(question.question_id == stoi(db_questiondetails[0])) {
                question.answer_data = (db_questiondetails[3]);
                ReadThis.close();
                return;
            }
        }
        ReadThis.close();
        return;
    }

    void GetQuestions(vector<QuestionDetails> &questions, int user_id, int col) {
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
            if(user_id == stoi(db_questiondetails[col]) || (user_id == -10 && stoi(db_questiondetails[5]) == -1)) { // -10 => get me everything
                QuestionDetails newQuestion;
                newQuestion.question_id = stoi(db_questiondetails[0]);
                newQuestion.asker_id = stoi(db_questiondetails[1]);
                newQuestion.asked_id = stoi(db_questiondetails[2]);
                newQuestion.question_data = db_questiondetails[3];
                newQuestion.is_aq = db_questiondetails[4][0] - '0';
                newQuestion.next_question = stoi(db_questiondetails[5]);
                questions.push_back(newQuestion);
            }
            else if(user_id == -11 && stoi(db_questiondetails[5]) != -1) { // -11 to mark get me all questions, that do belong to thread.
                QuestionDetails newQuestion;                // SHOULD MAKE SEPARATE ONE TO GET THREADS FOR GIVEN USER ID.
                newQuestion.question_id = stoi(db_questiondetails[0]);
                newQuestion.asker_id = stoi(db_questiondetails[1]);
                newQuestion.asked_id = stoi(db_questiondetails[2]);
                newQuestion.question_data = db_questiondetails[3];
                newQuestion.is_aq = db_questiondetails[4][0] - '0';
                newQuestion.next_question = stoi(db_questiondetails[5]); // >>>There's a problem with '/t' not showing in questions.txt I think.
                questions.push_back(newQuestion);
            }
        }
        GetAnsweres(questions, user_id, col);
        ReadThis.close();
        return;
    }

    // Mergeing questions.txt and questions.txt could get rid of this function.
    void GetAnsweres(vector<QuestionDetails> &questions, int id, int col) { // kidn of useless id.
        fstream ReadThis; // #repeated2
        ReadThis.open("answers.txt", fstream::in);
        string record, word;
        // getting rid of first row
        getline(ReadThis, record);
        int idx = 0; // <<<
        while(getline(ReadThis, record)) {
            vector<string> db_questiondetails;
            stringstream sep(record);
            while(getline(sep, word, '\t'))
                db_questiondetails.push_back(word);
            
            if(idx >= (int) questions.size())
                break;

            // This is a bad design I admit.
            // PROBLEM:
            // Answeres are NOT sorted, therefore searching for them would take n^2 time.
            // Solution:
            //  - Do internal sort? When?
            //  - Just go with the n^2 solution? #ReturnHere
            if(col == 1) {
                if(questions[idx].asker_id == stoi(db_questiondetails[1])) { // or id == ...
                    questions[idx].answer_data = db_questiondetails[3];
                    idx++;
                }
            }
            else {
                if(questions[idx].asked_id == stoi(db_questiondetails[2])) { // or id == ...
                    questions[idx].answer_data = db_questiondetails[3];
                    idx++;
                }
            }
        }
        
        ReadThis.close();
        return;
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
                 << newQuestion.asked_id << '\t' << newQuestion.question_data << '\t'
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
        DeleteFoundAnswer(question);
        return;
    }

    void DeleteFoundAnswer(QuestionDetails &question) {
        fstream WriteThis;
        WriteThis.open("answers2.txt", fstream::out);

        fstream ReadThis; // #repeated2
        ReadThis.open("answers.txt", fstream::in);
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
        remove("answers.txt");
        rename("answers2.txt", "answers.txt");
        return;
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
                          << '\t' << thread.question_data<< '\t' << thread.is_aq << '\t' << thread.next_question << '\n';
            else
                WriteThis << record << '\n';

        }
        ReadThis.close();
        WriteThis.close();
        remove("questions.txt");
        rename("questions2.txt", "questions.txt");
        return;
    }

public:
    Questions() { }

    void setQuestions(int &userID, bool &anon_q_) {
        user_id = userID;
        anon_q = anon_q_;
    }

    void PrintQuestionsToMe() {
        vector<QuestionDetails> questions;
        searcherObj.GetQuestions(questions, user_id, 2);
        // Searcher::GetQuestionsToMe(questions)? and same with answers?
        // Considering PrintQuestionsFromMe(), it will have many similarities,
        // So I'd say Searcher::GetQuestions(int id, int col_num), after this one finishes
        // calls Searcher::GetAnswers(int id, int col_num).
        // So instead of 4 functions it's 2 functions but TIGHLTLY COUPLED.
        int num_questions = questions.size(); // Repeated3
        for(int i = 0; i < num_questions; i++) {
            cout << "Quesiton ID: " << questions[i].question_id;
            // You need to be able to choose to ask anonymous questions, as well as the user sets if he accepts anonymous questions or not.
            if(!anon_q) // anon_q == 1 => accepts anonymous questions.. This one kinda useless, because if user is !anon_q the question will be anonymous in AskQuestion() anyway.
                cout << " From user id: " << questions[i].asker_id << '\n';
            else if(questions[i].is_aq) // this one has two options, either it is anonymous or not. #revise1
                cout << " From user id: ???" << '\n';
            else
                cout << " From user id: " << questions[i].asker_id << '\n';

            cout << "   Question: " << questions[i].question_data << '\n';
            if(questions[i].answer_data == "")
                cout << "   Answer: NO ANSWER YET.\n";
            else
                cout << "   Answer: " << questions[i].answer_data << '\n';
        }
    }

    void PrintQuestionsFromMe() {
        vector<QuestionDetails> questions;
        searcherObj.GetQuestions(questions, user_id, 1);
        int num_questions = questions.size(); // Repeated3
        for(int i = 0; i < num_questions; i++) {
            cout << "Quesiton ID: " << questions[i].question_id << " To user id: " << questions[i].asker_id << '\n';
            cout << "   Question: " << questions[i].question_data << '\n';
            if(questions[i].answer_data == "")
                cout << "\tAnswer: NO ANSWER YET.\n";
            else
                cout << "\tAnswer: " << questions[i].answer_data << '\n';
        }
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

    // I could merge questions.txt and answers.txt together.
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
        searcherObj.SearchAnswer(SearchedQusetion);
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
        WriteThis.open("answers2.txt", fstream::out);
        ReadThis.open("answers.txt", fstream::in);
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
                WriteThis << question.question_id << '\t' << question.asker_id << '\t' << question.asked_id << '\t' << question.answer_data << '\n';
                inserted = true;
            }
            else if(question.question_id > last_id && question.question_id <= after_id) { // = for cases. 0 0 0
                WriteThis << question.question_id << '\t' << question.asker_id << '\t' << question.asked_id << '\t' << question.answer_data << '\n';
                WriteThis << record << '\n';
                inserted = true;
            }
            else
                WriteThis << record << '\n';

            last_id = after_id;
        }
        
        if(!inserted)
            WriteThis << question.question_id << '\t' << question.asker_id << '\t' << question.asked_id << '\t' << question.answer_data << '\n';
        ReadThis.close();
        WriteThis.close();
        remove("answers.txt");
        rename("answers2.txt", "answers.txt");
        return;
    }
    // I was confused on whcich questions to delete, questios that myself asked,
    // or questions that are sent to me... went with the latter as it was the one demonstrated in the video.
    void DeleteQuesiton() {
        QuestionDetails question;
        cout << "Enter Questiond ID or -1 to cancel: ";
        cin >> question.question_id;
        cout << '\n';
        searcherObj.SearchQuestion(question);
        if(question.question_id == -1 || question.asked_id != user_id) { // no getter.
            cout << "Question not found or wrong ID.\n";
            return;
        }
        // could be a separate private function.
        DeleteFoundQuestion(question);
    }

    void ListFeed(vector<QuestionDetails> &feed) {
        // Magic numbers, -10 (get all questions), 2 matching with column two, the asked user.
        searcherObj.GetQuestions(feed, -10, 2);
    }

    // should be privatized.
    int SearchThreadsVector(const vector<QuestionDetails> &threads, const int &target) {
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

    // Complexity of this one is: O(n/2 * log(n)) where n is threads.size(), divided by two bucause it is certain that a thread at least has 2 questions. => O(n^1.5) ?
    void ListThreads(vector<QuestionDetails> &threads) { // This again should be extended to allow/give the ability to getThreads for given user id.
        searcherObj.GetQuestions(threads, -11, 2);

        // sort those threads... Pure problem sovling :D I am finally using binary search.
        vector<QuestionDetails> sorted_threads;
        int num_threads = threads.size();

        bool visited_questions[num_threads] = {0}; // too many. num_threads / 2

        for(int idx = 0; idx < num_threads; idx++) {
            if(!visited_questions[idx]) {
                sorted_threads.push_back(threads[idx]);
                visited_questions[idx] = 1;
                int next_idx = SearchThreadsVector(threads, threads[idx].next_question);
                while(threads[next_idx].next_question != -10) {
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

    void ListThreads() {
        vector<QuestionDetails> threads;
        questionsObj.ListThreads(threads);

        int threads_len = threads.size();

        for(int idx = 0; idx < threads_len; idx++) {
            if(idx == 0 || threads[idx - 1].next_question == -10)
                cout << "Thread Parent: ";
            else
                cout << "Thread Question: ";

            cout << "Question ID (" << threads[idx].question_id << ") from user ID ("; // repeated.
            if(threads[idx].is_aq)
                cout << "???";
            else
                cout << threads[idx].asker_id;

            cout << ") To user ID (" << threads[idx].asked_id << ")\n \t Question: " << threads[idx].question_data 
            << "\n \t Answer: " << threads[idx].answer_data << '\n';

            if(threads[idx].next_question == -10)
                cout << "Thread ID (" << threads[idx].question_id << ").\n";
        }
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

    void PrintQuestionsToMe() {
        questionsObj.PrintQuestionsToMe();
    }

    void PrintQuestionsFromMe() {
        questionsObj.PrintQuestionsFromMe();
    }
    // Threads to be implemented at a latter time.
    void AskQuestion() {
        questionsObj.AskQuestion();
    }

    void AnswerQuestion() {
        questionsObj.AnswerQuestion();
    }

    void DeleteQuestion() {
        questionsObj.DeleteQuesiton();
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

    void ListFeed() {
        vector<QuestionDetails> feed;
        questionsObj.ListFeed(feed);

        int feed_len = feed.size();
        for(int i = 0; i < feed_len; i++) {
            cout << "Question ID (" << feed[i].question_id << ") from user ID (";
            if(feed[i].is_aq)
                cout << "???";
            else
                cout << feed[i].asker_id;

            cout << ") To user ID (" << feed[i].asked_id << ")\n \t Question: " << feed[i].question_data 
            << "\n \t Answer: " << feed[i].answer_data << '\n';
        }
        ListThreads();
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

        cout << "Menu:\n";
        cout << "\t1: Print questions to me\n";
        cout << "\t2: Print questions from me\n";
        cout << "\t3: Answer question\n";
        cout << "\t4: Delete question\n";
        cout << "\t5: Ask question\n";
        cout << "\t6: List system users\n";
        cout << "\t7: Feed\n";
        cout << "\t8: Logout\n";
        cout << "Enter number in range 1-8: ";
        cin >> choice;

        if(choice == 1) {
            usr.PrintQuestionsToMe();
        }
        else if(choice == 2) {
            usr.PrintQuestionsFromMe();
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
        else if(choice == 7) {
            usr.ListFeed();
        }
        else if(choice == 8)
            break;
    }
    cout << "\n\n Bye <3 \n\n";
    return 0;
}
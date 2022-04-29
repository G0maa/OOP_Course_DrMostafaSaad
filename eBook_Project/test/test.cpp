#include <bits/stdc++.h>
// #include "HelperFunctions.h"
using namespace std;

void ReadFile(vector<string> &InLines, const string &path) {
    fstream ReadFile;
    ReadFile.open(path, fstream::in);

    if(ReadFile.fail()) {
        cout << "\nReading file in ReadFile() function FAILED.";
        return;
    }

    string record;
    while(getline(ReadFile, record))
        InLines.push_back(record);
    ReadFile.close();
    return;
}

void SplitString(vector<string> &InLine, const string &str, const char &delimiter = '\t') {
	vector<int> delimiter_indexes;
    delimiter_indexes.push_back(-1); // Special case for first word.
    

    for(int i = 0; i < (int) str.size(); i++)
        if(str[i] == delimiter)
            delimiter_indexes.push_back(i);

    delimiter_indexes.push_back(str.size()); // Special case for last word... buggy -1.

    int start = 0, end = 0, sz = 0;
    for(int i = 1; i < (int) delimiter_indexes.size(); i++) {
        start = delimiter_indexes[i - 1] + 1;
        end = delimiter_indexes[i];
        sz = end - start;
        string sstr = str.substr(start, sz);
        InLine.push_back(sstr);
    }
}

// Slightly in efficient, could have splitted string while reading file,
// but I didn't want to DRY.
void ReadFileSplit(vector<vector<string>> &OutLines, const string &path) {
    vector<string> in_lines;
    ReadFile(in_lines, path);

    // Hmm...
    OutLines.resize(in_lines.size());

    for(int idx = 0; idx < (int) in_lines.size(); idx++)
        SplitString(OutLines[idx], in_lines[idx]);
}


// Note: It loads all sessions, even if it's not of that particular user.
// void SessionManager::LoadSessions() {
//     vector<string> lines;
//     ReadFile(lines, "Sessions.txt");
//     for(int idx = 0; idx < (int) lines.size(); idx++) {

//         // Sessions.txt => user_id - cur_page | name - author - page_count | year - month - day
//         vector<string> splitted_string;
//         SplitString(splitted_string, lines[idx]);

//         vector<string> session_line;
//         session_line.push_back(splitted_string[0]);
//         session_line.push_back(splitted_string[1]);

//         vector<string> book_line;
//         book_line.push_back(splitted_string[2]);
//         book_line.push_back(splitted_string[3]);
//         book_line.push_back(splitted_string[4]);

//         vector<string> date_line;
//         date_line.push_back(splitted_string[5]);
//         date_line.push_back(splitted_string[6]);
//         date_line.push_back(splitted_string[7]);

//         sess_vec.push_back(Session(session_line, book_line, date_line));
//     }
// }

int main() {

    
    vector<vector<string>> temp;
    ReadFileSplit(temp, "CustomerUsers.txt");

    for(int idx = 0; idx < (int) temp.size(); idx++) {
        for(int idy = 0; idy < (int) temp[idx].size(); idy++) {
            cout << temp[idx][idy] << "$";
        }
        cout << '\n';
    }


    cout << "\nBye :)\n";
    return 0;
}


#include "HelperFunctions.h"
#include <bits/stdc++.h> 
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

// Can be improved with templates. Directly call Object.ToString() and append it to file.
void WriteFile(const vector<string> &OutLines, const string &path) {
    // auto status = ios::in | ios::out | ios::app;
    fstream ReadFile;
    ReadFile.open(path, fstream::out);

    if(ReadFile.fail()) {
        cout << "\nWriting file in WriteFile() function FAILED.";
        return;
    }

    for(int i = 0; i < (int) OutLines.size(); i++)
        ReadFile << OutLines[i] << '\n';

    ReadFile.close();
    return;
}

void AppendFile(const string &OutLine, const string &path) {
    // auto status = ios::in | ios::out | ios::app;
    fstream ReadFile;
    ReadFile.open(path, fstream::app);

    if(ReadFile.fail()) {
        cout << "\nWriting file in WriteFile() function FAILED.";
        return;
    }

    ReadFile << OutLine << '\n';
    ReadFile.close();
    return;
}

// First time using sentinel (insert datatype) ever!        Delimiter is a character!!
// Needs lots of input verification! Also kinda buggy!
void SplitString(vector<string> &InLine, const string &str, const char &delimiter) {
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

int StringToInt(const string &fake_int) {
    int num = 0;

    for(int i = 0; i < (int) fake_int.size(); i++)
        num = (num * 10) + (fake_int[i] - '0');

    return num;
}

// Doesn't deal with leading zeros.
string IntToString(int fake_string) {
    string true_string = "";

    if(fake_string == 0)
        true_string = "0";

    while(fake_string) {
        true_string = char((fake_string % 10) + '0') + true_string;
        fake_string /= 10;
    }
    return true_string;
}

// Common I/O Related functions:
void PrintMenu(const vector<string> &lines, const string& menu_name) {
    PrintLineHashed(menu_name);
    for(int i = 1 ; i <= (int) lines.size(); i++)
        cout << i << ": " << lines[i - 1] << '\n';
    // cout << "Choose an option: "; Deprecated for asethic reasons.
}

// New function, if proves to be useful will stay.
// Assumes linesA.size() == linesB.size()
void PrintPairs(const vector<string> &lines_a, const vector<string> &lines_b, const string& pairs_name) {
    PrintLineHashed(pairs_name);
    for(int idx = 0; idx < (int) lines_a.size(); idx++)
        cout << lines_a[idx] << " : " << lines_b[idx] << '\n';
}

void VerifyChoice(int &choice, const int &start, const int &end) {
    choice = -1; // If for whatever reason user fails to enter something.
    cin >> choice;
    while((choice < start || choice > end) && choice != -1) {
        cout << "Wrong choice! Try Again! Enter -1 To go back: ";
        cin >> choice;
    }
}


void PrintLineHashed(const string &line) {
    cout << "##### " << line << " #####\n";
}

// I wonder if this is useful?
void PrintLine(const string &line) {
    cout << line;
}
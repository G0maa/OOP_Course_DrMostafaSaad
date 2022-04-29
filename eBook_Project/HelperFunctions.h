#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

#include <bits/stdc++.h> 
using namespace std;

void ReadFile(vector<string> &InLines, const string &path);
void ReadFileSplit(vector<vector<string>> &OutLines, const string &path);
void WriteFile(const vector<string> &OutLines, const string &path);
void AppendFile(const string &OutLine, const string &path);
void SplitString(vector<string> &InLine, const string &str, const char &delimiter = '\t');
int StringToInt(const string &fake_int);
string IntToString(int fake_string);
void PrintLine(const string &line);
void PrintLineHashed(const string &line);
void VerifyChoice(int &choice,const int &start, const int &end);
void PrintMenu(const vector<string> &lines, const string& menu_name = "Menu Options:");
void PrintPairs(const vector<string> &lines_a, const vector<string> &lines_b, const string& pairs_name = "List");
#endif /* HELPERFUNCTIONS_H_ */
#include <bits/stdc++.h>
using namespace std;

class MyMap {
private:
    vector<string> vec_strs;
    vector<int> vec_ints;
    int iterator = 0;

public:
    MyMap() { }

    void Insert(const string &insert_string, const int &insert_int) {
        for(int idx = 0; idx < (int) vec_strs.size(); idx++) {
            if(vec_strs[idx] == insert_string) {
                vec_ints[idx] = insert_int;
                return;
            }
        }
        vec_strs.push_back(insert_string);
        vec_ints.push_back(insert_int);
    }

    int FindStr(const string &find_me) const {
        for(int idx = 0; idx < (int) vec_strs.size(); idx++)
            if(vec_strs[idx] == find_me)
                return vec_ints[idx];
        
        return 0;
    }

    int& FindStr(const string &find_me) {
        for(int idx = 0; idx < (int) vec_strs.size(); idx++)
            if(vec_strs[idx] == find_me)
                return vec_ints[idx];

        vec_strs.push_back(find_me);
        vec_ints.push_back(0);
        return vec_ints.back();
    }

    vector<string> FindNumber(const int &find_me) const {
        vector<string> ans;

        for(int idx = 0; idx < (int) vec_strs.size(); idx++)
            if(vec_ints[idx] == find_me)
                ans.push_back(vec_strs[idx]);
        
        // Is that what Dr meant by sort?
        sort(ans.begin(), ans.end());
        return ans;
    }

    int operator[] (const string &find_me) const {
        return FindStr(find_me);
    }


    int& operator[] (const string &insert_string) {
        return FindStr(insert_string);
    }

    vector<string> operator[] (const int &find_me) const {
        vector<string> ans = FindNumber(find_me);
        return ans;
    }

    bool HasNext() {
        return (iterator < (int) vec_ints.size());
    }

    pair<string, int> GetNext() {
        // Forgot to do the condition here... if(HasNex()) =>
        pair<string, int> ret = make_pair(vec_strs[iterator], vec_ints[iterator]);
        iterator++;
        return ret;
    }

    void ResetIterator() {
        iterator = 0;
    }

    void Clear() {
        iterator = 0;
        vec_ints.clear();
        vec_strs.clear();
    }
};


int main() {
    MyMap map;

    map["mostafa"] = 20;
    map["mostafa"] = 40;
    map["sayed"] = 20;
    map["ali"] = 20;

    cout << map["mostafa"] << '\n';

    vector<string> v = map[20];
    for(auto s : v)
        cout << s << '\n';

    map.ResetIterator();
    while(map.HasNext()) {
        auto p = map.GetNext();
        cout << p.first << " " << p.second << '\n';
    }
    map.Clear();
    cout << "\n\n Bye :) \n\n";
    return 0;
}
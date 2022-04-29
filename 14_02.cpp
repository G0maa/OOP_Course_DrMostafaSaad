#include <bits/stdc++.h>
using namespace std;

string operator*(const string &str, int mul) {
    // I wonder what's the complexity of this one? 
    // mhm.. 2 mintue googling told me that stringstream is slow, not 100% sure.
    ostringstream oss;
    while(mul--)
        oss << str;
    
    return oss.str();
}

int main() {
    string a = "bad";
    string b = "I am " + a * 3 + ", right?";

    cout << b;
    return 0;
}
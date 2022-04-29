#include <bits/stdc++.h>
using namespace std;

class test {
    string str = "DUMMY";
public:
    test() {

    }

    test(string str) : str(str) {}

    test(vector<string> vec) : test() {
        // string str2 = vec[0];
        test("dcba");
    }

    const string& GetStr() const {
        return str;
    }
};


int main() {

    test obj("abc");
    cout << obj.GetStr() << '\n';

    vector<string> vec = {"cba", "ddd"};

    test obj2(vec);
    cout << obj2.GetStr() << '\n';
    return 0;
}
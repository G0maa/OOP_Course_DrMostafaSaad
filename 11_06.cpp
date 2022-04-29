// I guess we will create new class (as shown) DecoratedString, and inherit from string?
#include <bits/stdc++.h>
using namespace std;

class DecoratedString : public string {
public:
    // warning told me something something use 'using' something something.
    string::string;

    // Didn't find a better way.
    void decorate() {
        this->push_back(']');
        this->push_back(']');
        this->push_back('>');
        this->push_back('>');
        reverse(this->begin(), this->end());
        this->push_back('[');
        this->push_back('[');
        this->push_back('<');
        this->push_back('<');
        reverse(this->begin(), this->end());
    }
};

int main() {
    DecoratedString str = "I am learning CS";
    str.decorate();

    cout << str;
}
// mhm... looks like I didn't quite understand the question I guess.
// https://github.com/mostafa-saad/ArabicCompetitiveProgramming/blob/master/19-object-oriented-programming/05_homework_01_answer.cpp
#include <bits/stdc++.h>
using namespace std;

class test {
private:
  int a;
  int b;
  int c;
public:
    test(int a, int b, int c) : b(b), a(a), c(c) { }

    ~test() {
        delete this->a;
    }
    void print() {
        cout << this->a << ' ' << this->b << ' ' << this->c;
    }
};

// Q1 conclustion -> it depends on the order in the constructor function
// not the initializer list.
// Q2 -> I'm not sure how to test this one.
int main () {
    test obj(1, 2, 3);
    obj.print();
    return 0;
}
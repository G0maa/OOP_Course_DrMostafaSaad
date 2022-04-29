#include <bits/stdc++.h>
using namespace std;

class A {
private:
    int x { };
public:
    void SetPrint() {
        x++;
        cout << "\n" << x << "\n";
    }
};

class B : public A {
public:

};

int main() {
    B test;
    test.SetPrint();
}
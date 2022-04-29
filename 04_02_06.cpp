#include <bits/stdc++.h>
using namespace std;

class test {
public:
    void func() {
        printf("Function address :%p\n", &test::func);
    }
};

int main () {
    test obj1;
    test obj2;
    obj1.func();
    obj2.func();
    // same address.
}
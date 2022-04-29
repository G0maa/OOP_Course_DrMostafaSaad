#include <bits/stdc++.h>
using namespace std;


class A {
private:
	int *x;
public:
	A() {
		cout<<"A constructor\n";
		x = new int;
		*x = 10;
	}
	~A() {
		cout<<"A destructor\n";
        delete x;
	}

};

int main() {
	A b;
    // delete b;
	return 0;
}
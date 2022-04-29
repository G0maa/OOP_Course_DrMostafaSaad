#include <bits/stdc++.h>
using namespace std;

class A {
public:
	static vector<int*> test;
	A() {
		
	}

	void change() {
		test.push_back(new int(2));
	}
	void print() {
		cout << *test[0];
	}
};

vector<int*> A::test = {};

int main() {
	A obj;
	
	obj.change();
	obj.print();
	return 0;
}
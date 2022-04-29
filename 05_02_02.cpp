#include <bits/stdc++.h>
using namespace std;

class ClassA {
public:
	ClassA() {
		cout<<"ClassA Constructor\n";
	}
};

class ClassB {
private:
	ClassA aa;
	int x;
public:
	ClassB(int x) : aa(ClassA()), x(x) {
	}
};

class ClassC {
private:
	int &y;
	ClassB bb;

public:
    // I think because of const -> initializer list only.
	ClassC(int &y, const ClassB &bb) : y(y), bb(bb){
	}
};

// 2 times classA will be called, because of class b calling class a, and class c calling class b callibng class a.
// tip: I don't know, probably call class A form class B directly.
int main() {
	int hello = 10;
	ClassB b(5);
	ClassC cc(hello, b);
	return 0;
}
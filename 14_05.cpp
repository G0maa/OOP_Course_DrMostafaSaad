// Mhm, pretty confusing.
// output: (before running it)
// F (Normal bool)
// FCTC (class 'Boolean')
// tip: if first part is false, return false without executing second part,
//      how to do that? dunno.
#include <bits/stdc++.h>
using namespace std;

class Boolean {
private:
	bool is_true;

public:
	Boolean(bool is_true) : is_true(is_true) {	}
	bool operator &&(const Boolean &other) const {
		return this->is_true && other.is_true;
	}
};

bool T() {	cout << "T\n";	return true;	}
bool F() {	cout << "F\n";	return false;	}

Boolean TC() {	cout << "TC\n";	return Boolean(true);	}
Boolean FC() {	cout << "FC\n";	return Boolean(false);	}

int main() {
	F() && T();
	FC() && TC();

	return 0;
}
// After output:
// erm... dunno
// I guess second one gets executed first when overloading.
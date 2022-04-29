#include <bits/stdc++.h>
using namespace std;

class MyPair {
private:
	int first, second;

public:
	MyPair(int first, int second) :
			first(first), second(second) {
	}

    // tie doesn't work with c1.GetFirst(), took me a while to figure that out .-.
	virtual bool operator <(const MyPair &c2) {
		MyPair &c1 = *this;
		return tie(c1.first, c1.second) <
               tie(c2.first, c2.second);
	}

	virtual void print() const {
		cout << "(" << first << "," << second << ")\n";
	}

	int GetFirst() const {
		return first;
	}

	void SetFirst(int first) {
		this->first = first;
	}

	int GetSecond() const {
		return second;
	}

	void SetSecond(int second) {
		this->second = second;
	}

    // void operator>>(istream &input) {
    //     input >> first >> second;
    // }

    // void operator<<(ostream &output) {
    //     output << first << second;
    // }
    friend istream& operator>>(istream &input, MyPair &pair);
    friend ostream& operator<<(ostream &output, const MyPair &pair);
};

istream& operator>>(istream &input, MyPair &pair) {
    input >> pair.first >> pair.second;
    return input;
}

// After seeing solution I thought the >> here was unintentional...
ostream& operator<<(ostream &output, const MyPair &pair) {
    output << pair.first << pair.second;
    return output;
}

// Tips:
//      - Unless you want to make people laugh you'd always need to overload << & >> as a non-member function.
//      - return them so you can do << x << y << z etc..
//      - const in output => not gonna change it.
//      - friend function for faster input.... or currupt it.. not sure :D
int main() {
    MyPair x(2, 3);
    // without changes in works like this: :DDD
    // x >> cin;
    // x << cout;
    // after changes:
    // After changes:
    cin >> x;
    cout << x;
}
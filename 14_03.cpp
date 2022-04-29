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
	// Dr Logic is better I guess.
	bool operator <(const MyPair &c2) {
		MyPair &c1 = *this;
		return tie(c1.first, c1.second) <
               tie(c2.first, c2.second);
	}

	void print() {
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
};

int main() {

    vector<MyPair> vec;
    vec.push_back(MyPair(10, 20));
    vec.push_back(MyPair(10, 7));
    vec.push_back(MyPair(1, 200));

    sort(vec.begin(), vec.end());

    for(auto &pair : vec)
        pair.print();

    return 0;
}
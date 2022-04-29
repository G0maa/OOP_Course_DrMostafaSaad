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
};

class NamedPair : public MyPair {
private:
    string name;
public:
    NamedPair(const string &name, const int &first, const int &second) : MyPair(first, second), name(name) {

    }

    string GetName() const {
		return name;;
	}

	void SetName(const string &name_) {
		this->name = name_;
	}

    virtual bool operator <(const NamedPair &c2) {
		NamedPair &c1 = *this;

		// Dr logic one if condition only.
        if(c1.name < c2.name)
            return true;
        else if(c1.name > c2.name)
            return false;
        
        return c1.MyPair::operator<(c2);
	}

	virtual void print() const {
		cout << "(" << GetName() << ": " << GetFirst() << "," << GetSecond() << ")\n";
	}

};

int main() {

    vector<NamedPair> vec;

    vec.push_back(NamedPair("A", 10, 20));
    vec.push_back(NamedPair("B", 10, 7));
    vec.push_back(NamedPair("B", 1, 200));

    sort(vec.begin(), vec.end());

    for(auto &pair : vec)
        pair.print();
    
    cout << "\n\n Bye :) \n\n";
    return 0;
}
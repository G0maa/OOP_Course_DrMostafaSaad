#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

class Array {
protected: // or private?
    int size { };
    int *ptr { };
public:

    Array(const int &size = 0) : size(size) {
        ptr = new int[size];
    }

    Array(const Array &other) {
        Copy(other);
    }

    // Forgot to delete old ptr[].
    void Copy(const Array &other) {
        ptr = new int[other.GetSize()];
        size = other.GetSize();
        for(int idx = 0; idx < size; idx++)
            (*this)[idx] = other[idx];
    }

    int& Get(int pos) {
        return ptr[pos];
    }

    int Get(int pos) const {
        return ptr[pos];
    }

    bool Compare(const Array &other) const {
        if(this->size != other.GetSize())
            return false;
        
        for(int idx = 0; idx < this->size; idx++) 
            if((*this)[idx] != other[idx])
                return false;
        
        return true;
    }
    
    void PrintAll() const {
        for(int idx = 0; idx < size; idx++)
            cout << ptr[idx] << ' ';
    }

    void InputAll() {
        cout << "You are expected to type in: " << size << " values now:\n";
        for(int idx = 0; idx < size; idx++)
            cin >> ptr[idx];
    }

    void IncrementAll() {
        for(int idx = 0; idx < size; idx++)
            ++ptr[idx];
    }

    int GetSize() const {
        return size;
    }

    // Is assignmnet a copy?
    // From dr solution => NO.
    // Should delete first then copy.
    Array& operator= (const Array &other) {
        if(this == &other)
            return *this;
        
        Copy(other);
        return *this;
    }

    int& operator[] (const int &pos) {
        return Get(pos);
    }

    int operator[] (const int &pos) const {
        return Get(pos);
    }

    bool operator== (const Array &arr) const {
        return Compare(arr);
    }

    bool operator!= (const Array &arr) const {
        return !Compare(arr);
    }

    Array& operator++() {
        IncrementAll();
        return *this;
    }

    Array operator++(int) {
        Array temp(*this);

        IncrementAll();
        return temp;
    }

    ~Array() {
        // Don't forget to destory me UwU.
        delete []ptr;
        ptr = nullptr;
    }
};

istream& operator>>(istream &input, Array &arr) {
    arr.InputAll(); // If you call function pass it the stream.
    return input;
}

ostream& operator<<(ostream &output, const Array &arr) {
    arr.PrintAll();
    return output;
}


void test_Array() {
	Array arr1(6);

	int counter = 0;
	for (int i = 0; i < arr1.GetSize(); ++i)
		arr1[i] = counter++;

	cout<<arr1<<"\n";

	Array arr2 = ++arr1;	// copy
	cout<<arr2<<"\n";

	if(arr2 == arr1)
		cout<<"arr2 == arr1\n";
	else
		cout<<"arr2 != arr1\n";

	Array arr3;
	arr3 = arr2++;
	cout<<arr3<<"\n";



	if(arr3 != arr1)
		cout<<"arr3 != arr1\n";
	else
		cout<<"arr3 == arr1\n";
}

int main() {
    test_Array();
    cout << "\n\n Bye :) \n\n";
    return 0;
}
// Couldn't solve.
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
    arr.InputAll();
    return input;
}

ostream& operator<<(ostream &output, const Array &arr) {
    arr.PrintAll();
    return output;
}



class Array2D : public Array {
private:
    int rows { };
    int colums { };
    
    // Couldn't solve this one.
    // Because of this, tried many things.
    // Never crossed my mind to just use Array(rows * colums)
    vector<Array*> ptr2D;

public:

    Array2D(const int &rows_ = 0, const int &colums_ = 0) {
        Create(rows_, colums_);
    }

    Array2D(const Array2D &other) {
        Copy(other);
    }

    void Create(const int &rows_, const int &colums_) {
        rows = rows_;
        colums = colums_;
        size = colums_;
        
        ptr2D.resize(rows);
        for(int idx = 0; idx < rows; idx++)
            ptr2D[idx] = new Array(colums);
    }

    void Copy(const Array2D &other) {
        Create(other.GetRows(), other.GetColums());

        for(int idx = 0; idx < rows; idx++)
            this[idx].Array::Copy(other[idx]);
     
    }

    Array& operator[] (const int &row) {
        return *ptr2D[row];
    }

    const Array& operator[] (const int &row) const {
        return *ptr2D[row];
    }

    int GetRows() const {
        return rows;
    }

    int GetColums() const {
        return colums;
    }

    int& Get(const int &i, const int &j) {
        return (*ptr2D[i])[j];
    }

    int Get(const int &i, const int &j) const {
        return (*ptr2D[i])[j];
    }

    int& operator() (const int &i, const int &j) {
        return Get(i, j);
    }

    int operator() (const int &i, const int &j) const {
        return Get(i, j);
    }

    // Revise and make sure to delete old one.
    Array2D& operator= (const Array2D &other) {
        if(this == &other)
            return *this;

        // delete this; hmmm.

        Copy(other);
        return *this;
    }

    void PrintAll() {
        for(int idx = 0; idx < rows; idx++)
            this[idx].Array::PrintAll();
    }

    void InputAll() {
        for(int idx = 0; idx < rows; idx++)
            this[idx].Array::InputAll();
    }

    bool Compare(const Array2D &arr2D) const {
        if(GetColums() != arr2D.GetColums() || GetRows() != arr2D.GetRows())
            return false;
        
        for(int i = 0; i < rows; i++)
            if(this[i].Array::Compare(arr2D[i]))

        return true;
    } 

    Array2D& operator++() {
        for(int idx = 0; idx < rows; idx++)
            this[idx].Array::IncrementAll();
        return *this;
    }

    Array2D operator++(int) {
        Array2D temp(*this);

        for(int idx = 0; idx < rows; idx++)
            this[idx].Array::IncrementAll();

        return temp;
    }

    ~Array2D() {
        // Hmmmm...
        for(int i = 0; i < rows; i++)
            delete (ptr2D[i]);
        
    }
};

istream& operator>>(istream &input, Array2D &arr) {
    arr.InputAll();
    return input;
}

ostream& operator<<(ostream &output, Array2D &arr) {
    arr.PrintAll();
    return output;
}

void test_Array2d() {
	Array2D arr1(2, 3);

	int counter = 0;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			arr1(i, j) = counter++;
		}
	}

	cout<<arr1<<"\n";

	Array2D arr2 = ++arr1;	// copy
	cout<<arr2<<"\n";

	if(arr2 == arr1)
		cout<<"arr2 == arr1\n";
	else
		cout<<"arr2 != arr1\n";

	Array2D arr3;
	arr3 = arr2++;
	cout<<arr3<<"\n";



	if(arr3 != arr1)
		cout<<"arr3 != arr1\n";
	else
		cout<<"arr3 == arr1\n";
}

int main() {
	test_Array2d();
	cout << "Bye\n";

	return 0;
}
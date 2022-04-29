#include <bits/stdc++.h>
using namespace std;

class MyVector {
private:
    int *arr;
    int len = 100;
public:
    MyVector(int len, int default_value = 0) {
        this->len = len;
        this->arr = new int[len];

        for(int i = 0; i < len; i++)
            this->arr[i] = default_value;
    }

    MyVector(const MyVector &another) {
        // should delete old arr?
        this->arr = new int[another.len];
        this->len = another.len;
        for(int i = 0; i < another.len; i++)
            this->arr[i] = another.arr[i];
    }

    ~MyVector() {
        delete[] this->arr;
    }

    int get(int pos) {
        if(pos < 0 || pos >= len)
            return -1;
        return this->arr[pos];
    }

    void set(int pos, int val) {
        if(pos < 0 || pos >= len)
            return;
        this->arr[pos] = val;
    }

    int& get_length() {
        return len;
    }
};

int main() {
    MyVector a(5);
    int &len = a.get_length();
    len = 3;
    cout << a.get_length();
    string test("hello");
}
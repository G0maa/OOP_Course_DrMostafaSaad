#include <bits/stdc++.h>
using namespace std;

vector<int> operator+(vector<int> &vec1, vector<int> &vec2) {
    if((int) vec1.size() > (int) vec2.size())
        swap(vec1, vec2); // this swap forbids me from using const.
    
    vector<int> vec_res;
    vec_res.resize((int) vec2.size());

    for(int idx = 0; idx < (int) vec1.size(); idx++)
        vec_res[idx] = vec1[idx] + vec2[idx];

    // Efficent.
    for(int idx = (int) vec1.size(); idx < (int) vec2.size(); idx++)
        vec_res[idx] = vec2[idx];

    return vec_res;
}

int main() {
    vector<int> a = {1, 2, 3, 4};
    vector<int> b = {10, 20};

    vector<int> c = a + b;

    for(int idx = 0; idx < (int) c.size(); idx++)
        cout << c[idx] << ' ';
    return 0;
}
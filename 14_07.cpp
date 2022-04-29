#include <bits/stdc++.h>
using namespace std;

class Double {
private:
    double num;
    const double EPS = (1e-7);
public:
    Double(double num) : num(num) { }

    // Double compare, if equal return 0, x bigger return -1, y bigger return 1.
    int dcmp(Double x, Double y) const { return fabs(x.num-y.num) <= EPS ? 0 : x < y ? -1 : 1; }

    // Much shorter conditions on dr's side .-.
    bool operator< (const Double &other) const {
        if(dcmp(num, other) == 1)
            return true;
        return false;
    }

    bool operator> (const Double &other) const {
        if(dcmp(num, other) == -1)
            return true;
        return false;
    }

    bool operator<= (const Double &other) const {
        int res = dcmp(num, other);

        if(res == 1)
            return true;
        if(res == 0)
            return true;

        return false;
    }


    // ^ Especially strting from here.
    bool operator>= (const Double &other) const {
        int res = dcmp(num, other);

        if(res == -1)
            return true;
        if(res == 0)
            return true;

        return false;
    }

    bool operator== (const Double &other) const {
        if(dcmp(num, other) == 0)
            return true;
        return false;
    }

};

int main() {
    double d1 = 1 + 3.0 / 7.0 - 1;
    double d2 = 3.0 / 7.0;

    cout << d1 << " " << d2 << " " << (d1 == d2) << "\n";

    Double cd1(d1);
    Double cd2(d2);

    cout << (cd1 == cd2) << "\n";

    map<Double, string> map;

    map[cd1] = 10;
    map[cd2] = 20;
    cout << map.size();
    return 0;
}
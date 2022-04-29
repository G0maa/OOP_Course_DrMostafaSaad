#include <bits/stdc++.h>
using namespace std;

class Fraction {
private:
    int n;
    int d;

    int gcd(int a, int b) { return (b == 0) ? a : gcd(b, a % b); }

    void Simplify() {
        int gcd_ = gcd(n, d);

        n /= gcd_;
        d /= gcd_;
    }
public:

    // No need for copy, no pointers.
    // Will be used for implicint conversion.
    Fraction(int n) : Fraction(n, 1) {}

    Fraction(int n, int d) : n(n), d(d) {
        Simplify();
    }

    // This one might need some more love, which I don't have in me rn.
    Fraction operator= (const Fraction &other) {
        Fraction res(other.n, other.d);
        return res;
    }

    friend istream& operator>>(istream &input, Fraction &pair);
    friend ostream& operator<<(ostream &output, const Fraction &pair);
    friend Fraction operator* (const Fraction &first, const Fraction &second);
    friend void operator*= (Fraction &first, const Fraction &second);
};

istream& operator>>(istream &input, Fraction &pair) {
    input >> pair.n >> pair.d;
    return input;
}

ostream& operator<<(ostream &output, const Fraction &pair) {
    output << pair.n << '/' << pair.d;
    return output;
}

Fraction operator* (const Fraction &first, const Fraction &second) {
    Fraction res(first.n * second.n, first.d * second.d);
    return res;
}

// Fraction&
void operator*= (Fraction &first, const Fraction &second) {
    first.n *= second.n;
    first.d *= second.d;
    first.Simplify();
    // return first;
}

int main() {
    Fraction f1(3, 8);
    Fraction f2 = 2 * f1;
    Fraction f3 = f1 * f2;
    Fraction f4 = f3;
    f4 *= f4;

    cout << f1 << '\n' << f2 << '\n' << f3 << '\n' << f4;

    cout << "\n\n Bye :) \n\n";
    return 0;
}
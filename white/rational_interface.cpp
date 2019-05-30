#include <iostream>
#include <sstream>
#include <iomanip>
#include <set>
#include <vector>
#include <map>

using namespace std;

class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
        int a = abs(numerator);
        int b = abs(denominator);
        int nod = 1;

        if (denominator == 0) {
            throw invalid_argument("Invalid argument");
        }

        while (a != 0 && b != 0) {
            if (a > b) {
                a = a % b;
            } else {
                b = b % a;
            }
        }

        nod = a + b;

        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }

        p = numerator / nod;
        q = denominator / nod;
    }

    int Numerator() const {
        return p;
    }

    int Denominator() const {
        return q;
    }

private:
    int p;
    int q;
};

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator();
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    return Rational(
        lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
        lhs.Denominator() * rhs.Denominator()
    );
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    return Rational(
        lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
        lhs.Denominator() * rhs.Denominator()
    );
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(
        lhs.Numerator() * rhs.Numerator(),
        lhs.Denominator() * rhs.Denominator()
    );
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    if (rhs.Numerator() == 0) {
        throw domain_error("Division by zero");
    }

    return Rational(
        lhs.Numerator() * rhs.Denominator(),
        lhs.Denominator() * rhs.Numerator()  
    );
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    int l = lhs.Numerator() * rhs.Denominator();
    int r = rhs.Numerator() * lhs.Denominator();
    return l < r;
}

istream& operator>>(istream& stream, Rational& rational) {
    int numerator = 0;
    int denominator = 1;
    
    if (stream >> numerator) {
        stream.ignore(1);
        if (stream >> denominator) {
            rational = Rational(numerator, denominator); 
        }
    }
    return stream;
}

ostream& operator<<(ostream& stream, const Rational& rational) {
    stream << rational.Numerator() << "/" << rational.Denominator();
    return stream;
}

int main() {
    Rational r1;
    Rational r2;
    char operation;

    try {
        cin >> r1;
        cin.ignore(1);
        cin >> operation;
        cin.ignore(1);
        cin >> r2;
    } catch(invalid_argument& e) {
        cout << e.what() << endl;
        return 0;
    }

    if (operation == '+') {
        cout << r1 + r2 << endl;
    } else if (operation == '-') {
        cout << r1 - r2 << endl;
    } else if (operation == '*') {
        cout << r1 * r2 << endl;
    } else if (operation == '/') {
        try {
            cout << r1 / r2 << endl;
        } catch(domain_error& e) {
            cout << e.what() << endl;
            return 0;
        } 
    }

}

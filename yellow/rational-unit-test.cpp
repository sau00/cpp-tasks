#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream &operator<<(ostream &os, const vector<T> &s)
{
    os << "{";
    bool first = true;
    for (const auto &x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream &operator<<(ostream &os, const set<T> &s)
{
    os << "{";
    bool first = true;
    for (const auto &x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m)
{
    os << "{";
    bool first = true;
    for (const auto &kv : m)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {})
{
    if (t != u)
    {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty())
        {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string &hint)
{
    AssertEqual(b, true, hint);
}

class TestRunner
{
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string &test_name)
    {
        try
        {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception &e)
        {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...)
        {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner()
    {
        if (fail_count > 0)
        {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

class Rational
{
public:
    // Вы можете вставлять сюда различные реализации,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный

    Rational() {
        n = 0;
        d = 1;
    }
    Rational(int numerator, int denominator)
    {
        n = numerator;
        d = denominator;
    }

    int Numerator() const
    {
        return n;
    }

    int Denominator() const
    {
        return d;
    }

private:
    int n, d;
};

void TestDefaultRational() {
    Rational r;
    AssertEqual(r.Numerator(), 0, "Numerator");
    AssertEqual(r.Denominator(), 1, "Denominator");
}

void TestFractionReduction() {
    Rational r(9, 3);
    AssertEqual(r.Numerator(), 3, "numerator");
    AssertEqual(r.Denominator(), 1, "denominator");
}

void TestNegativity() {
    Rational r(3, -1);
    AssertEqual(r.Numerator(), -3, "numerator");
    AssertEqual(r.Denominator(), 1, "denominator");
}

void TestPositivity() {
    Rational r(3, 1);
    AssertEqual(r.Numerator(), 3, "numerator");
    AssertEqual(r.Denominator(), 1, "denominator");

    Rational(-3, -1);
    AssertEqual(r.Numerator(), 3, "numerator");
    AssertEqual(r.Denominator(), 1, "denominator");
}

void TestZero() {
    Rational r(0, 10);
    Assert(r.Denominator() == 1, "denominator");
}

void RunTests()
{
    TestRunner runner;
    runner.RunTest(TestDefaultRational, "TestDefaultRational");
    runner.RunTest(TestFractionReduction, "TestFractionReduction");
    runner.RunTest(TestNegativity, "TestNegativity");
    runner.RunTest(TestPositivity, "TestPositivity");
    runner.RunTest(TestZero, "TestZero");
}

int main()
{
    RunTests();

    return 0;
}

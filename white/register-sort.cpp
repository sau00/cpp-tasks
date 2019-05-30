#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>

using namespace std;

void Print(const vector<string>& v) {
    for (const auto& i : v) {
        cout << i << " ";
    }
}

int main() {
    int n;
    cin >> n;

    vector<string> v(n);

    for (auto& i : v) {
        cin >> i;
    }

    sort(begin(v), end(v), [](string i, string j) {
        string s1, s2;

        for (const auto& c : i) {
            s1.push_back(tolower(c));
        }

        for (const auto& c : j) {
            s2.push_back(tolower(c));
        }

        return s1 < s2;
    });

    Print(v);

    return 0;
}
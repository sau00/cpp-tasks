#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {

    int q;
    cin >> q;

    set<string> words;

    for (int i = 0; i < q; ++i) {
        string s;
        cin >> s;
        words.insert(s);
    }

    cout << words.size();
    
    return 0;
}
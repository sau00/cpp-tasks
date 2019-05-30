#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <map>

using namespace std;

void Add(map<set<string>, bool>& s, map<string, int>& s_c, const string& w1, const string& w2) {
    set<string> words;
    words.insert(w1);
    words.insert(w2);

    if (s.count(words) == 0) {
        s[words] = true;
        s_c[w1]++;
        s_c[w2]++;
    }
}

int main() {
    int q;
    cin >> q;

    map<set<string>, bool> syn;
    map<string, int> syn_counter;

    for (int i = 0; i < q; ++i) {
        string cmd;
        cin >> cmd;
        if (cmd == "ADD") {
            string w1, w2;
            cin >> w1 >> w2;
            Add(syn, syn_counter, w1, w2);
        }

        if (cmd == "COUNT") {
            string w;
            cin >> w;
            cout << syn_counter[w] << endl;
        }

        if (cmd == "CHECK") {
            string w1, w2;
            cin >> w1 >> w2;
            set<string> pair;
            pair.insert(w1);
            pair.insert(w2);

            if (syn.count(pair) == 0) {
                cout << "NO" << endl;
            } else {
                cout << "YES" << endl;
            }
        }
    }

    return 0;
}
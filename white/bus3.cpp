#include <iostream>
#include <map>
#include <set>
using namespace std;

int main() {
    int q;
    int n;
    cin >> q;

    map<set<string>, int> stops;
    int counter = 0;
    for (int i = 0; i < q; ++i) {
        cin >> n;
        set<string> stop;
        for (int j = 0; j < n; ++j) {
            string s;
            cin >> s;
            stop.insert(s);
        }

        if (stops.count(stop) == 0) {
            counter++;
            stops[stop] = counter;
            cout << "New bus " << counter << endl;
        } else {
            cout << "Already exists for " << stops[stop] << endl;
        }
    }
}
#include <iostream>
#include <set>
#include <map>
using namespace std;

int main() {
    int q;
    cin >> q;
    map<set<string>, int> routes;
    int counter = 1;
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        set<string> stops;

        for (int i = 0; i < k; ++i) {
            string s;
            cin >> s;
            stops.insert(s);
        }

        if (routes.count(stops) == 0) {
            routes[stops] = counter;
            cout << "New bus " << counter << endl;
            counter++;
        } else {
            cout << "Already exists for " << routes[stops] << endl;
        }
    } 

    return 0;
}
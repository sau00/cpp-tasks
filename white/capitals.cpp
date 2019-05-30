#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
using namespace std;

int main() {
    int k;

    cin >> k;

    map<string, string> country_capital;

    for (int i = 0; i < k; ++i) {
        string cmd;
        cin >> cmd;

        if (cmd == "CHANGE_CAPITAL") {
            string country, new_capital;
            cin >> country >> new_capital;

            if (country_capital.count(country) == 0) {
                cout << "Introduce new country " << country << " with capital " << new_capital << endl;
            } else {
                if (country_capital[country] == new_capital) {
                    cout << "Country " << country << " hasn't changed its capital" << endl;
                } else {
                    cout << "Country " << country << " has changed its capital from " << country_capital[country] << " to " << new_capital << endl;
                }
            }
            country_capital[country] = new_capital;
        } else if (cmd == "RENAME") {
            string old_country_name, new_country_name;
            cin >> old_country_name >> new_country_name;
            if (old_country_name == new_country_name || country_capital.count(old_country_name) == 0 || country_capital.count(new_country_name) == 1) {
                cout << "Incorrect rename, skip" << endl;
            } else {
                cout << "Country " << old_country_name << " with capital " << country_capital[old_country_name] << " has been renamed to " << new_country_name << endl;
                country_capital[new_country_name] = country_capital[old_country_name];
                country_capital.erase(old_country_name);
            }
        } else if (cmd == "ABOUT") {
            string country;
            cin >> country;

            if (country_capital[country] == "") {
                cout << "Country " << country << " doesn't exist" << endl;
                country_capital.erase(country);
            } else {
                cout << "Country " << country << " has capital " << country_capital[country] << endl;
            }
        } else if (cmd == "DUMP") {
            if (country_capital.size() <= 0) {
                cout << "There are no countries in the world" << endl;
            } else {
                for (auto& cc : country_capital) {
                    cout << cc.first << "/" << cc.second << " ";
                }

                cout << endl;
            }

        }
    }

    return 0;
}
#include <iostream>
#include <map>
#include <vector>
using namespace std;

void NewBus(map<string, vector<string>>& b, vector<string>& bo) {
    int count;
    string route_name;
    string stop_name;
    cin >> route_name >> count;
    for (int i = 0; i < count; ++i) {
        cin >> stop_name;
        b[route_name].push_back(stop_name);
    }
    bo.push_back(route_name);
}

// Выводим автобусные маршруты для конкретной остановки
void PrintBusesForStop(map<string, vector<string>>& b, vector<string>& bo, string stop) {
    bool empty = true;

    for (auto& r : bo) {
        for (auto& s : b[r]) {
            if (s == stop) {
                empty = false;
                cout << r << " ";
            }
        }
    }

    if (empty) {
        cout << "No stop";
    }

    cout << endl;
}

// Мы выводим список остановок каждого конкретного автобусного маршрута (string bus)
// И для каждой остановки мы выводим список автобусов, которые через эту остановку проезжают
void PrintStopsForBus(map<string, vector<string>>& b, vector<string>& bo, string route_name) {
    if (b.count(route_name) > 0) {
        for (auto& s : b[route_name]) {
            cout << "Stop " << s << ": ";
            bool empty = true;
            for (auto& r : bo) {
                for (auto& s1 : b[r]) {
                    if (s1 == s && r != route_name) {
                        empty = false;
                        cout << r << " ";
                    }
                }
            }

            if (empty) {
                cout << "no interchange";
            }

            cout << endl;
        }
    } else {
        cout << "No bus" << endl;
    }
}

void PrintAllBuses(const map<string, vector<string>>& b, vector<string>& bo) {
    if (!b.empty()) {
        for (auto& r : b) {
            cout << "Bus " << r.first << ": ";
                for (auto& s : r.second) {
                    cout << s << " ";
                }
            cout << endl;
        }
    } else {
        cout << "No buses" << endl;
    }
}

int main() {
    int q;
    string cmd;
    // map[bus] = [stop1, stop2, stop3];
    map<string, vector<string>> b;
    vector<string> bo;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        cin >> cmd;
        if (cmd == "NEW_BUS") {
            NewBus(b, bo);
        } else if (cmd == "BUSES_FOR_STOP") {
            string stop;
            cin >> stop;
            PrintBusesForStop(b, bo, stop);
        } else if (cmd == "STOPS_FOR_BUS") {
            string bus;
            cin >> bus;
            PrintStopsForBus(b, bo, bus);
        } else if (cmd == "ALL_BUSES") {
            PrintAllBuses(b, bo);
        }

    }

    return 0;
}
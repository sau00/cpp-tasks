#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType
{
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query
{
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream &operator>>(istream &is, Query &q)
{
    q = {};
    string query_type;
    is >> query_type;

    if (query_type == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        
        int stops_count;
        is >> stops_count;

        for (int i = 0; i < stops_count; ++i) {
            string stop;
            is >> stop;
            q.stops.push_back(stop);
        }
    }

    if (query_type == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }

    if (query_type == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }

    if (query_type == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse
{
    string stop;
    map<string, vector<string>> stops_to_buses;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r)
{
    if (r.stops_to_buses.count(r.stop) == 0) {
        cout << "No stop" << endl;
      } else {
        for (const string& bus : r.stops_to_buses.at(r.stop)) {
          cout << bus << " ";
        }
        cout << endl;
      }
    return os;
}

struct StopsForBusResponse
{
    // Название маршрута
    string bus;
    // Остановки всех автобусов
    map<string, vector<string>> stops_to_buses;
    // Остановки данного автобуса
    map<string, vector<string>> buses_to_stops;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r)
{
    if (r.buses_to_stops.count(r.bus) == 0) {
        cout << "No bus" << endl;
    } else {
        for (const string& stop : r.buses_to_stops.at(r.bus)) {
            cout << "Stop " << stop << ": ";
            if (r.stops_to_buses.at(stop).size() == 1) {
                cout << "no interchange";
            } else {
                for (const string& other_bus : r.stops_to_buses.at(stop)) {
                    if (r.bus != other_bus) {
                        cout << other_bus << " ";
                    }
                }
            }
            cout << endl;
        }
    }
    return os;
}

struct AllBusesResponse
{
    map<string, vector<string>> buses_to_stops;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r)
{
    if (r.buses_to_stops.empty()) {
        cout << "No buses" << endl;
    } else {
        for (const auto& bus_item : r.buses_to_stops) {
            cout << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second) {
                cout << stop << " ";
            }
            cout << endl;
        }
    }

    return os;
}

class BusManager
{
public:
    void AddBus(const string &bus, const vector<string> &stops)
    {
        buses_to_stops[bus] = stops;
        for (string& stop : buses_to_stops[bus]) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string &stop) const
    {
        return {stop, stops_to_buses};
    }

    StopsForBusResponse GetStopsForBus(const string &bus) const
    {
        return {bus, stops_to_buses, buses_to_stops};
    }

    AllBusesResponse GetAllBuses() const
    {
        return {buses_to_stops};
    }

private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main()
{
    int query_count;
    Query q;

    cin >> query_count;
    BusManager bm;
    for (int i = 0; i < query_count; ++i)
    {
        cin >> q;
        switch (q.type)
        {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}

#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <set>
#include <iomanip>
#include <vector>

using namespace std;

// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
public:
  Date() {
    day = 0;
    month = 0;
    year = 0;
  }
  Date(const string& date) {
    int d, m, y = 0;
    istringstream ss(date);
    
    string sd, sm, sy;
    
    ss >> y;
    ss.ignore(1);
    ss >> m;
    ss.ignore(1);
    ss >> d;

    // Проверяем на соответствие формату
    if (!ValidateFormat(date)) {
      throw runtime_error("Wrong date format: " + date);
    }

    if (!ValidateMonth(m)) {
      throw runtime_error("Month value is invalid: " + to_string(m));
    }

    if (!ValidateDay(d)) {
      throw runtime_error("Day value is invalid: " + to_string(d));
    }

    day = d;
    month = m;
    year = y;
  }

  int GetYear() const {
    return year;
  }

  int GetMonth() const {
    return month;
  }

  int GetDay() const {
    return day;
  }

private:
  int year;
  int month;
  int day;

  bool ValidateFormat(const string& date) const {
    // Проверяем на наличие запрещенных символов в строке
    for (const auto& s : date) {
      if (!ValidateSymbol(s)) {
        return false;
      }
    }
    
    // Эта проверка отметает всё, что имеет в своем наличии более трех символов -, в любой части строки    
    if (!ValidateMinuses(date)) {
      return false;
    }

    // Проверяем длину разрядности 
    if (!ValidateCapacity(date)) {
      return false;
    }

    istringstream ss(date);
    vector<int> date_items;
    while (ss) {
      int val;
      ss >> val;
      ss.ignore(1);
      date_items.push_back(val);
    }

    if (date_items.size() != 3) {
      return false;
    }

    return true;
  }

  bool ValidateMinuses(const string& date) const {
    istringstream ss(date);
    string val;
    int hyphen_counter = 1;
    while (getline(ss, val , '-')) {
      if (val.length() > 0) {
        hyphen_counter = 1;
      } else {
        ++hyphen_counter;
      }

      if (hyphen_counter > 2) {
        return false;
      }
    }

    return true;
  }

  bool ValidateCapacity(const string& date) const {
    istringstream ss(date);
    vector<int> date_items;
    while (ss) {
      int val;
      if(ss >> val) {
        ss.ignore(1);
        date_items.push_back(val);
      }
    }

    if (date_items.size() != 3) {
      return false;
    }
    return true;
  }

  bool ValidateSymbol(const char& s) const {
    string allowed_symbols = "-+0123456789";
    for (const auto& as : allowed_symbols) {
      if (s == as) {
        return true;
      }
    }
    return false;
  }

  bool ValidateMonth(const int& m) {
    if (m < 1 || m > 12) {
      return false;
    } else {
      return true;
    }
  }

  bool ValidateDay(const int& d) {
    if (d < 1 || d > 31) {
      return false;
    } else {
      return true;
    }
  }
};

istream& operator >> (istream& is, Date& d) {
  string str_date;
  is >> str_date;
  d = Date(str_date);
  return is;
}

bool operator < (const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() == rhs.GetYear()) {
    if (lhs.GetMonth() == rhs.GetMonth()) {
      return lhs.GetDay() < rhs.GetDay();
    } else {
      return lhs.GetMonth() < rhs.GetMonth();
    }
  } else {
    return lhs.GetYear() < rhs.GetYear();
  }
}

bool operator == (const Date& lhs, const Date& rhs) {
  return lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() == rhs.GetDay();
}

class Database {
public:
  void AddEvent(const Date& date, const string& event) {
    db[date].insert(event);
  }
  bool DeleteEvent(const Date& date, const string& event) {
    for (auto& row : db) {
      if (row.first == date) {
        for (const auto& row_event : row.second) {
          if (row_event == event) {
            row.second.erase(event);
            return true;
          }
        }
      }
    }

    return false;
  }
  int DeleteDate(const Date& date) {
    int res = db[date].size();
    db.erase(date);
    return res;
  }

  void Find(const Date& date) const {
    if (db.count(date) > 0) {
      for (const auto& event : db.at(date)) {
        cout << event << endl;
      }
    }
  }
  
  void Print() const {
    for (const auto& row : db) {
      for (const auto& event : row.second) {
        Date d = row.first;
        cout << setfill('0');
        cout << setw(4) << d.GetYear() << "-" 
          << setw(2) << d.GetMonth() << "-" 
          << setw(2) << d.GetDay() 
          << " " << event << endl;
      }
    }
  }

private:
  map<Date, set<string>> db;
};

int main() {
  Database db;
  
  string line;
  while (getline(cin, line)) {
    // Считайте команды с потока ввода и обработайте каждую

    stringstream ss(line);
    string command;
    getline(ss, command, ' ');

    try {
      if (command == "Add") {
        Date date;
        ss >> date;

        string event;
        ss >> event;

        db.AddEvent(date, event);

        // Завтра надо будет добавить валидацию считывания команд и функцию печати. Данные буду хранить как map<Date, set<string>>
        // cout << date.GetDay() << "." << date.GetMonth() << "." << date.GetYear() << endl;
      } else if (command == "Del") {
        Date date;
        ss >> date;

        string event;
        ss >> event;

        if (event.length() > 0) {
          if (db.DeleteEvent(date, event)) {
            cout << "Deleted successfully" << endl;
          } else {
            cout << "Event not found" << endl;
          }
        } else {
          cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
        }
      } else if (command == "Find") {
        Date date;
        ss >> date;
        db.Find(date);
      } else if (command == "Print") {
        db.Print();
      } else if (command != "") {
        cout << "Unknown command: " << command << endl;
      }
    } catch (exception& e) {
      cout << e.what() << endl;
      return 0;
    }
  }

  return 0;
}
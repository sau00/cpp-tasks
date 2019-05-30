#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        firstnames[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        lastnames[year] = last_name;
    }
    string GetFullName(int year) {
        const string firstname = FindNameByYear(firstnames, year);
        const string lastname = FindNameByYear(lastnames, year);

        if (firstname.empty() && lastname.empty()) {
            return "Incognito";
        } else if (lastname.empty()) {
            return firstname + " with unknown last name";
        } else if (firstname.empty()) {
            return lastname + " with unknown first name";
        } else {
            return firstname + " " + lastname;
        }
    }
    string GetFullNameWithHistory(int year) {
        const string firstname = FindNamesArchive(firstnames, year);
        const string lastname = FindNamesArchive(lastnames, year);

        if (firstname.empty() && lastname.empty()) {
            return "Incognito";
        } else if (lastname.empty()) {
            return firstname + " with unknown last name";
        } else if (firstname.empty()) {
            return lastname + " with unknown first name";
        } else {
            return firstname + " " + lastname;
        }
    }
private:
    map<int, string> firstnames;
    map<int, string> lastnames;

    string FindNamesArchive(const map<int, string>& names, int year) {
        vector<string> res_names;
        int k = 0;
        
        for (const auto& i : names) {
            if (i.first <= year) {
                // Это для того, чтобы два раза подряд не было смены фамилии
                if (res_names.size() > 0) {
                    if (i.second != res_names[k]) {
                        // cout << i.second << k << " - || ";
                        res_names.push_back(i.second);
                        k++;
                    }
                } else {
                    res_names.push_back(i.second);
                }
            } else {
                break;
            }
        }

        if (res_names.size() >= 2) {
            string res = res_names[res_names.size() - 1] + " (";

            for (int i = res_names.size() - 2; i >= 0; --i) {
                res += res_names[i];
                if (i == 0) {
                    res += ")";
                } else {
                    res += ", ";
                }
            }

            return res;
        } else {
            return FindNameByYear(names, year);
        }
    }

    string FindNameByYear(const map<int, string>& names, int year) {
        string name;

        for (const auto& i : names) {
            if (i.first <= year) {
                name = i.second;
            } else {
                break;
            }
        }

        return name;
    }
};

int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1990, "Polina");
  person.ChangeLastName(1990, "Volkova-Sergeeva");
  cout << person.GetFullNameWithHistory(1990) << endl;
  
  person.ChangeFirstName(1966, "Pauline");
  cout << person.GetFullNameWithHistory(1966) << endl;
  
  person.ChangeLastName(1960, "Sergeeva");
  for (int year : {1960, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1961, "Ivanova");
  cout << person.GetFullNameWithHistory(1967) << endl;
  
  return 0;
}

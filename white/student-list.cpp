#include <iostream>
#include <vector>
using namespace std;

struct Birthdate {
    int day;
    int month;
    int year;
};

struct Student {
    string firstname;
    string lastname;
    Birthdate birthdate;
};

void PrintStudents(const vector<Student>& students) {
    for (auto& student : students) {
        cout << "Firstname: " << student.firstname << endl;
    }
}

int main() {
    // amount of students to read
    int n = 0;
    cin >> n;
    vector<Student> students(n);

    for (auto& student : students) {
        cin >> student.firstname >> student.lastname 
            >> student.birthdate.day >> student.birthdate.month 
            >> student.birthdate.year;
    }

    // amount of requests to exec
    int m = 0;
    cin >> m;

    for (int i = 0; i < m; ++i) {
        string cmd;
        int sn; // student_number
        cin >> cmd >> sn;
        -- sn;

        if (cmd == "name" && sn < n && sn >= 0) {
            // Print name
            cout << students[sn].firstname << " " << students[sn].lastname << endl;
        } else if (cmd == "date" && sn < n && sn >= 0) {
            cout << students[sn].birthdate.day << "." << students[sn].birthdate.month << "." << students[sn].birthdate.year << endl;
        } else {
            cout << "bad request" << endl;
        }
    }

    return 0;
}
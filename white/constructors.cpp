#include <string>
#include <iostream>

using namespace std;

class ReversibleString {
    public: 
        ReversibleString() {}
        ReversibleString(string a_string) {
            str = a_string;
        }
        
        // Метод переворачивает строку задом наперед. И сохраняет это
        void Reverse() {
            string tmp;
            for (const auto& s : str) {
                tmp = s + tmp;
            }
            str = tmp;
        }

        string ToString() const {
            return str;
        }

    private:
        string str;
};

int main() {
  ReversibleString s("live");
  s.Reverse();
  cout << s.ToString() << endl;
  
  s.Reverse();
  const ReversibleString& s_ref = s;
  string tmp = s_ref.ToString();
  cout << tmp << endl;
  
  ReversibleString empty;
  cout << '"' << empty.ToString() << '"' << endl;
  
  return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class FunctionPart {
    public:
        FunctionPart(const char& new_cmd, const double& new_val) {
            cmd = new_cmd;
            val = new_val;
        }
        double Apply(double new_val) const {
            if (cmd == '+') {
                return new_val + val;
            } else if (cmd == '-') {
                return new_val - val;
            }
        }
        void Invert() {
            if (cmd == '+') {
                cmd = '-';
            } else if (cmd == '-') {
                cmd = '+';
            }
        }
    private:
        char cmd;
        double val;
};

class Function {
    public:
        void AddPart(const char& cmd, const double& val) {
            parts.push_back({cmd, val});
        }
        double Apply(double val) const {
            for (const auto& part : parts) {
                val = part.Apply(val);
            }

            return val;
        }
        void Invert() {
            for (auto& part : parts) {
                part.Invert();
            }
            reverse(parts.begin(), parts.end());
        }

    private:
        vector<FunctionPart> parts;
};
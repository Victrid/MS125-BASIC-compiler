#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
using namespace std;
class asmproc {
    //This is for label replacing.

    vector<pair<int, string>> lines;
    vector<string> prgm;
    void asm_assert(bool b, string str) {
        if (!b)
            throw logic_error("Asm Error: " + str);
    }

public:
    void asmp_inputline(istream& is, ostream& os) {
        string str;
        smatch res;
        while (getline(is, str)) {
            if (regex_match(str, res, regex("(.*):$"))) {
                lines.push_back(pair<int, string>(prgm.size(), res[1].str()));
                prgm.push_back("addi zero, zero, 0");
            } else {
                prgm.push_back(str);
            }
        }
        for (auto i = prgm.begin(); i != prgm.end(); i++) {
            if (regex_match((*i), res, regex("(.*)(label_.+)$")))
                for (auto j : lines) {
                    if (j.second == res[2].str()) {
                        string str = regex_replace((*i), regex("(.*)\\s(label_.+)$"), "$1 " + to_string((j.first - (i - prgm.begin())) * 4));
                        (*i)       = str;
                    }
                }
        }
        for (auto i : prgm) {
            os << i << endl;
        }
    }
};
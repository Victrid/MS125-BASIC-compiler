#include "lexer.hpp"
using namespace std;
int main(int argc, char** argv) {
    switch (argc) {
    case 1:
        lineproc(cin, cout);
    case 2: {
        fstream f;
        f.open(argv[1]);
        if (!f)
            throw exception();
        lineproc(f, cout);
    } break;
    case 3: {
        fstream f1, f2;
        f1.open(argv[1]);
        f2.open(argv[2],ios::out);
        if ((!f1) || (!f2))
            throw exception();
        lineproc(f1, f2);
    } break;
    default:
        throw invalid_argument("Wrong argument!");
    }
    return 0;
}
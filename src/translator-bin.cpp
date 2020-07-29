#include "parser.hpp"
#include "translate.hpp"
using namespace std;
int main(int argc, char** argv) {
    translator T;
    switch (argc) {
    case 1: {
        node t = buildtree(cin);
        T.translate(&t, cout);
    } break;
    case 2: {
        fstream f;
        f.open(argv[1]);
        if (!f)
            throw exception();
        node t = buildtree(f);
        T.translate(&t, cout);
        f.close();
    } break;
    case 3: {
        fstream f1, f2;
        f1.open(argv[1]);
        f2.open(argv[2], ios::out);
        if ((!f1) || (!f2))
            throw exception();
        node t = buildtree(f1);
        f1.close();
        T.translate(&t, f2);
        f2.close();
    } break;
    default:
        throw invalid_argument("Wrong argument!");
    }
    return 0;
}
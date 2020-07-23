#include "ordos.hpp"
#include "parser.hpp"
using namespace std;
int main(int argc, char** argv) {
    switch (argc) {
    case 1: {
        node t = buildtree(cin);
        orderconstruct(&t);
        cout << t;
    } break;
    case 2: {
        fstream f;
        f.open(argv[1]);
        if (!f)
            throw exception();
        node t = buildtree(f);
        orderconstruct(&t);
        cout << t;
        f.close();
    } break;
    case 3: {
        fstream f1, f2;
        f1.open(argv[1]);
        f2.open(argv[2], ios::out);
        if ((!f1) || (!f2))
            throw exception();
        node t = buildtree(f1);
        orderconstruct(&t);
        f2 << t;
        f1.close();
        f2.close();
    } break;
    default:
        throw invalid_argument("Wrong argument!");
    }
    return 0;
}
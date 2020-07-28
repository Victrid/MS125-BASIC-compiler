#include "ordos.hpp"
#include "parser.hpp"
using namespace std;
int main(int argc, char** argv) {
    switch (argc) {
    case 1: {
        node t = buildtree(cin);
        stringstream sttl, sttt;
        sttl << t;
        cfgize_labelproc(sttl, sttt);
        cfgize_symbolproc(sttt, cout);
    } break;
    case 2: {
        fstream f;
        f.open(argv[1]);
        if (!f)
            throw exception();
        node t = buildtree(f);
        stringstream sttl, sttt;
        sttl << t;
        cfgize_labelproc(sttl, sttt);
        cfgize_symbolproc(sttt, cout);
        f.close();
    } break;
    case 3: {
        fstream f1, f2;
        f1.open(argv[1]);
        f2.open(argv[2], ios::out);
        if ((!f1) || (!f2))
            throw exception();
        node t = buildtree(f1);
        stringstream sttl, sttt;
        sttl << t;
        cfgize_labelproc(sttl, sttt);
        cfgize_symbolproc(sttt, f2);
        f1.close();
        f2.close();
    } break;
    default:
        throw invalid_argument("Wrong argument!");
    }
    return 0;
}
#include "lexer.hpp"
using namespace std;
int main(int argc, char** argv) {
    fstream f;
    string str;
    if (argc != 2)
        throw exception();
    f.open(argv[1]);
    if (!f)
        throw exception();
    lineproc(f, cout);
    return 0;
}
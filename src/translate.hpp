#include "parser.hpp"
#include <stack>
using namespace std;
class translator {
public:
    void calc(node* n, ostream& os) {
        //USES t0,t1,t2
        //answer stored to a0.
        if (n->child[0]->klass == "CALC") {
            calc(n->child[0], os);
            os << "mv t0, a0" << endl;
        } else if (n->child[0]->klass == "ID") {
            loadmem(n->child[0]->value, os);
            os << "mv t0, a0" << endl;
        } else if (n->child[0]->klass == "NUM") {
            os << "li t0, " << n->child[0]->value << endl;
        }
        if (n->child[1]->klass == "CALC") {
            calc(n->child[1], os);
            os << "mv t1, a0" << endl;
        } else if (n->child[1]->klass == "ID") {
            loadmem(n->child[1]->value, os);
            os << "mv t1, a0" << endl;
        } else if (n->child[1]->klass == "NUM") {
            os << "li t1," << n->child[1]->value << endl;
        }
        if (n->value == "or") {
            os << "or a0,t0,t1" << endl;
        } else if (n->value == "and") {
            os << "and a0,t0,t1" << endl;
        } else if (n->value == "ne") {
            os << "sub a0, t0, t1" << endl;
            os << "sltu a0, zero, a0" << endl;
        } else if (n->value == "eq") {
            os << "sub a0, t0, t1" << endl;
            os << "sltu a0, zero, a0" << endl;
            os << "xori a0, a0, 1" << endl;
        } else if (n->value == "le") {
            os << "sltu a0, t1, t0" << endl;
            os << "xori a0, a0, 1" << endl;
        } else if (n->value == "ge") {
            os << "sltu a0, t0, t1" << endl;
            os << "xori a0, a0, 1" << endl;
        } else if (n->value == "g") {
            os << "sltu a0, t0, t1" << endl;
        } else if (n->value == "l") {
            os << "sltu a0, t1, t0" << endl;
        } else if (n->value == "min") {
            os << "sub a0, t0, t1" << endl;
        } else if (n->value == "add") {
            os << "add a0, t1, t0" << endl;
        } else if (n->value == "mul") {
            os << "mul a0, t0, t1" << endl;
        } else if (n->value == "div") {
            os << "div a0, t1, t0" << endl;
        } else { //ASSERT
        }
        return;
    }

    void expr(node* n, ostream& os) {
        if (n->klass == "ID") {
            loadmem(n->value, os);
            return;
        }
        if (n->klass == "NUM") {
            os << "li a0," << n->child[1]->value << endl;
            return;
        }
        if (n->klass == "CALC") {
            calc(n, os);
            return;
        }
        //ASSERT
    }

    void stam(node* n, ostream& os) {
        //uses t0
        expr(n->child[1], os);
        storemem(n->child[0]->value, os);
    }

    void let(node* n, ostream& os) {
        expr(n->child[1], os);
        storemem(n->value, os);
    }

    void label(node* n, ostream& os) {
        os << "label_" << n->value << ":" << endl;
    }

    void input(node* n, ostream& os) {
        for (auto i : n->child) {
            os << "input" << endl;
            storemem(i->value, os);
        }
    }

    void ifcase(node* n, ostream& os) {
        //TODO
    }

    void loadmem(string str, ostream& os) {
        //load to a0
    }

    void storemem(string str, ostream& os) {
        //store a0
    }
};
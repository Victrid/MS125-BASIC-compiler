#include "parser.hpp"
#include <stack>
using namespace std;
class translator {
private:
    void start(ostream& os) {
        os << "label_init:" << endl
           << "lui sp, 256" << endl
           << "lui gp, 2048" << endl
           << "jal ra, label_main" << endl
           << "addi a0, x0, 255" << endl
           << "label_main:" << endl;
    }

    void l_calc(node* n, ostream& os) {
        //USES t0,t1,t2
        //answer stored to a0.
        if (n->child[0]->klass == "CALC") {
            l_calc(n->child[0], os);
            os << "push a0" << endl;
        } else if (n->child[0]->klass == "ID") {
            loadvariable(n->child[0]->value, os);
            os << "push a0" << endl;
        } else if (n->child[0]->klass == "NUM") {
            os << "li t0, " << n->child[0]->value << endl;
            os << "push t0" << endl;
        }
        if (n->child[1]->klass == "CALC") {
            l_calc(n->child[1], os);
            os << "mv t1, a0" << endl;
        } else if (n->child[1]->klass == "ID") {
            loadvariable(n->child[1]->value, os);
            os << "mv t1, a0" << endl;
        } else if (n->child[1]->klass == "NUM") {
            os << "li t1," << n->child[1]->value << endl;
        }
        os << "pop t0" << endl;
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

    void l_expr(node* n, ostream& os) {
        if (n->klass == "ID") {
            loadvariable(n->value, os);
            return;
        }
        if (n->klass == "NUM") {
            os << "li a0," << n->child[1]->value << endl;
            return;
        }
        if (n->klass == "CALC") {
            l_calc(n, os);
            return;
        }
        //ASSERT
    }

    void l_stam(node* n, ostream& os) {
        //uses t0
        l_expr(n->child[1], os);
        storevariable(n->child[0]->value, os);
    }

    void l_let(node* n, ostream& os) {
        l_expr(n->child[1], os);
        storevariable(n->value, os);
    }

    void label(node* n, ostream& os) {
        os << "label_" << n->value << ":" << endl;
    }

    void l_input(node* n, ostream& os) {
        for (auto i : n->child) {
            os << "input" << endl;
            storevariable(i->value, os);
        }
    }

    void l_if(node* n, ostream& os) {
        l_expr(n->child[0], os);
        os << "bne x0, a0, label_" << n->value << endl;
    }

    void l_for(node* n, ostream& os) {
        l_expr(n->child[1], os);
        os << "beq x0, a0, label_" << n->value << endl;
        l_stam(n->child[0], os);
    }

    void l_goto(node* n, ostream& os) {
        os << "j " << n->value << endl;
    }

    void loadvariable(string str, ostream& os) {
        os << "lw a0, gp, " << stoi(str.substr(3));
    }

    void storevariable(string str, ostream& os) {
        os << "sw a0, gp, " << stoi(str.substr(3));
    }

    void l_end(ostream& os) {
        os << "ret" << endl;
    }

    void l_exit(node* n, ostream& os) {
        if (n->child.empty()) {
            os << "mv a0, x0" << endl;
        } else {
            l_expr(n->child[0], os);
        }
        l_end(os);
    }

public:
    void translate(node* prgm, ostream& os) {
        start(os);
        for (auto i : prgm->child) {
            if (i->klass == "INPUT") {
                l_input(i, os);
            } else if (i->klass == "LINE") {
                label(i, os);
            } else if (i->klass == "LET") {
                l_let(i, os);
            } else if (i->klass == "EXIT") {
                l_exit(i, os);
            } else if (i->klass == "GOTO") {
                l_goto(i, os);
            } else if (i->klass == "IF") {
                l_if(i, os);
            } else if (i->klass == "FOR") {
                l_for(i, os);
            } else
                ; //ASSERT
        }
        os << "mv a0, x0" << endl;
        l_end(os);
    }
};
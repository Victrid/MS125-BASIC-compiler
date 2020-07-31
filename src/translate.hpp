#include "parser.hpp"
#include <stack>
#include <vector>
using namespace std;
class translator {
private:
    vector<string> forgroups;
    void start(ostream& os) {
        os << "label_init:" << endl
           << "lui sp, 256" << endl
           << "lui gp, 2048" << endl
           << "jal ra, label_main" << endl
           << "addi a0, zero, 255" << endl
           << "label_main:" << endl;
    }

    void l_calc(node* n, ostream& os) {
        //USES t0,t1,t2
        //answer stored to a0.
        if (n->child[0]->klass == "CALC") {
            l_calc(n->child[0], os);
            os << "addi sp, sp, 4" << endl;
            os << "sw a0, 0(sp) " << endl;
        } else if (n->child[0]->klass == "ID") {
            loadvariable(n->child[0]->value, os);
            os << "addi sp, sp, 4" << endl;
            os << "sw a0, 0(sp) " << endl;
        } else if (n->child[0]->klass == "NUM") {
            os << "addi t0, zero, " << n->child[0]->value << endl;
            os << "addi sp, sp, 4" << endl;
            os << "sw t0, 0(sp) " << endl;
        }
        if (n->child[1]->klass == "CALC") {
            l_calc(n->child[1], os);
            os << "add t1, a0, zero" << endl;
        } else if (n->child[1]->klass == "ID") {
            loadvariable(n->child[1]->value, os);
            os << "add t1, a0, zero" << endl;
        } else if (n->child[1]->klass == "NUM") {
            os << "addi t1, zero, " << n->child[1]->value << endl;
        }
        os << "lw t0, 0(sp) " << endl;
        os << "addi sp, sp, -4" << endl;
        if (n->value == "or") {
            os << "or a0, t0, t1" << endl;
        } else if (n->value == "and") {
            os << "and a0, t0, t1" << endl;
        } else if (n->value == "ne") {
            os << "sub a0, t0, t1" << endl;
            os << "sltu a0, zero, a0" << endl;
        } else if (n->value == "eq") {
            os << "sub a0, t0, t1" << endl;
            os << "sltu a0, zero, a0" << endl;
            os << "xori a0, a0, 1" << endl;
        } else if (n->value == "le") {
            os << "slt a0, t1, t0" << endl;
            os << "xori a0, a0, 1" << endl;
        } else if (n->value == "ge") {
            os << "slt a0, t0, t1" << endl;
            os << "xori a0, a0, 1" << endl;
        } else if (n->value == "g") {
            os << "slt a0, t1, t0" << endl;
        } else if (n->value == "l") {
            os << "slt a0, t0, t1" << endl;
        } else if (n->value == "min") {
            os << "sub a0, t0, t1" << endl;
        } else if (n->value == "add") {
            os << "add a0, t0, t1" << endl;
        } else if (n->value == "mul") {
            os << "mul a0, t0, t1" << endl;
        } else if (n->value == "div") {
            os << "div a0, t0, t1" << endl;
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
            os << "addi a0, zero, " << n->value << endl;
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
        l_expr(n->child[0], os);
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
        os << "bne zero, a0, label_" << n->value << endl;
    }

    void l_for(node* n, ostream& os) {
        l_expr(n->child[1], os);
        os << "beq zero, a0, label_" << n->value << endl;
        forgroups.push_back(n->attrib);
    }

    void l_goto(node* n, ostream& os) {
        os << "jal zero, label_" << n->value << endl;
    }

    void l_forend(node* n, ostream& os) {
        l_stam(n->child[0], os);
        os << "jal zero, "
           << "label_" << n->value << endl;
    }

    void loadvariable(string str, ostream& os) {
        os << "lw a0, " << stoi(str.substr(3)) * 4 << "(gp) " << endl;
    }

    void storevariable(string str, ostream& os) {
        os << "sw a0, " << stoi(str.substr(3)) * 4 << "(gp) " << endl;
    }

    void l_end(ostream& os) {
        os << "jalr zero, 0(ra)" << endl;
    }

    void l_exit(node* n, ostream& os) {
        if (n->child.empty()) {
            os << "add a0, zero, zero" << endl;
        } else {
            l_expr(n->child[0], os);
        }
        l_end(os);
    }

public:
    void translate(node* prgm, ostream& os) {
        start(os);
        for (auto i = prgm->child.begin(); i != prgm->child.end() - 1; i++) {
            if ((*(i + 1))->klass == "FOR") {
                int forg = 0;
                stack<std::vector<node*>::iterator> st;
                string andest;
                for (auto j = i + 2;; j++) {
                    if ((*j)->attrib == "dest" && (*j)->value == (*i)->value) {
                        st.push(j);
                    }
                    if ((*(j + 1))->klass == "FOREND" && (*(j + 1))->value == (*i)->value) {
                        andest = (*j)->value;
                        break;
                    }
                }
                while (!st.empty()) {
                    (*st.top())->value = andest;
                    st.pop();
                }
            }
        }
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
            } else if (i->klass == "FOREND") {
                l_forend(i, os);
            }; //ASSERT
        }
        os << "add a0, zero, zero" << endl;
        l_end(os);
    }
};
// generate symbol table, jump table.

#include "ordos.hpp"

using namespace std;

void symbol_assert(bool b, std::string str) {
    if (!b)
        throw logic_error("Symbol not defined: " + str);
}

void cfgize_labelproc(istream& is, ostream& os) {
    //remove unused linenumber and rem lines.
    node n = buildtree(is);
    stack<node*> pstack;
    set<int> labelset;
    pstack.push(&n);
    while (!pstack.empty()) {
        node* rt = pstack.top();
        pstack.pop();
        if (rt->hasattrib && rt->attrib == "dest") {
            labelset.insert(stoi(rt->value));
        }
        if (!(rt->child.empty())) {
            for (auto i = rt->child.begin(); i != rt->child.end(); i++) {
                pstack.push(*i);
            }
        }
    }
    auto it = n.child.begin();
    while (it != n.child.end()) {
        if ((*it)->klass == "LINE" && labelset.find(stoi((*it)->value)) == labelset.end() && (it + 1 == n.child.end() || (*(it + 1))->klass != "FOR"))
            it = n.child.erase(it);
        else
            ++it;
    }
    it = n.child.begin();
    while (it != n.child.end()) {
        if ((*it)->klass == "REM")
            it = n.child.erase(it);
        else
            ++it;
    }
    os << n;
    return;
}

void cfgize_symbolproc(istream& is, ostream& os) {
    //check symbols
    node n = buildtree(is);
    map<string, int> symboltable;
    int symnum = 0;
    for (auto i = n.child.begin(); i != n.child.end(); i++) {
        if ((*i)->klass == "LET") {
            if (symboltable.find((*i)->value) == symboltable.end()) {
                symboltable.insert(pair<string, int>((*i)->value, symnum));
                symnum++;
            }
        }
        if ((*i)->klass == "INPUT") {
            for (auto j = (*i)->child.begin(); j != (*i)->child.end(); j++) {
                if (symboltable.find((*j)->value) == symboltable.end()) {
                    symboltable.insert(pair<string, int>((*j)->value, symnum));
                    symnum++;
                }
                (*j)->value = "sym" + to_string(symboltable[(*j)->value]);
            }
        }
    }
    stack<node*> pstack;
    pstack.push(&n);
    while (!pstack.empty()) {
        node* rt = pstack.top();
        pstack.pop();
        if (rt->klass == "INPUT")
            continue;
        if (rt->hasattrib && rt->attrib == "id") {
            symbol_assert(symboltable.find(rt->value) != symboltable.end(), rt->value);
            rt->value = "sym" + to_string(symboltable[rt->value]);
        }
        if (!(rt->child.empty())) {
            for (auto i = rt->child.begin(); i != rt->child.end(); i++) {
                pstack.push(*i);
            }
        }
    }
    os << n;
    return;
}

void forclosure(istream& is, ostream& os) {
    //check symbols
    node n = buildtree(is);
    stack<string> fortagstack;
    for (auto i = n.child.begin(); i != n.child.end(); i++) {
        if ((*i)->klass == "FOR") {
            fortagstack.push((*(i - 1))->value);
        }
        if ((*i)->klass == "EF") {
            string addr = fortagstack.top();
            fortagstack.pop();
            (*i)->klass     = "GOTO";
            (*i)->hasattrib = true;
            (*i)->attrib    = "dest";
            (*i)->value     = addr;
        }
    }
    symbol_assert(fortagstack.empty(),"For tag unclosed.");
    os << n;
    return;
}
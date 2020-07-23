#include "ordos.hpp"

using namespace std;

void order_assert(bool b) {
    if (!b)
        throw logic_error("Order Error.");
}

void orderselect(node* n) {
    for (auto j = n->child.begin(); j != n->child.end(); j++) {
        if ((*j)->klass == "EXPR")
            orderselect(*j);
    }
    for (auto j = n->child.end(); j != n->child.begin();) {
        j--;
        if ((*j)->klass == "SYM" && (*j)->value == "or") {
            node* nleft   = new node();
            nleft->klass  = "EXPR";
            node* nright  = new node();
            nright->klass = "EXPR";
            for (auto p = n->child.begin(); p != j; p++)
                nleft->addchild(*p);
            for (auto p = j + 1; p != n->child.end(); p++)
                nright->addchild(*p);
            orderselect(nleft);
            orderselect(nright);
            n->klass     = "CALC";
            n->hasattrib = true;
            n->attrib    = "type";
            n->value     = (*j)->value;
            n->child.clear();
            n->child.push_back(nleft);
            n->child.push_back(nright);
            return;
        }
    }
    for (auto j = n->child.end(); j != n->child.begin();) {
        j--;
        if ((*j)->klass == "SYM" && (*j)->value == "and") {
            node* nleft   = new node();
            nleft->klass  = "EXPR";
            node* nright  = new node();
            nright->klass = "EXPR";
            for (auto p = n->child.begin(); p != j; p++)
                nleft->addchild(*p);
            for (auto p = j + 1; p != n->child.end(); p++)
                nright->addchild(*p);
            orderselect(nleft);
            orderselect(nright);
            n->klass     = "CALC";
            n->hasattrib = true;
            n->attrib    = "type";
            n->value     = (*j)->value;
            n->child.clear();
            n->child.push_back(nleft);
            n->child.push_back(nright);
            return;
        }
    }
    for (auto j = n->child.end(); j != n->child.begin();) {
        j--;
        if ((*j)->klass == "SYM" && ((*j)->value == "eq" || (*j)->value == "ne")) {
            node* nleft   = new node();
            nleft->klass  = "EXPR";
            node* nright  = new node();
            nright->klass = "EXPR";
            for (auto p = n->child.begin(); p != j; p++)
                nleft->addchild(*p);
            for (auto p = j + 1; p != n->child.end(); p++)
                nright->addchild(*p);
            orderselect(nleft);
            orderselect(nright);
            n->klass     = "CALC";
            n->hasattrib = true;
            n->attrib    = "type";
            n->value     = (*j)->value;
            n->child.clear();
            n->child.push_back(nleft);
            n->child.push_back(nright);
            return;
        }
    }
    for (auto j = n->child.end(); j != n->child.begin();) {
        j--;
        if ((*j)->klass == "SYM" && ((*j)->value == "g" || (*j)->value == "l" || (*j)->value == "ge" || (*j)->value == "le")) {
            node* nleft   = new node();
            nleft->klass  = "EXPR";
            node* nright  = new node();
            nright->klass = "EXPR";
            for (auto p = n->child.begin(); p != j; p++)
                nleft->addchild(*p);
            for (auto p = j + 1; p != n->child.end(); p++)
                nright->addchild(*p);
            orderselect(nleft);
            orderselect(nright);
            n->klass     = "CALC";
            n->hasattrib = true;
            n->attrib    = "type";
            n->value     = (*j)->value;
            n->child.clear();
            n->child.push_back(nleft);
            n->child.push_back(nright);
            return;
        }
    }
    for (auto j = n->child.end(); j != n->child.begin();) {
        j--;
        if ((*j)->klass == "SYM" && (j != n->child.begin()) && ((*j)->value == "add" || (*j)->value == "min")) {
            node* nleft   = new node();
            nleft->klass  = "EXPR";
            node* nright  = new node();
            nright->klass = "EXPR";
            for (auto p = n->child.begin(); p != j; p++)
                nleft->addchild(*p);
            for (auto p = j + 1; p != n->child.end(); p++)
                nright->addchild(*p);
            orderselect(nleft);
            orderselect(nright);
            n->klass     = "CALC";
            n->hasattrib = true;
            n->attrib    = "type";
            n->value     = (*j)->value;
            n->child.clear();
            n->child.push_back(nleft);
            n->child.push_back(nright);
            return;
        }
    }
    for (auto j = n->child.end(); j != n->child.begin();) {
        j--;
        if ((*j)->klass == "SYM" && (j != n->child.begin()) && ((*j)->value == "mul" || (*j)->value == "div")) {
            node* nleft   = new node();
            nleft->klass  = "EXPR";
            node* nright  = new node();
            nright->klass = "EXPR";
            for (auto p = n->child.begin(); p != j; p++)
                nleft->addchild(*p);
            for (auto p = j + 1; p != n->child.end(); p++)
                nright->addchild(*p);
            orderselect(nleft);
            orderselect(nright);
            n->klass     = "CALC";
            n->hasattrib = true;
            n->attrib    = "type";
            n->value     = (*j)->value;
            n->child.clear();
            n->child.push_back(nleft);
            n->child.push_back(nright);
            return;
        }
    }
    for (auto j = n->child.begin(); j != n->child.end(); j++) {
        if ((*j)->klass == "SYM" && (j == n->child.begin()) && ((*j)->value == "add" || (*j)->value == "min")) {
            node* nleft      = new node();
            nleft->klass     = "NUM";
            nleft->hasattrib = true;
            nleft->attrib    = "number";
            nleft->value     = "0";
            node* nright     = new node();
            nright->klass    = "EXPR";
            for (auto p = j + 1; p != n->child.end(); p++)
                nright->addchild(*p);
            orderselect(nright);
            n->klass     = "CALC";
            n->hasattrib = true;
            n->attrib    = "type";
            n->value     = (*j)->value;
            n->child.clear();
            n->child.push_back(nleft);
            n->child.push_back(nright);
            return;
        }
    }
    order_assert(n->child.size() == 1);
    order_assert(!(n->child[0]->klass == "SYM"));
    (*n) = *(n->child[0]);
    return;
}

void orderconstruct(node* n) {
    {
        auto p = n->selectsonbyclass("IF");
        for (auto m : p) {
            auto j = m->selectsonbyclass("EXPR");
            for (auto i : j) {
                orderselect(i);
            }
        }
    }
    {
        auto p = n->selectsonbyclass("FOR");
        for (auto m : p) {
            auto j = m->selectsonbyclass("EXPR");
            for (auto i : j) {
                orderselect(i);
            }
        }
    }
    {
        auto p = n->selectsonbyclass("FOR");
        for (auto m : p) {
            auto q = m->selectsonbyclass("STAM");
            for (auto s : q) {
                auto j = s->selectsonbyclass("EXPR");
                for (auto i : j) {
                    orderselect(i);
                }
            }
        }
    }
    {
        auto p = n->selectsonbyclass("LET");
        for (auto m : p) {
            auto j = m->selectsonbyclass("EXPR");
            for (auto i : j) {
                orderselect(i);
            }
        }
    }
    {
        auto p = n->selectsonbyclass("EXIT");
        for (auto m : p) {
            auto j = m->selectsonbyclass("EXPR");
            for (auto i : j) {
                orderselect(i);
            }
        }
    }
    return;
}
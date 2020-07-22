#include "parser.hpp"

using namespace std;

void parsing_assert(bool b, std::string str) {
    if (!b)
        throw std::logic_error("Parse Error: " + str);
}

bool node::isleaf() { return leaf; }

void node::addchild(node* n) {
    leaf = false;
    child.push_back(n);
}

void node::fill_attrib(const string& str) {
    smatch res;
    if (regex_match(str, res, regex("<(.+)\\s+(.+)=\"(.+)\"/?>"))) {
        klass  = res[1].str();
        attrib = res[2].str();
        value  = res[3].str();
    } else if (regex_match(str, res, regex("<(.+?)/?>")))
        klass = res[1].str();
    else
        parsing_assert(false, str);
};

bool node::validate_tag_closure(string str) { return true; } //TODO

node& node::selectbynum(int n) { return *child[n]; }

node::node(string& str) {
    smatch res, rres;
    if (regex_match(str, res, regex("\\s*(<.+?>)\\s*(.+)\\s*$"))) {
        string fr = res[1].str();
        fill_attrib(fr);
        if (!regex_match(fr, regex("\\s*<.+?/>\\s*$"))) {
            // if not an empty tag:
            str = res[2].str();
            while (!regex_match(str, regex("\\s*</" + klass + ">.*$")))
                //while not an closing tag:
                addchild(new node(str));
            //then get the tag closed.
            parsing_assert(regex_match(str, res, regex("\\s*(</.+?>)\\s*(.+)\\s*$")), str);
            parsing_assert(validate_tag_closure(res[1].str()), str);
            str = res[2].str();
        } else
            str = res[2].str();
    }
}

node buildtree(istream& is) {
    ostringstream ost;
    ost << is.rdbuf();
    string str = ost.str();
    return node(str);
}
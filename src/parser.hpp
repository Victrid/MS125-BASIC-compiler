#ifndef _parser_
#define _parser_

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

void parsing_assert(bool b, std::string str);

class node {
private:
    bool leaf      = true;
    bool hasattrib = false;

    std::vector<node*> child;
    std::string klass;
    std::string attrib;
    std::string value;

protected:
    void fill_attrib(const std::string& str);
    bool validate_tag_closure(std::string str);

public:
    bool isleaf();
    void addchild(node* n);

    node& selectbynum(int n);
    std::vector<node*> selectsonbyclass(std::string& classname);

    node(std::string& str);
};

node buildtree(std::istream& is);

#endif
#ifndef _parser_
#define _parser_

//This parser is for parsing between tree stucture and file in markup language.

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
    friend std::ostream& operator<<(std::ostream& os, const node& obj);
    friend void orderselect(node* n);
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
    bool isleaf() const;
    void addchild(node* n);
    void changechild(node* origin, node* newchild);

    node& selectbynum(int n);
    std::vector<node*> selectsonbyclass(std::string classname);

    node(std::string& str);
    node() {}
};

node buildtree(std::istream& is);

#endif
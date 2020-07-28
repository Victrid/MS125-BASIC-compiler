#ifndef _ordos_
#define _ordos_

#include "parser.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

void order_assert(bool b);
void symbol_assert(bool b, std::string str);

void orderselect(node* n);
void orderconstruct(node* n);

void cfgize_labelproc(std::istream& is, std::ostream& os);
void cfgize_symbolproc(std::istream& is, std::ostream& os);

#endif
#ifndef _ordos_
#define _ordos_

#include "parser.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

void order_assert(bool b);

void orderselect(node* n);
void orderconstruct(node* n);

#endif
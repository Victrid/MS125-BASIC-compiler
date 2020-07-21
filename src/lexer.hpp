#ifndef _lexer_
#define _lexer_

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

void assert(bool b, std::string str);

void exprproc(std::string str, std::ostream& os);
void statementproc(std::string str, std::ostream& os);
void idlistproc(std::string str, std::ostream& os);
void commandproc(std::string str, std::ostream& os);

void lineproc(std::istream& is, std::ostream& os);

#endif
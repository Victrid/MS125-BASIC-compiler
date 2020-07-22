#ifndef _lexer_
#define _lexer_

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

void lingual_assert(bool b, std::string str);

void lex_expression(std::string str, std::ostream& os);
void lex_statement(std::string str, std::ostream& os);
void lex_parentheses(std::istream& is, std::ostream& os);
void lex_idlist(std::string str, std::ostream& os);
void lex_commands(std::string str, std::ostream& os);

void lex_inputline(std::istream& is, std::ostream& os);

#endif
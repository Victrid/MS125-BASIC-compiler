#include "lexer.hpp"

using namespace std;

static const string vv[]   = {"||", "&&", "==", "!=", "<=", ">=", "<", ">", "-", "+", "/", "*"};
static const string cont[] = {"or", "and", "eq", "ne", "le", "ge", "l", "g", "min", "add", "div", "mul"};

void assert(bool b, string str) {
    if (!b)
        throw logic_error("Parse Error: " + str);
}

void exprproc(string str, ostream& os) {
    smatch res;
    if (regex_match(str, res, regex("\\s*(\\|\\||&&|==|!=|<=|>=)\\s*(.*)\\s*$"))) {
        for (int i = 0; i <= 12; i++) {
            assert(i != 12, str);
            if (vv[i] == res[1].str()) {
                os << "<SYM symnum=\"" << cont[i] << "\"/> ";
                break;
            }
        }
        exprproc(res[2].str(), os);
        return;
    }
    if (regex_match(str, res, regex("\\s*(<|>|-|\\+|/|\\*)\\s*(.*)\\s*$"))) {
        for (int i = 0; i <= 12; i++) {
            assert(i != 12, str);
            if (vv[i] == res[1].str()) {
                os << "<SYM symnum=\"" << cont[i] << "\"/> ";
                break;
            }
        }
        exprproc(res[2].str(), os);
        return;
    }
    if (regex_match(str, res, regex("\\s*\\(\\s*(.*)\\s*$"))) {
        os << "(";
        exprproc(res[1].str(), os);
        return;
    }
    if (regex_match(str, res, regex("\\s*\\)\\s*(.*)\\s*$"))) {
        os << ")";
        exprproc(res[1].str(), os);
        return;
    }
    if (regex_match(str, res, regex("\\s*([0-9]+)\\s*(.*)\\s*$"))) {
        os << "<NUM number=\"" << res[1] << "\"/> ";
        exprproc(res[2].str(), os);
        return;
    }
    if (regex_match(str, res, regex("\\s*([a-zA-Z]+)\\s*(.*)\\s*$"))) {
        os << "<ID id=\"" << res[1] << "\"/> ";
        exprproc(res[2].str(), os);
        return;
    }
    if (regex_match(str, res, regex("\\s*$"))) {
        return;
    }
    assert(false, str);
    return;
}

void parenthesesproc(istream& is, ostream& os) {
    stack<string> stq;
    smatch res;
    string str;
    int stage = 0;
    ostringstream ost;
    ost << is.rdbuf();
    str = ost.str();
    while (regex_match(str, res, regex("(.*)\\(([^\\(\\)]*)\\)(.*)$"))) {
        stq.push(res[2].str());
        str = regex_replace(str, regex("(.*)(\\([^\\(\\)]*\\))(.*)$"), "$1<mstr num=" + to_string(stage) + "/>$3");
        stage++;
    }
    while (stage) {
        stage--;
        str = regex_replace(str, regex("(.*)(<mstr num=" + to_string(stage) + "/>)(.*)$"), "$1 <EXPR> " + stq.top() + " </EXPR> $3");
        stq.pop();
    }
    os << str;
    return;
}

void statementproc(string str, ostream& os) {
    smatch res;
    if (regex_match(str, res, regex("\\s*([a-zA-Z]+)\\s*=\\s*(.+)\\s*$"))) {
        os << "<ID id=\"" << res[1] << "\"/> ";
        os << "<EXPR> ";
        stringstream strr;
        exprproc(res[2].str(), strr);
        parenthesesproc(strr, os);
        os << "</EXPR> ";
        return;
    }
    assert(false, str);
}

void idlistproc(string str, ostream& os) {
    smatch res;
    if (regex_match(str, res, regex("\\s*([a-zA-Z]+)\\s*,\\s*(.+)\\s*$"))) {
        os << "<ID id=\"" << res[1] << "\"/> ";
        idlistproc(res[2].str(), os);
        return;
    }
    if (regex_match(str, res, regex("\\s*([a-zA-Z]+)\\s*$"))) {
        os << "<ID id=\"" << res[1] << "\"/> ";
        return;
    }
    assert(false, str);
}

void commandproc(string str, ostream& os) {
    string tomatch[] = {
        "REM.*$",
        "LET\\s+([a-zA-Z]*)\\s*=\\s*(.+)\\s*$",
        "INPUT\\s(.+)\\s*$",
        "EXIT\\s+(.+)\\s*$",
        "GOTO\\s+([0-9]+)\\s*$",
        "IF\\s+(.+)\\s+THEN\\s+([0-9]+)\\s*$",
        "FOR\\s+(.+)\\s*;\\s*(.+)\\s*$",
        "END\\s+FOR\\s*$",
        "\\s*([a-zA-Z]*)\\s*=\\s*(.+)\\s*$"};
    smatch res;
    if (regex_match(str, res, regex(tomatch[0]))) {
        os << "<REM/> ";
        return;
    }
    if (regex_match(str, res, regex(tomatch[1]))) {
        os << "<LET id=\"" << res[1].str() << "\"> ";
        os << "<EXPR> ";
        stringstream strr;
        exprproc(res[2].str(), strr);
        parenthesesproc(strr, os);
        os << "</EXPR> ";
        os << "</LET> ";
        return;
    }
    if (regex_match(str, res, regex(tomatch[2]))) {
        os << "<INPUT> ";
        idlistproc(res[1].str(), os);
        os << "</INPUT> ";
        return;
    }
    if (regex_match(str, res, regex(tomatch[3]))) {
        os << "<EXIT> ";
        os << "<EXPR> ";
        stringstream strr;
        exprproc(res[1].str(), strr);
        parenthesesproc(strr, os);
        os << "</EXPR> ";
        os << "</EXIT> ";
        return;
    }
    if (regex_match(str, res, regex(tomatch[4]))) {
        os << "<GOTO dest=\"" << res[1] << "\"/> ";
        return;
    }
    if (regex_match(str, res, regex(tomatch[5]))) {
        os << "<IF dest=\"" << res[2] << "\"> ";
        os << "<EXPR> ";
        stringstream strr;
        exprproc(res[1].str(), strr);
        parenthesesproc(strr, os);
        os << "</EXPR> ";
        os << "</IF> ";
        return;
    }
    if (regex_match(str, res, regex(tomatch[6]))) {
        os << "<FOR> ";
        os << "<STAM>";
        statementproc(res[1].str(), os);
        os << "</STAM>";
        os << "<EXPR> ";
        stringstream strr;
        exprproc(res[2].str(), strr);
        parenthesesproc(strr, os);
        os << "</EXPR> ";
        os << "</FOR> ";
        return;
    }
    if (regex_match(str, res, regex(tomatch[7]))) {
        os << "<EF/> ";
        return;
    }
    if (regex_match(str, res, regex(tomatch[8]))) {
        os << "<SET id=\"" << res[1].str() << "\"> ";
        os << "<EXPR> ";
        stringstream strr;
        exprproc(res[2].str(), strr);
        parenthesesproc(strr, os);
        os << "</EXPR> ";
        os << "</SET> ";
        return;
    }
    assert(false, str);
    return;
}

void lineproc(istream& is, ostream& os) {
    string str;
    smatch res;
    os << "<PRGM> ";
    while (getline(is, str)) {
        assert(regex_match(str, res, regex("\\s*([0-9]+)\\s+(.*)$")), str);
        os << "<LINE linenum=\"" << res[1] << "\"/> ";
        commandproc(res[2].str(), os);
    }
    os << "</PRGM> ";
}
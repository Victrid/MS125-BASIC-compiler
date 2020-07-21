#include "lexer.hpp"

void assert(bool b, std::string str) {
    if (!b)
        throw std::logic_error("Parse Error: " + str);
}

void exprproc(std::string str, std::ostream& os) {
    std::smatch res;
    if (std::regex_match(str, res, std::regex("\\s*(\\|\\||&&|==|!=|<=|>=)\\s*(.*)\\s*$"))) {
        os << "<SYM symnum=\"" << res[1].str() << "\"/> ";
        exprproc(res[2].str(), os);
        return;
    }
    if (std::regex_match(str, res, std::regex("\\s*(<|>|-|\\+|/|\\*)\\s*(.*)\\s*$"))) {
        os << "<SYM symnum=\"" << res[1].str() << "\"/> ";
        exprproc(res[2].str(), os);
        return;
    }
    if (std::regex_match(str, res, std::regex("\\s*\\(\\s*(.*)\\s*$"))) {
        os << "(";
        exprproc(res[1].str(), os);
        return;
    }
    if (std::regex_match(str, res, std::regex("\\s*\\)\\s*(.*)\\s*$"))) {
        os << ")";
        exprproc(res[1].str(), os);
        return;
    }
    if (std::regex_match(str, res, std::regex("\\s*([0-9]+)\\s*(.*)\\s*$"))) {
        os << "<NUM number=\"" << res[1] << "\"/> ";
        exprproc(res[2].str(), os);
        return;
    }
    if (std::regex_match(str, res, std::regex("\\s*([a-zA-Z]+)\\s*(.*)\\s*$"))) {
        os << "<ID id=\"" << res[1] << "\"/> ";
        exprproc(res[2].str(), os);
        return;
    }
    if (std::regex_match(str, res, std::regex("\\s*$"))) {
        return;
    }
    assert(false, str);
    return;
}

void parenthesesproc(std::istream& is, std::ostream& os) {
    std::stack<std::string> stq;
    std::smatch res;
    std::string str;
    int stage = 0;
    std::ostringstream ost;
    ost << is.rdbuf();
    str = ost.str();
    while (std::regex_match(str, res, std::regex("(.*)\\(([^\\(\\)]*)\\)(.*)$"))) {
        stq.push(res[2].str());
        str = std::regex_replace(str, std::regex("(.*)(\\([^\\(\\)]*\\))(.*)$"), "$1<mstr num=" + std::to_string(stage) + "/>$3");
        stage++;
    }
    while (stage) {
        stage--;
        str = std::regex_replace(str, std::regex("(.*)(<mstr num=" + std::to_string(stage) + "/>)(.*)$"), "$1 <EXPR> " + stq.top() + " </EXPR> $3");
        stq.pop();
    }
    os << str;
    return;
}

void statementproc(std::string str, std::ostream& os) {
    std::smatch res;
    if (std::regex_match(str, res, std::regex("\\s*([a-zA-Z]+)\\s*=\\s*(.+)\\s*$"))) {
        os << "<ID id=\"" << res[1] << "\"/> ";
        os << "<EXPR> ";
        std::stringstream strr;
        exprproc(res[2].str(), strr);
        parenthesesproc(strr, os);
        os << "</EXPR> ";
        return;
    }
    assert(false, str);
}

void idlistproc(std::string str, std::ostream& os) {
    std::smatch res;
    if (std::regex_match(str, res, std::regex("\\s*([a-zA-Z]+)\\s*,\\s*(.+)\\s*$"))) {
        os << "<ID id=\"" << res[1] << "\"/> ";
        idlistproc(res[2].str(), os);
        return;
    }
    if (std::regex_match(str, res, std::regex("\\s*([a-zA-Z]+)\\s*$"))) {
        os << "<ID id=\"" << res[1] << "\"/> ";
        return;
    }
    assert(false, str);
}

void commandproc(std::string str, std::ostream& os) {
    std::string tomatch[] = {
        "REM.*$",
        "LET\\s+([a-zA-Z]*)\\s*=\\s*(.+)\\s*$",
        "INPUT\\s(.+)\\s*$",
        "EXIT\\s+(.+)\\s*$",
        "GOTO\\s+([0-9]+)\\s*$",
        "IF\\s+(.+)\\s+THEN\\s+([0-9]+)\\s*$",
        "FOR\\s+(.+)\\s*;\\s*(.+)\\s*$",
        "END\\s+FOR\\s*$",
        "\\s*([a-zA-Z]*)\\s*=\\s*(.+)\\s*$"};
    std::smatch res;
    if (std::regex_match(str, res, std::regex(tomatch[0]))) {
        os << "<REM/> ";
        return;
    }
    if (std::regex_match(str, res, std::regex(tomatch[1]))) {
        os << "<LET id=\"" << res[1].str() << "\"> ";
        os << "<EXPR> ";
        std::stringstream strr;
        exprproc(res[2].str(), strr);
        parenthesesproc(strr, os);
        os << "</EXPR> ";
        os << "</LET> ";
        return;
    }
    if (std::regex_match(str, res, std::regex(tomatch[2]))) {
        os << "<INPUT> ";
        idlistproc(res[1].str(), os);
        os << "</INPUT> ";
        return;
    }
    if (std::regex_match(str, res, std::regex(tomatch[3]))) {
        os << "<EXIT> ";
        os << "<EXPR> ";
        std::stringstream strr;
        exprproc(res[1].str(), strr);
        parenthesesproc(strr, os);
        os << "</EXPR> ";
        os << "</EXIT> ";
        return;
    }
    if (std::regex_match(str, res, std::regex(tomatch[4]))) {
        os << "<GOTO dest=\"" << res[1] << "\"/> ";
        return;
    }
    if (std::regex_match(str, res, std::regex(tomatch[5]))) {
        os << "<IF dest=\"" << res[2] << "\"> ";
        os << "<EXPR> ";
        std::stringstream strr;
        exprproc(res[1].str(), strr);
        parenthesesproc(strr, os);
        os << "</EXPR> ";
        os << "</IF> ";
        return;
    }
    if (std::regex_match(str, res, std::regex(tomatch[6]))) {
        os << "<FOR> ";
        os << "<STAM>";
        statementproc(res[1].str(), os);
        os << "</STAM>";
        os << "<EXPR> ";
        std::stringstream strr;
        exprproc(res[2].str(), strr);
        parenthesesproc(strr, os);
        os << "</EXPR> ";
        os << "</FOR> ";
        return;
    }
    if (std::regex_match(str, res, std::regex(tomatch[7]))) {
        os << "<EF/> ";
        return;
    }
    if (std::regex_match(str, res, std::regex(tomatch[8]))) {
        os << "<SET id=\"" << res[1].str() << "\"> ";
        os << "<EXPR> ";
        std::stringstream strr;
        exprproc(res[2].str(), strr);
        parenthesesproc(strr, os);
        os << "</EXPR> ";
        os << "</SET> ";
        return;
    }
    assert(false, str);
    return;
}

void lineproc(std::istream& is, std::ostream& os) {
    std::string str;
    std::smatch res;
    os << "<PRGM> ";
    while (getline(is, str)) {
        assert(std::regex_match(str, res, std::regex("\\s*([0-9]+)\\s+(.*)$")), str);
        os << "<LINE linenum=\"" << res[1] << "\"/> ";
        commandproc(res[2].str(), os);
    }
    os << "</PRGM> ";
}
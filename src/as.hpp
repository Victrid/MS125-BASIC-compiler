#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

using namespace std;

const string tomatch[] = {
    "(.+)\\s(.+),\\s(.+)\\((.+)\\)\\s*$",
    "(.+)\\s(.+),\\s(.+),\\s(.+)$",
    "(.+)\\s(.+),\\s(.+)$",
    "input"};

const string threeops[] = {
    "addi", "xori", "beq", "bne", "add", "sub", "mul", "div", "slt", "sltu", "and", "or"};

const string twoops[] = {
    "jal", "lui"};

const string parops[] = {
    "lw", "sw", "jalr"};

const string regist[] = {
    "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

const string R[]{
    "add", "sub", "mul", "div", "sll", "slt", "sltu", "xor", "srl", "sra", "or", "and"};
const unsigned int Ri[]{
    0b00000000000000000000000000110011,
    0b01000000000000000000000000110011,
    0b00000010000000000000000000110011,
    0b00000010000000000100000000110011,
    0b00000000000000000001000000110011,
    0b00000000000000000010000000110011,
    0b00000000000000000011000000110011,
    0b00000000000000000100000000110011,
    0b00000000000000000101000000110011,
    0b01000000000000000101000000110011,
    0b00000000000000000110000000110011,
    0b00000000000000000111000000110011,
};
void parse_assert(bool b, string str) {
    if (!b)
        throw logic_error("ASM Parse Error: " + str);
}

unsigned int getdigits(unsigned int content, int l, int r) {
    if (r == 31)
        return content >> (l + 1);
    return (content - (content >> (r + 1) << (r + 1))) >> (l + 1);
};

unsigned int I_cons(string str1, string str2, string str3, int num) {
    unsigned int ret = 0, rd, rs1;
    for (int i = 0; i <= 32; i++) {
        if (i == 32)
            ; //assert;
        if (regist[i] == str2) {
            rd = i;
            break;
        }
    }
    for (int i = 0; i <= 32; i++) {
        if (i == 32)
            ; //assert;
        if (regist[i] == str3) {
            rs1 = i;
            break;
        }
    }
    if (str1 == "addi") {
        unsigned int imm = (unsigned int)num;
        if (num < 0)
            imm |= 0b100000000000;
        ret = 0b0010011 | rd << 7 | rs1 << 15 | imm << 20;
    } else if (str1 == "xori") {
        unsigned int imm = (unsigned int)num;
        if (num < 0)
            imm |= 0b100000000000;
        ret = 0b0010011 | rd << 7 | 0b100 << 12 | rs1 << 15 | imm << 20;
    } else if (str1 == "jalr") {
        num /= 2;
        unsigned int imm = (unsigned int)num;
        if (num < 0)
            imm |= 0b100000000000;
        ret = 0b1100111 | rd << 7 | rs1 << 15 | imm << 20;
    } else { //ASSERT
    }
    return ret;
}

unsigned int B_cons(string str1, string str2, string str3, int num) {
    unsigned int ret = 0, rs1 = 0, rs2 = 0;
    for (int i = 0; i <= 32; i++) {
        if (i == 32)
            ; //assert;
        if (regist[i] == str2) {
            rs1 = i;
            break;
        }
    }
    for (int i = 0; i <= 32; i++) {
        if (i == 32)
            ; //assert;
        if (regist[i] == str3) {
            rs2 = i;
            break;
        }
    }
    unsigned int imm = (unsigned int)num;
    if (num < 0)
        imm |= 0b1000000000000;
    unsigned int pimm = (getdigits(imm, 10, 11) << 7) | (getdigits(imm, 0, 4) << 8) | (getdigits(imm, 4, 10) << 25) | (getdigits(imm, 11, 12) << 31);
    ret               = pimm | 0b1100011 | rs2 << 20 | rs1 << 15;
    if (str1 == "bne")
        ret |= 0b001 << 12;
    return ret;
}

unsigned int R_cons(string str1, string str2, string str3, string str4) {
    unsigned int ret = 0, rd, rs1, rs2;
    for (int i = 0; i <= 32; i++) {
        if (i == 32)
            ; //assert;
        if (regist[i] == str2) {
            rd = i;
            break;
        }
    }
    for (int i = 0; i <= 32; i++) {
        if (i == 32)
            ; //assert;
        if (regist[i] == str3) {
            rs1 = i;
            break;
        }
    }
    for (int i = 0; i <= 32; i++) {
        if (i == 32)
            ; //assert;
        if (regist[i] == str4) {
            rs2 = i;
            break;
        }
    }
    for (int i = 0; i <= 12; i++) {
        if (i == 12)
            ; //assert
        if (R[i] == str1)
            ret = Ri[i];
    }
    ret = ret | rd << 7 | rs1 << 15 | rs2 << 20;
    return ret;
}

unsigned int SL_cons(string str1, string str2, string str3, int num) {
    if (str1 == "sw") {
        unsigned int ret = 0b00000000000000000010000000100011, rs1, rs2;
        for (int i = 0; i <= 32; i++) {
            if (i == 32)
                ; //assert;
            if (regist[i] == str2) {
                rs2 = i;
                break;
            }
        }
        for (int i = 0; i <= 32; i++) {
            if (i == 32)
                ; //assert;
            if (regist[i] == str3) {
                rs1 = i;
                break;
            }
        }
        unsigned int imm = (unsigned int)num;
        if (num < 0)
            imm |= 0b100000000000;
        ret = ret | getdigits(imm, -1, 4) << 7 | getdigits(imm, 4, 11) << 25 | rs2 << 20 | rs1 << 15;
        return ret;
    } else {
        unsigned int ret = 0b00000000000000000010000000000011, rd, rs1;
        for (int i = 0; i <= 32; i++) {
            if (i == 32)
                ; //assert;
            if (regist[i] == str2) {
                rd = i;
                break;
            }
        }
        for (int i = 0; i <= 32; i++) {
            if (i == 32)
                ; //assert;
            if (regist[i] == str3) {
                rs1 = i;
                break;
            }
        }
        unsigned int imm = (unsigned int)num;
        if (num < 0)
            imm |= 0b100000000000;
        ret = ret | rd << 7 | rs1 << 15 | imm << 20;
        return ret;
    }
}

unsigned int U_J_cons(string str1, string str2, int num) {
    unsigned int ret = 0, rd;
    for (int i = 0; i <= 32; i++) {
        if (i == 32)
            ; //assert;
        if (regist[i] == str2) {
            rd = i;
            break;
        }
    }
    if (str1 == "lui") {
        unsigned int imm = (unsigned int)num;
        ret              = 0b0110111 | rd << 7 | imm << 12;
    } else {
        unsigned int imm = (unsigned int)num;
        if (num < 0)
            imm |= 0b100000000000000000000;
        unsigned int padimm = getdigits(imm, 11, 19) | (getdigits(imm, 10, 11) << 8) | (getdigits(imm, 0, 10) << 9) | (getdigits(imm, 19, 20) << 19);
        ret                 = 0b1101111 | rd << 7 | padimm << 12;
    }
    return ret;
}

void printinstr(unsigned int ui, ostream& os) {
    std::stringstream stream;
    stream << setfill('0') << setw(8) << right << std::hex << ui;
    std::string result(stream.str());
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    result = regex_replace(result, regex("(..)(..)(..)(..)"), "$4 $3 $2 $1 ");
    os << result << endl;
}

void parse_commands(string str, ostream& os) {

    smatch res;
    if (regex_match(str, res, regex(tomatch[0]))) {
        for (int i = 0; i < 2; i++) {
            if (res[1].str() == parops[i]) {
                unsigned int instr = SL_cons(res[1].str(), res[2].str(), res[4].str(), stoi(res[3].str()));
                printinstr(instr, os);
            }
        }
        if (res[1].str() == parops[2]) {
            unsigned int instr = I_cons(res[1].str(), res[2].str(), res[4].str(), stoi(res[3].str()));
            printinstr(instr, os);
        }
        //assert
        os.flush();
        return;
    }
    if (regex_match(str, res, regex(tomatch[1]))) {
        for (int i = 0; i < 2; i++) {
            if (res[1].str() == threeops[i]) {
                unsigned int instr = I_cons(res[1].str(), res[2].str(), res[3].str(), stoi(res[4].str()));
                printinstr(instr, os);
            }
        }
        for (int i = 2; i < 4; i++) {
            if (res[1].str() == threeops[i]) {
                unsigned int instr = B_cons(res[1].str(), res[2].str(), res[3].str(), stoi(res[4].str()));
                printinstr(instr, os);
            }
        }
        for (int i = 4; i < 12; i++) {
            if (res[1].str() == threeops[i]) {
                unsigned int instr = R_cons(res[1].str(), res[2].str(), res[3].str(), res[4].str());
                printinstr(instr, os);
            }
        }
        //assert
        os.flush();
        return;
    }
    if (regex_match(str, res, regex(tomatch[2]))) {
        for (int i = 0; i < 2; i++) {
            if (res[1].str() == twoops[i]) {
                unsigned int instr = U_J_cons(res[1].str(), res[2].str(), stoi(res[3].str()));
                printinstr(instr, os);
            }
        }
        //assert
        os.flush();
        return;
    }
    if (regex_match(str, res, regex(tomatch[3]))) {
        os << "00 FF 00 FF " << endl;
        os.flush();
        return;
    }
    parse_assert(false, str);
    return;
}

void parse_inputline(istream& is, ostream& os) {
    string str;
    os << "@00000000" << endl;
    while (getline(is, str)) {
        parse_commands(str, os);
    }
}

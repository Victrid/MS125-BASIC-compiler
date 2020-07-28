#include "lexer.hpp"
#include "ordos.hpp"
#include "parser.hpp"
#include <gtest/gtest.h>
using namespace std;

#define C(AAA)                                                            \
    TEST(ControlcfgTest, AAA) {                                           \
        fstream f1;                                                       \
        stringstream os, sttl, sttt;                                      \
        f1.open("testfiles/testcases/control_test/control_" #AAA ".txt"); \
        lex_inputline(f1, os);                                            \
        f1.close();                                                       \
        node t = buildtree(os);                                           \
        orderconstruct(&t);                                               \
        sttl << t;                                                        \
        cfgize_labelproc(sttl, sttt);                                     \
        EXPECT_NO_THROW(cfgize_symbolproc(sttt, sttl));                   \
    }

#define B(AAA)                                                        \
    TEST(BasiccfgTest, AAA) {                                         \
        fstream f1;                                                   \
        stringstream os, sttl, sttt;                                  \
        f1.open("testfiles/testcases/basic_test/basic_" #AAA ".txt"); \
        lex_inputline(f1, os);                                        \
        f1.close();                                                   \
        node t = buildtree(os);                                       \
        orderconstruct(&t);                                           \
        sttl << t;                                                    \
        cfgize_labelproc(sttl, sttt);                                 \
        EXPECT_NO_THROW(cfgize_symbolproc(sttt, sttl));               \
    }

#define O(AAA)                                                  \
    TEST(OpcfgTest, AAA) {                                      \
        fstream f1;                                             \
        stringstream os, sttl, sttt;                            \
        f1.open("testfiles/testcases/op_test/op_" #AAA ".txt"); \
        lex_inputline(f1, os);                                  \
        f1.close();                                             \
        node t = buildtree(os);                                 \
        orderconstruct(&t);                                     \
        sttl << t;                                              \
        cfgize_labelproc(sttl, sttt);                           \
        EXPECT_NO_THROW(cfgize_symbolproc(sttt, sttl));         \
    }

O(1);
O(2);
O(3);
O(4);
O(5);
O(6);
O(7);
O(8);
O(9);
O(10);

B(1);
B(2);
B(3);
B(4);
B(5);
B(6);
B(7);
B(8);
B(9);
B(10);

C(1);
C(2);
C(3);
C(4);
C(5);

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
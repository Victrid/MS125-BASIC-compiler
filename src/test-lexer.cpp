#include "lexer.hpp"
#include <gtest/gtest.h>
using namespace std;

#define C(AAA)                                                           \
    TEST(ControlTest, AAA) {                                             \
        fstream os, f;                                                   \
        f.open("testfiles/testcases/control_test/control_" #AAA ".txt"); \
        os.open("/dev/null");                                            \
        EXPECT_NO_THROW(lineproc(f, os));                                \
    }

#define B(AAA)                                                       \
    TEST(BasicTest, AAA) {                                           \
        fstream os, f;                                               \
        f.open("testfiles/testcases/basic_test/basic_" #AAA ".txt"); \
        os.open("/dev/null");                                        \
        EXPECT_NO_THROW(lineproc(f, os));                            \
    }

#define O(AAA)                                                 \
    TEST(OpTest, AAA) {                                        \
        fstream os, f;                                         \
        f.open("testfiles/testcases/op_test/op_" #AAA ".txt"); \
        os.open("/dev/null");                                  \
        EXPECT_NO_THROW(lineproc(f, os));                      \
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
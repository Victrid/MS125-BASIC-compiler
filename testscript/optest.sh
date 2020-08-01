GREEN='\033[1;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color
YELLOW='\033[1;33m'
echo -e ${BLUE}testing op${NC}:
echo building...
make
echo -e ${YELLOW}test_op_1${NC}:
./lexer testfiles/testcases/op_test/op_1.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "5 7" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 67$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_op_2${NC}:
./lexer testfiles/testcases/op_test/op_2.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "1 1" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 3$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_op_3${NC}:
./lexer testfiles/testcases/op_test/op_3.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "4 6" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 53$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_op_4${NC}:
./lexer testfiles/testcases/op_test/op_4.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "4 6" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 1944$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_op_5${NC}:
./lexer testfiles/testcases/op_test/op_5.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "4 6" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 19$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_op_6${NC}:
./lexer testfiles/testcases/op_test/op_6.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "8 6" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 0$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_op_7${NC}:
./lexer testfiles/testcases/op_test/op_7.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "10" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 4$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_op_8${NC}:
./lexer testfiles/testcases/op_test/op_8.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "3 6" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 1$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_op_9${NC}:
./lexer testfiles/testcases/op_test/op_9.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "8 10" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 4$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_op_10${NC}:
./lexer testfiles/testcases/op_test/op_10.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "7 8 2 3" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 12$'\t'output: ${GREEN}$O1${NC} 

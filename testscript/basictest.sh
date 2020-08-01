GREEN='\033[1;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color
YELLOW='\033[1;33m'
echo -e ${BLUE}testing basic${NC}:
echo building...
make
echo -e ${YELLOW}test_basic_1${NC}:
./lexer testfiles/testcases/basic_test/basic_1.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "0" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 0$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_basic_2${NC}:
./lexer testfiles/testcases/basic_test/basic_2.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "5" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 5$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_basic_3${NC}:
./lexer testfiles/testcases/basic_test/basic_3.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "4" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 4$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_basic_4${NC}:
./lexer testfiles/testcases/basic_test/basic_4.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "2" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 3$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_basic_5${NC}:
./lexer testfiles/testcases/basic_test/basic_5.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "2" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 4$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_basic_6${NC}:
./lexer testfiles/testcases/basic_test/basic_6.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "5 3" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 5$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_basic_7${NC}:
./lexer testfiles/testcases/basic_test/basic_7.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "5 3" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 3$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_basic_8${NC}:
./lexer testfiles/testcases/basic_test/basic_8.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "5" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 10$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_basic_9${NC}:
./lexer testfiles/testcases/basic_test/basic_9.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "5" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 6$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_basic_10${NC}:
./lexer testfiles/testcases/basic_test/basic_10.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "5" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 30$'\t'output: ${GREEN}$O1${NC} 
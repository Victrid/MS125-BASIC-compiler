GREEN='\033[1;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color
YELLOW='\033[1;33m'
echo -e ${BLUE}testing control${NC}:
echo building...
make
echo -e ${YELLOW}test_control_1${NC}:
./lexer testfiles/testcases/control_test/control_1.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "13" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 60480$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_control_2${NC}:
./lexer testfiles/testcases/control_test/control_2.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "6" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 6$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_control_3${NC}:
./lexer testfiles/testcases/control_test/control_3.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "10 5" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 0$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_control_4${NC}:
./lexer testfiles/testcases/control_test/control_4.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "5" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 16$'\t'output: ${GREEN}$O1${NC} 
echo -e ${YELLOW}test_control_5${NC}:
./lexer testfiles/testcases/control_test/control_5.txt | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
O1=$(echo "5" | ./riscv-core 1.riscv)
echo -e $'\t'expect: 10$'\t'output: ${GREEN}$O1${NC} 

if [[ $# -eq 0 ]] ; then
    echo 'usage: ./test.sh testfiles/testcases/basic_test'
    exit 1
fi
dir=$1

GREEN='\033[1;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color
YELLOW='\033[1;33m'

echo building...
make
echo -e ${BLUE}Running ${dir##*/}${NC}:
tests=0
passed=0
printf "%-10s %-8s %-8s %-10s\n" "Test Name" EXPECT VALUE STATUS
printf "\n"
for file in $dir/*; do
((tests++))
filename=${file##*/}
echo -ne 
./lexer ${file} | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > 1.riscv
retval=$(sed -n 's/^.*REM input:\s*\(.*\)$/\1/p' ${file} | ./riscv-core 1.riscv)
expectval=$(sed -n 's/^.*REM return value:\s*\(.*\)$/\1/p' ${file})
if [ "${expectval}" -eq "${retval}" ]
then
printf "${YELLOW}%-10s${NC} %-8s ${GREEN}%-8s${NC} ${GREEN}%-10s${NC}\n" ${filename%.txt} ${expectval} $retval Passed
((passed++))
else
printf "${YELLOW}%-10s${NC} %-8s ${RED}%-8s${NC} ${RED}%-10s${NC}\n" ${filename%.txt} ${expectval} $retval "Not Pass"
fi
rm 1.riscv
done
echo Final Result:
echo -e "$passed"/"$tests" Passed.

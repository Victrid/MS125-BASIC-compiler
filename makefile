.PHONY: all
all: lexer orderer
	@echo "done"

lexer: src/lexer-bin.cpp src/lexer.cpp src/lexer.hpp
	g++ src/lexer-bin.cpp src/lexer.cpp -o lexer

orderer: src/lexer-bin.cpp src/lexer.cpp src/ordos.cpp src/parser.cpp src/ordos.hpp src/parser.hpp
	g++ src/ordos-bin.cpp src/ordos.cpp src/lexer.cpp src/parser.cpp -o orderer

test_lexer: src/lexer.cpp src/test-lexer.cpp
	g++ src/lexer.cpp src/test-lexer.cpp -lgtest -o test_lexer

test_parser: src/lexer.cpp src/parser.cpp src/test-parser.cpp src/parser.hpp
	g++ src/lexer.cpp src/parser.cpp src/test-parser.cpp -lgtest -o test_parser

test_ordos: src/lexer.cpp src/parser.cpp src/ordos.cpp src/test-ordos.cpp src/ordos.hpp src/parser.hpp
	g++ src/lexer.cpp src/parser.cpp src/ordos.cpp src/test-ordos.cpp -lgtest -o test_ordos

test: test_lexer test_parser test_ordos
	./test_lexer
	./test_parser
	./test_ordos

unit_test_lexer: test_lexer
	./test_lexer

unit_test_parser: test_parser
	./test_parser

unit_test_ordos: test_ordos
	./test_ordos

.PHONY: clean
clean:
	rm -f ./test_lexer
	rm -f ./test_parser
	rm -f ./test_ordos
	rm -f ./test
	rm -f ./lexer
	rm -f ./orderer
	@echo "done"
.PHONY: all
all: lexer
	@echo "done"

lexer: src/lexer-bin.cpp src/lexer.cpp
	g++ src/lexer-bin.cpp src/lexer.cpp -o lexer

test_lexer: src/lexer.cpp src/test-lexer.cpp
	g++ src/lexer.cpp src/test-lexer.cpp -lgtest -o test_lexer

test_parser: src/lexer.cpp src/parser.cpp src/test-parser.cpp
	g++ src/lexer.cpp src/parser.cpp src/test-parser.cpp -lgtest -o test_parser

test: test_lexer test_parser
	./test_lexer
	./test_parser

unit_test_lexer: test_lexer
	./test_lexer

unit_test_parser: test_parser
	./test_parser

.PHONY: clean
clean:
	rm -f ./test_lexer
	rm -f ./test_parser
	rm -f ./lexer
	@echo "done"
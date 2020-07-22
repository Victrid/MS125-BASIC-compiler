.PHONY: all
all: lexer
	@echo "done"

lexer: src/lexer-bin.cpp src/lexer.cpp
	g++ src/lexer-bin.cpp src/lexer.cpp -o lexer

test_lexer: src/lexer.cpp src/test-lexer.cpp
	g++ src/lexer.cpp src/test-lexer.cpp -lgtest -o test_lexer

test: test_lexer
	./test_lexer

.PHONY: clean
clean:
	rm -f ./test_lexer
	rm -f ./lexer
	@echo "done"
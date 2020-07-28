.PHONY: all
all: lexer orderer cfgizer
	@echo "done"

lexer: src/lexer-bin.cpp src/lexer.cpp src/lexer.hpp
	g++ src/lexer-bin.cpp src/lexer.cpp -o lexer

orderer: src/ordos-bin.cpp src/ordos.cpp src/parser.cpp src/ordos.hpp src/parser.hpp
	g++ src/ordos-bin.cpp src/ordos.cpp src/parser.cpp -o orderer

cfgizer: src/parser.cpp src/ordos.cpp src/cfgize.cpp src/cfg-bin.cpp src/ordos.hpp src/parser.hpp
	g++ src/cfg-bin.cpp src/ordos.cpp src/parser.cpp src/cfgize.cpp -o cfgizer

test_lexer: src/lexer.cpp src/test-lexer.cpp
	g++ src/lexer.cpp src/test-lexer.cpp -lgtest -o test_lexer

test_parser: src/lexer.cpp src/parser.cpp src/test-parser.cpp src/parser.hpp
	g++ src/lexer.cpp src/parser.cpp src/test-parser.cpp -lgtest -o test_parser

test_ordos: src/lexer.cpp src/parser.cpp src/ordos.cpp src/test-ordos.cpp src/ordos.hpp src/parser.hpp
	g++ src/lexer.cpp src/parser.cpp src/ordos.cpp src/test-ordos.cpp -lgtest -o test_ordos

test_cfg: src/lexer.cpp src/parser.cpp src/ordos.cpp src/cfgize.cpp src/test-cfg.cpp src/ordos.hpp src/parser.hpp
	g++ src/lexer.cpp src/parser.cpp src/ordos.cpp src/cfgize.cpp src/test-cfg.cpp -lgtest -o test_cfg

.PHONY: test
test: test_lexer test_parser test_ordos test_cfg
	./test_lexer
	./test_parser
	./test_ordos
	./test_cfg

.PHONY: unit_test*
unit_test_lexer: test_lexer
	./test_lexer

unit_test_parser: test_parser
	./test_parser

unit_test_ordos: test_ordos
	./test_ordos

unit_test_cfg: test_cfg
	./test_cfg

.PHONY: clean
clean:
	rm -f ./test
	rm -f ./test_*
	rm -f ./cfgizer
	rm -f ./lexer
	rm -f ./orderer
	rm -f *.xml
	@echo "done"
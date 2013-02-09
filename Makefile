.PHONY: all tests clean

all: parser.exe tests

CXXFLAGS = -Wall -pedantic -g -O0
VPATH = nodes
QUEX_PATH = ./quex-0.63.1/
ASTNODES = ast.o programnode.o unitnode.o \
		binaryexpressionnode.o unaryexpressionnode.o variablenode.o numberexpressionnode.o \
		stringexpressionnode.o booleanexpressionnode.o functioncallnode.o \
		assignmentnode.o blockstatementnode.o gotonode.o labeledstatementnode.o \
		procedurecallnode.o repeatloopnode.o withnode.o arrayindexnode.o whileloopnode.o \
		forloopnode.o forrange.o ifthennode.o \
		blocknode.o typenode.o subroutinenode.o \
		environment.o

parser.exe: parser.o tiny_lexer.o pascal.o $(ASTNODES)
	$(LINE)
	$(CXX) $^ -o parser

pascal.o: pascal.c pascal.h
	$(LINE)
	$(CXX) -Wall -pedantic -c pascal.c -I$(QUEX_PATH) -I.

pascal.c pascal.h: pascal.y astnode.hpp lemon/lemon.exe
	$(LINE)
	lemon/lemon pascal.y

parser.o: parser.cpp tiny_lexer.cpp pascal.h astnode.hpp
	$(LINE)
	$(CXX) $(CXXFLAGS) -DQUEX_OPTION_ASSERTS_WARNING_MESSAGE_DISABLED -c parser.cpp -I$(QUEX_PATH) -I.

tiny_lexer.o : tiny_lexer.cpp
	$(LINE)
	$(CXX) -c $< -I$(QUEX_PATH) -I.

lemon/lemon.exe: lemon/lemon.c lemon/lempar.c
	$(LINE)
	$(CC) $< -o lemon/lemon.exe

$(ASTNODES) : astnode.hpp

tiny_lexer.cpp : pascal.qx
	$(LINE)
	./quex-0.63.1/quex-exe.py -i pascal.qx -o tiny_lexer

tests: parser.exe
	$(LINE)
	parser $(TESTFLAGS) tests/test1.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test2.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test3.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test4.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test5.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test6.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test7.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test8.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test9.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test10.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test11.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test12.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test13.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test14.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test15.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test16.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test17.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test18.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test19.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test20.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test21.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test22.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test23.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test24.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test25.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test26.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test27.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test28.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test29.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test30.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test31.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test32.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test33.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test34.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test35.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test36.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test37.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test38.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test39.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test40.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test41.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test42.pas
	$(LINE)
	parser $(TESTFLAGS) tests/test43.pas

clean:
	rm -f *.o
	rm -f *.exe
	rm -f pascal.c
	rm -f pascal.h
	rm -f tiny_lexer*

LINE = @echo --------------------

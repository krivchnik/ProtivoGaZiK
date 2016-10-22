# Makefile

TREE_DIR = ./Nodes/
OUT_DIR = ./Output/
COMPILER = CNumExpression.o CIdExpression.o COperationExpression.o CAssignStatement.o CCompoundStatement.o CPrintStatement.o CPrintVisitor.o 

OBJS	= bison.o lex.o main.o $(COMPILER)

CC	= g++
CFLAGS	= -g -Wall -ansi -pedantic -std=c++11



calc:	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o calc -lfl

lex.o:	
		$(CC) $(CFLAGS) -c 	$(OUT_DIR)lexer.c -o lex.o

bison.o:
		$(CC) $(CFLAGS) -c $(OUT_DIR)parser.c -o bison.o

main.o:		./Parser/main.cc
		$(CC) $(CFLAGS) -c ./Parser/main.cc -o main.o

lex.o yac.o main.o	: ./Parser/common_include.h
lex.o main.o		: ./Parser/heading.h

clean:
	rm -f *.o *~ lex.c lex.yy.c bison.c tok.h calc.tab.c calc.tab.h calc.output calc


CNumExpression.o: $(TREE_DIR)CNumExpression.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

CIdExpression.o: $(TREE_DIR)CIdExpression.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

COperationExpression.o: $(TREE_DIR)COperationExpression.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

CAssignStatement.o: $(TREE_DIR)CAssignStatement.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

CCompoundStatement.o: $(TREE_DIR)CCompoundStatement.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

CPrintStatement.o: $(TREE_DIR)CPrintStatement.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

CPrintVisitor.o: $(TREE_DIR)CPrintVisitor.cpp
	$(CC) -c $(CFLAGS) $^ -o $@



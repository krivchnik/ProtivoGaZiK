# Makefile

TREE_DIR = ./Nodes/
COMPILER = CNumExpression.o CIdExpression.o COperationExpression.o CAssignStatement.o CCompoundStatement.o CPrintStatement.o CPrintVisitor.o 

OBJS	= bison.o lex.o main.o $(COMPILER)

CC	= g++
CFLAGS	= -g -Wall -ansi -pedantic -std=c++11



calc:	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o calc -lfl

lex.o:	lex.c
		$(CC) $(CFLAGS) -c lex.c -o lex.o

lex.c:	flex.l
		flex flex.l
		cp lex.yy.c lex.c

bison.o:	bison.c
		$(CC) $(CFLAGS) -c bison.c -o bison.o

bison.c:	calc.y
		bison -d -v calc.y
		cp calc.tab.c bison.c
		cmp -s calc.tab.h tok.h || cp calc.tab.h tok.h

main.o:		main.cc
		$(CC) $(CFLAGS) -c main.cc -o main.o

lex.o yac.o main.o	: heading.h
lex.o main.o		: tok.h

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



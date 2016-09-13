CC = g++

CFLAGS = --std=c++11

Compiler: CNumExpression.o CIdExpression.o COperationExpression.o CAssignStatement.o CCompoundStatement.o main.o
	$(CC) --std=c++11 $^ -o Compiler

main.o: main.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

CNumExpression.o: CNumExpression.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

CIdExpression.o: CIdExpression.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

COpearationExpression.o: COperationExpression.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

CAssignStatement.o: CAssignStatement.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

CCompoundStatement.o: CCompoundStatement.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

CPrintVisitor.o: CPrintVisitor.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

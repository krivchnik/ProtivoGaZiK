all: build run

build:
	flex flex.l
	gcc lex.yy.c -lfl -o flex.out

run:
	cat resourceForFlexTest/QuickSort.java | ./flex.out

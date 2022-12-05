CC=g++
CFLAGS=-I.

all: find_union_przyklad
	
find_union_przyklad: find_union_przyklad.o find_union.o
	$(CC) -o find_union_przyklad find_union_przyklad.o find_union.o

find_union_przyklad.o: find_union_przyklad.cpp find_union.h
	$(CC) -c find_union_przyklad.cpp

find_union.o: find_union.cpp find_union.h
	$(CC) -c find_union.cpp
	
clean:
	rm -f *.o find_union_przyklad

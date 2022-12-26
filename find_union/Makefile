CC=g++
CFLAGS=-I.

all: find_union_przyklad skarbonki malpki gaz
	
find_union_przyklad: find_union_przyklad.o find_union.o
	$(CC) -o find_union_przyklad find_union_przyklad.o find_union.o

find_union_przyklad.o: find_union_przyklad.cpp find_union.h
	$(CC) -c find_union_przyklad.cpp

skarbonki: skarbonki.o find_union.o
	$(CC) -o skarbonki skarbonki.o find_union.o

skarbonki.o: skarbonki.cpp find_union.h
	$(CC) -c skarbonki.cpp

malpki: malpki.o find_union.o
	$(CC) -o malpki malpki.o find_union.o

malpki.o: malpki.cpp find_union.h
	$(CC) -c malpki.cpp

gaz: gaz.o find_union.o
	$(CC) -o gaz gaz.o find_union.o

gaz.o: gaz.cpp find_union.h
	$(CC) -c gaz.cpp

find_union.o: find_union.cpp find_union.h
	$(CC) -c find_union.cpp
	
clean:
	rm -f *.o find_union_przyklad skarbonki malpki gaz

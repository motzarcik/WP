CC=g++
CFLAGS=-I.

all: nawiasowanie widoczne kolejka_przyklad

widoczne: widoczne.o kolejka.o
	$(CC) -o widoczne widoczne.o kolejka.o

widoczne.o: widoczne.c kolejka.h
	$(CC) -c widoczne.c
	
nawiasowanie: nawiasowanie.o 
	$(CC) -o nawiasowanie nawiasowanie.o

nawiasowanie.o: nawiasowanie.c
	$(CC) -c nawiasowanie.c
	
kolejka_przyklad: kolejka_przyklad.o kolejka.o
	$(CC) -o kolejka_przyklad kolejka_przyklad.o kolejka.o

kolejka_przyklad.o: kolejka_przyklad.c kolejka.h
	$(CC) -c kolejka_przyklad.c

kolejka.o: kolejka.c kolejka.h
	$(CC) -c kolejka.c
	
clean:
	rm -f *.o widoczne kolejka_przyklad

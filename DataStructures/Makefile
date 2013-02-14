CC=gcc
CFLAGS=-g -pedantic -std=c99 -Wall -Wextra

main: main.o queue.o
	$(CC) $(CFLAGS) main.o queue.o -o main

main.o: main.c queue.h
	$(CC) $(CFLAGS) -c main.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

clean:
	rm -f *o
	rm -f main
	rm -f *~
all: main

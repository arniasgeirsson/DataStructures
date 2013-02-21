CC=gcc
CFLAGS=-g -pedantic -std=c99 -Wall -Wextra -pthread

main: main.o queue.o LinkedList.o stack.o ArrayQueue.o heap.o fibHeap.o
	$(CC) $(CFLAGS) main.o queue.o LinkedList.o stack.o ArrayQueue.o heap.o fibHeap.o -o main

main.o: main.c queue.h
	$(CC) $(CFLAGS) -c main.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

LinkedList.o: LinkedList.c LinkedList.h
	$(CC) $(CFLAGS) -c LinkedList.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

ArrayQueue.o: ArrayQueue.c ArrayQueue.h
	$(CC) $(CFLAGS) -c ArrayQueue.c

heap.o: heap.c heap.h
	$(CC) $(CFLAGS) -c heap.c

fibHeap.o: fibHeap.c fibHeap.h
	$(CC) $(CFLAGS) -c fibHeap.c

clean:
	rm -f *o
	rm -f main
	rm -f *~
all: main

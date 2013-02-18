#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "testQueue.h"
#include "queue.h"

typedef QNode* QQueue; /* Define a QQueue to give a more
                        intuativ understanding  */
#define debugValues 0  /* Used by use to quickly see the
                        values of the different log expressions */

/* Returns an integer from a void pointer  */
int sumInts(Data el)
{
    if (el == NULL) {
        return 0;
    }
    return *(int*)el;
}

/* Test the behaviour of our queue implementation,
   if queue is NULL. */
int testNullQueue()
{
    QQueue *queue = NULL;
    Data el = malloc(sizeof(int));
    Data rel;
    int a = 6;
    el = &a;
    
    enqueue(queue, el);
    rel = dequeue(queue);
    if (debugValues) {
        printf("Truth of rel == NULL, %d\n", rel == NULL);
    }
    return (rel == NULL);
}

/* Test the behaviour of our queue implementation,
   if the data is NULL, and if the queue is empty. */
int testNullData()
{
    QQueue queue = NULL;
    Data el = NULL;
    Data rel;
    int len;
    int sumq;
    
    enqueue(&queue, el);
    len = length(queue);
    sumq = sum(queue, sumInts);
    rel = dequeue(&queue);

    if (debugValues) {
        printf("Truth of (len == 0), %d, (sumq == -1), %d, (rel == NULL), %d\n"
	       , (len == 0), (sumq == 0), (rel == NULL));
    }
    return (len == 0) && (sumq == 0) && (rel == NULL);
}

/* Test the behaviour of our queue implementation,
   by creating a queue with a random number of nodes
   and each containing a random integer.*/
int testRandomQueue()
{
    QQueue queue = NULL;
    int sumq = 0;
    int sumb = 0;
    int suma = 0;
    int len = 0;
    srand((u_int32_t)time(NULL)); /* Seed the random generator */
    int size = rand() % 1000;
    
    
    for (int i = 0; i < size; i++)
    {
        int* el = (int*)malloc(sizeof(Data));
        *el = rand()/100000;
        sumb = sumb + *el;
        enqueue(&queue, el);
    }
    sumq = sum(queue, sumInts);
    len = length(queue);
    for (int i = 0; i < size; i++) {
        int* el = dequeue(&queue);
        suma = suma + sumInts(el);
        free(el);
    }
    
    if (debugValues) {
        printf("Truth of (sumi == sumq && sumq == suma), %d, len == size(%d), %d\n"
	       , (sumb == sumq && sumq == suma), size, len == size);
    }
    
    return (sumb == sumq && sumq == suma) && len == size;
}

int runTest()
{
    printf("Running queue test!\n");
    
    /* Hvad skal testest?
       k Alle funktionerne med queues som NULL.
       k Alle funktionerne med data som NULL.
       k Alle funktioner med tomme queues.
       k Alle funktioner med random queues af længde på 1-1000.
            Alle funktioner med forskellige data typer.
        Test om ting som burde gå galt, går galt. (?)
     */
    int test1 = testNullQueue();
    int test2 = testNullData();
    int test3 = testRandomQueue();
    
    return test1 && test2 && test3;
}

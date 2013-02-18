//
//  ArrayQueue.c
//  DSX
//
//  Created by Arni Asgeirsson on 14/02/13.
//  Copyright (c) 2013 Arni Asgeirsson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "ArrayQueue.h"

/**
 Initialise an priority Queue with the
 specified type.
 */
array_queue* initQueue(int type)
{
    array_queue* queue = (array_queue*)malloc(sizeof(array_queue));
    queue->length = 0;
    if (type != MAXIMUM_QUEUE && type != MINIMUM_QUEUE)
    {
        printf("Init: Invalid queue type, must be either MAXIMUM_QUEUE or MINIMUM_QUEUE, not %d.\n", type);
        printf("Queue is initialised as a MINIMUM_QUEUE.\n");
        queue->type = MINIMUM_QUEUE;
    } else {
        queue->type = type;
    }
    
    return queue;
}


void exchange(array_queue *queue, int a, int b)
{
    
    Data x = queue->array[a];
    queue->array[a] = queue->array[b];
    queue->array[b] = x;
     /*
    int x = queue->array[a];
    queue->array[a] = queue->array[b];
    queue->array[b] = x;*/
}

int compareInts(Data el1, Data el2, int type)
{
    if (type == LESSTHEN_OR_EQUAl) {
        return ((*(int*)el1) >= (*(int*)el2));
    } else {
        printf("Compare: %d is not a valid compare type.\n", type);
        return 0;
    }
}

int partition(array_queue *queue, int p, int r)
{
    /*
    int x = queue->array[r];
    int i = p-1;
    for (int j = p; j < r; j++) {
        if (compareInts((queue->array[j]), x, LESSTHEN_OR_EQUAl)) {
            i++;
            exchange(queue, i, j);
        }
    }
    exchange(queue, i+1, r);
    return i+1;
    */
    Data x = queue->array[r];
    int i = p-1;
    for (int j = p; j < r; j++) {
        if (compareInts((queue->array[j]), x, LESSTHEN_OR_EQUAl)) {
            i++;
            exchange(queue, i, j);
        }
    }
    exchange(queue, i+1, r);
    return i+1;
}

void quickSort(array_queue *queue, int p, int r)
{
    int q;
    if (p < r)
    {
        q = partition(queue,p,r);
        quickSort(queue, p, q-1);
        quickSort(queue, q+1, r);
    }
}

/**
 Add an element to the queue.
 */
void addToQueue(array_queue* queue, Data el)
{
    if (queue == NULL) {
        printf("Add: Queue cannot be NULL.\n");
        return;
    }
    
    if (queue->length == MAX_QUEUE_LENGTH) {
        printf("Add: Queue is full, cannot add anymore.\n");
        return;
    }
/*
    printf("adding: %d\n", *(int*)el);
    
    Data elP = (Data)malloc(sizeof(int));
    elP = (int*)el;
    queue->array[queue->length] = &el;
    
    quickSort(queue, 1, queue->length);
    queue->length = queue->length+1;
    
    */
    
    queue->array[queue->length] = el;
    
    //quickSort(queue, 0, queue->length);
    queue->length = queue->length+1;
}

/**
 Returns the first element in the queue.
 Returns NULL if the queue is empty.
 */
Data getFirstFromQueue(array_queue* queue)
{
    if (queue == NULL) {
        printf("GetFirst: Queue cannot be NULL.\n");
        return NULL;
    }
    if (queue->length == 0) {
        printf("GetFirst: Queue is empty.\n");
        return NULL;
    }
    
    queue->length = queue->length-1;
    return queue->array[queue->length];
    
    /*
    int index = (queue->length-1);
    printf("index = %d\n", index);
    int* el = (int*)malloc(sizeof(int));
    el = *(queue->array[index]);
    printf("el = %d\n", *el);
    queue->length = queue->length-1;
    return el;
     */
}

/**
 Returns the length of the queue.
 */
int lengthAQ(array_queue* queue)
{
    return queue->length;
}

void printQueueInts(array_queue* queue)
{
    if (queue == NULL) {
        printf("GetFirst: Queue cannot be NULL.\n");
        return;
    }
    
    printf("print: length = %d\n", queue->length);
    
    for (int i = 0; i < queue->length; i++)
    {
        printf("queue[%d] = %d\n", i, *((int*)queue->array[i]));
        //printf("queue[%d] = %d\n", i, *(int*)(*(queue->array[i])));
    }
    printf("\n");
}

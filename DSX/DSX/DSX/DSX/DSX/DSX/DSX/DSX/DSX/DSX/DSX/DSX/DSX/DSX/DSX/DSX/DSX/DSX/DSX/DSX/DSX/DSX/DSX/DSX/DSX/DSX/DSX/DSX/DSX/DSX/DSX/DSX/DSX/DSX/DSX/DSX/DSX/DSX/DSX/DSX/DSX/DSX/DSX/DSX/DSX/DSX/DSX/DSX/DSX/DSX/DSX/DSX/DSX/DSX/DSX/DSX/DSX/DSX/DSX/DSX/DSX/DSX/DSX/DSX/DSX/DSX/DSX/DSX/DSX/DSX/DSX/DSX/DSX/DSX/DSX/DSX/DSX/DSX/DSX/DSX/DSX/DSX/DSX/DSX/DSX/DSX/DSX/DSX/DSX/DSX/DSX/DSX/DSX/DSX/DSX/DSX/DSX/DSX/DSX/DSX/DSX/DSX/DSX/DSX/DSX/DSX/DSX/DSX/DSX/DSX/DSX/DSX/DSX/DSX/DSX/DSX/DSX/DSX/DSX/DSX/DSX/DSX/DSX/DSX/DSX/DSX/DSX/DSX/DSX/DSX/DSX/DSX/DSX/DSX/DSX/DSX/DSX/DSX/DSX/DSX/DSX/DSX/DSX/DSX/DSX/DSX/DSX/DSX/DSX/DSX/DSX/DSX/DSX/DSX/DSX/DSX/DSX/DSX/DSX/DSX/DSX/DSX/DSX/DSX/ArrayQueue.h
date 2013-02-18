//
//  ArrayQueue.h
//  DSX
//
//  Created by Arni Asgeirsson on 14/02/13.
//  Copyright (c) 2013 Arni Asgeirsson. All rights reserved.
//

#ifndef DSX_ArrayQueue_h
#define DSX_ArrayQueue_h

#include "Definitions.h"

#define MAX_QUEUE_LENGTH 10000
#define MAXIMUM_QUEUE 0
#define MINIMUM_QUEUE 1

#define LESSTHEN_OR_EQUAl 0

typedef struct array_queue_ {
    Data array[MAX_QUEUE_LENGTH];
    int type;
    int length;
} array_queue;

/**
 Initialise an priority Queue with the
 specified type.
 */
array_queue* initQueue(int type);

/**
 Use quicksort to sort the queue.
 */
void quickSort(array_queue *queue, int p, int r);

/**
 Add an element to the queue.
 */
void addToQueue(array_queue* queue, Data el);

/**
 Returns the first element in the queue.
 Returns NULL if the queue is empty.
 */
Data getFirstFromQueue(array_queue* queue);

/**
 Returns the length of the queue.
 */
int lengthAQ(array_queue* queue);

void printQueueInts(array_queue* queue);

#endif

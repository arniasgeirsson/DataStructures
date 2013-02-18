//
//  queue.c
//  DataStructures
//
//  Created by Arni Asgeirsson on 12/02/13.
//  Copyright (c) 2013 Arni Asgeirsson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* return number of elements in queue */
int length(QNode* queue)
{
    int len = 0;
    QNode current;
    
    if (queue == NULL) {
        return 0;
    }

    current = *queue;
    if (&current == NULL) {
        return 0;
    }
    
    do
    {
        len = len + 1;
        current = *current.link;
    } while (!(current.content == (*queue).content && current.link == (*queue).link)
             && &current != NULL);
    
    return len;
}

/* add element at rear end */
void enqueue(QNode** queue, Data el)
{
    /* Create a new node */
    QNode *newNode = (QNode*)malloc(sizeof(QNode));
    QNode *lastAddedNode;
    QNode *firstNode;
    
    if (el == NULL) {
        free(newNode);
        return;
    }
    
    if (newNode == NULL) {
        printf("Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    
    /* Set content of the new node */
    newNode->content = el;
    newNode->link = NULL;
    if (queue == NULL) {
        free(newNode);
        return;
    }
    if (*queue != NULL) {
        lastAddedNode = *queue;
        firstNode = lastAddedNode->link;
        
        lastAddedNode->link = newNode;
        newNode->link = firstNode;
        
        *queue = newNode;
    } else {
        /* Set the link to itself. */
        newNode->link = newNode;
        *queue = newNode;
    }
}

/* remove and return front element */
Data dequeue(QNode** queue)
{
    Data el = NULL;
    QNode *firstNode;
    int len = 0;
    if (queue == NULL) {
        return NULL;
    }
    if (*queue != NULL) {
        len = length(*queue);
        firstNode = (*queue)->link;
        (*queue)->link = firstNode->link;
        el = firstNode->content;
        free(firstNode);
        /* Make sure to set the queue to point to NULL
           if last element was removed. */
        if (len == 1) {
            *queue = NULL;
        }
    }
    
    return el;
}

/* sum values of all data in queue */
int sum(QNode* queue, int (*val)(Data))
{
    int sum = 0;
    QNode current;
    
    if (queue == NULL) {
        return 0;
    }
    
    current = *queue;
    if (&current == NULL) {
        return 0;
    }
    do {
        sum = sum + val(current.content);
        current = *current.link;
    } while (!(current.content == (*queue).content && current.link == (*queue).link)
             && &current != NULL);
    
    return sum;
}

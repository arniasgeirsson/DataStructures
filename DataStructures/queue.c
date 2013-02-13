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

/* Is used to help the length function. */
int return1(Data el)
{
    return 1;
}

int length(QNode* queue)
{
    return sum(queue, return1);
}

void enqueue(QNode** queue, Data el)
{
    /* Create a new node */
    QNode *newNode = (QNode*)malloc(sizeof(QNode));
    QNode *lastAddedNode;
    QNode *firstNode;
    
    if (newNode == NULL) {
        printf("Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    
    /* Set content of the new node */
    newNode->content = el;
    newNode->link = NULL;
    
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

Data dequeue(QNode** queue)
{
    Data el = NULL;
    QNode *firstNode;
    int len = 0;
    
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

int sum(QNode* queue, int (*val)(Data))
{
    if (queue == NULL) {
        return 0;
    }
    
    int sum = 0;
    QNode current = *queue;
    
    do {
        sum = sum + val(current.content);
        current = *current.link;
    } while (!(current.content == (*queue).content && current.link == (*queue).link));
    
    return sum;
}
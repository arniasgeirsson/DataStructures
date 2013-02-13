//
//  main.c
//  DataStructures
//
//  Created by Arni Asgeirsson on 12/02/13.
//  Copyright (c) 2013 Arni Asgeirsson. All rights reserved.
//
// http://en.wikipedia.org/wiki/List_of_data_structures

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int number(Data el)
{
    return *(int*)el;
}

void testQueue()
{
    QNode *queue = NULL;
    Data el1 = malloc(sizeof(int));
    Data el2 = malloc(sizeof(int));
    Data el3 = malloc(sizeof(int));
    Data el4 = malloc(sizeof(int));
    int a1 = 8;
    int a2 = 2;
    int a3 = 10;
    int a4 = 7;
    el1 = &a1;
    el2 = &a2;
    el3 = &a3;
    el4 = &a4;
    int b = - 1;
    int c;
    b = length(queue);
    printf("Length: %d\n", b);
    
    enqueue(&queue, el1);
    b = sum(queue, number);
    printf("1Sum: %d\n", b);
    
    enqueue(&queue, el2);
    b = sum(queue, number);
    printf("2Sum: %d\n", b);
    
    enqueue(&queue, el3);
    b = sum(queue, number);
    printf("3Sum: %d\n", b);
    
    enqueue(&queue, el4);
    printf("Lengt11h: %d\n", b);
    
    b = length(queue);
    printf("Length: %d\n", b);
    
    b = sum(queue, number);
    printf("Sum: %d\n", b);
    
    b = length(queue);
    printf("Length: %d\n", b);
    
    b = sum(queue, number);
    printf("Sum: %d\n", b);
    
    Data h = dequeue(&queue);
    b = length(queue);
    c = sum(queue, number);
    
    printf("%d, len: %d, sum: %d\n", *(int*)h,b,c);
    
    h = dequeue(&queue);
    b = length(queue);
    c = sum(queue, number);
    
    printf("%d, len: %d, sum: %d\n", *(int*)h,b,c);
    
    h = dequeue(&queue);
    b = length(queue);
    c = sum(queue, number);
    
    printf("%d, len: %d, sum: %d\n", *(int*)h,b,c);
    
    h = dequeue(&queue);
    b = length(queue);
    c = sum(queue, number);
    
    printf("%d, len: %d, sum: %d\n", *(int*)h,b,c);
    
    h = dequeue(&queue);
    b = length(queue);
    c = sum(queue, number);
    
    if (h != NULL) {
        printf("%d, len: %d, sum: %d\n", *(int*)h,b,c);
    } else {
        printf("The queue is empty\n");
    }
}


int main(int argc, const char * argv[])
{
    printf("Hello, World!\n");


    //testQueue();
    
    
    printf("Hello, World!\n");
    return 0;
}
